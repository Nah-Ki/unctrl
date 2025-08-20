#include <SFML/Network.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <optional>
#include <random>
#include "../shared/packets.hpp"

struct ClientEndpoint {
    sf::IpAddress address;
    unsigned short port{};

    ClientEndpoint() : address(sf::IpAddress::None, port(0){}
    ClientEndpoint(const sf::IpAddress& addr, unsigned short p)
        : address(addr), port(p) {}
};

struct Player {
    std::uint32_t id{};
    sf::Vector2f pos{400.f, 300.f};
};

int main() {
    const unsigned short kServerPort = 54000;
    const float kSpeed = 200.f; // units/sec

    sf::UdpSocket socket;
    auto status = socket.bind(kServerPort);
    if (status != sf::Socket::Status::Done) {
        std::cerr << "[Server] Failed to bind on port " << kServerPort << "\n";
        return 1;
    }
    socket.setBlocking(false);
    std::cout << "[Server] Listening on port " << kServerPort << "...\n";

    // id -> player
    std::unordered_map<std::uint32_t, Player> players;
    // endpoint key string -> id
    std::unordered_map<std::string, std::uint32_t> endpointToId;
    // id -> endpoint
    std::unordered_map<std::uint32_t, ClientEndpoint> idToEndpoint;

    // simple id generator
    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<std::uint32_t> dist(1000, 999999);

    auto endpointKey = [](const sf::IpAddress& ip, unsigned short port) {
        return ip.toString() + ":" + std::to_string(port);
    };

    sf::Clock tickClock;
    const float tickRate = 1.f / 60.f;
    float tickAcc = 0.f;

    while (true) {
        // ---- Receive all pending packets ----
        while (true) {
            sf::Packet packet;
            std::optional<sf::IpAddress> sender;
            unsigned short senderPort{};
            auto rs = socket.receive(packet, sender, senderPort);
            if (rs != sf::Socket::Status::Done) break; // no more

            PacketType type{};
            if (!(packet >> type)) continue;

            const std::string key = endpointKey(sender.value(), senderPort);

            if (type == PacketType::Join) {
                // Assign ID if new; else resend AssignId
                std::uint32_t id;
                if (endpointToId.find(key) == endpointToId.end()) {
                    id = dist(rng);
                    endpointToId[key] = id;
                    idToEndpoint[id] = ClientEndpoint{sender.value(), senderPort};
                    players[id] = Player{id, sf::Vector2f{400.f, 300.f}};
                    std::cout << "[Server] New client " << key << " -> id " << id << "\n";
                } else {
                    id = endpointToId[key];
                }
                sf::Packet out;
                out << PacketType::AssignId << id;
                socket.send(out, sender.value(), senderPort);
            }
            else if (type == PacketType::Input) {
                std::uint32_t id; std::uint8_t keys; float dt;
                if (!(packet >> id >> keys >> dt)) continue;
                auto it = players.find(id);
                if (it == players.end()) continue;

                // keys bitmask: 1=W, 2=A, 4=S, 8=D
                sf::Vector2f dir{0.f, 0.f};
                if (keys & 1) dir.y -= 1.f;
                if (keys & 4) dir.y += 1.f;
                if (keys & 2) dir.x -= 1.f;
                if (keys & 8) dir.x += 1.f;
                it->second.pos += dir * (kSpeed * dt);
            }
        }

        // ---- Broadcast state at ~60Hz ----
        float dt = tickClock.restart().asSeconds();
        tickAcc += dt;
        if (tickAcc >= tickRate) {
            tickAcc = 0.f;

            // Build state packet: [State][count][id x y]...
            sf::Packet state;
            state << PacketType::State;
            std::uint32_t count = static_cast<std::uint32_t>(players.size());
            state << count;
            for (auto& [id, p] : players) {
                PlayerState ps{id, p.pos.x, p.pos.y};
                state << ps;
            }

            for (auto& [id, ep] : idToEndpoint) {
                socket.send(state, ep.address, ep.port);
            }
        }

        // Small sleep to avoid busy-spin
        sf::sleep(sf::milliseconds(1));
    }
    return 0;
}
