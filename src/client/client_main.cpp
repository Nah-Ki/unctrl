#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <unordered_map>
#include <optional>
#include "../shared/packets.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "unctrl - Client");
    window.setFramerateLimit(120);

    // ---- Networking ----
    sf::UdpSocket socket;
    socket.bind(sf::Socket::AnyPort);
    socket.setBlocking(false);

    auto serverIp = sf::IpAddress::resolve("127.0.0.1").value(); // change if server is remote
    unsigned short serverPort = 54000;

    // Send Join
    {
        sf::Packet join; join << PacketType::Join;
        socket.send(join, serverIp, serverPort);
    }

    std::uint32_t myId = 0;
    std::unordered_map<std::uint32_t, sf::Vector2f> positions;

    sf::Clock frameClock;

    while (window.isOpen()) {
        // ---- Handle window events (SFML 3 style) ----
        while (auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) window.close();
        }

        float dt = frameClock.restart().asSeconds();

        // ---- Send input to server ----
        std::uint8_t keys = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) keys |= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) keys |= 2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) keys |= 4;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) keys |= 8;

        if (myId != 0) {
            sf::Packet input;
            input << PacketType::Input << myId << keys << dt;
            socket.send(input, serverIp, serverPort);
        }

        // ---- Receive packets ----
        while (true) {
            sf::Packet packet;
            std::optional<sf::IpAddress> sender;
            unsigned short senderPort{};
            auto rs = socket.receive(packet, sender, senderPort);
            if (rs != sf::Socket::Status::Done) break;

            PacketType type{};
            if (!(packet >> type)) continue;

            if (type == PacketType::AssignId) {
                packet >> myId;
                std::cout << "[Client] Assigned id = " << myId << "\n";
            }
            else if (type == PacketType::State) {
                std::uint32_t count; packet >> count;
                positions.clear();
                for (std::uint32_t i = 0; i < count; ++i) {
                    PlayerState ps; packet >> ps;
                    positions[ps.id] = {ps.x, ps.y};
                }
            }
        }

        // ---- Draw ----
        window.clear(sf::Color::Black);

        for (auto& [id, pos] : positions) {
            sf::CircleShape playerShape(12.f);
            playerShape.setOrigin({12.f, 12.f});
            playerShape.setPosition(pos);
            playerShape.setFillColor(id == myId ? sf::Color::Green : sf::Color::White);
            window.draw(playerShape);
        }

        window.display();
    }
    return 0;
}
