#include <SFML/Network.hpp>
#include <iostream>
#include <optional>

int main() {
    sf::UdpSocket socket;
    if (socket.bind(54000) != sf::Socket::Status::Done) {
        std::cerr << "Failed to bind server socket\n";
        return -1;
    }

    std::cout << "Server listening on port 54000...\n";

    while (true) {
        sf::Packet packet;
        std::optional<sf::IpAddress> sender;
        unsigned short port;

        if (socket.receive(packet, sender, port) == sf::Socket::Status::Done) {
            std::string msg;
            packet >> msg;
            std::cout << "Received: " << msg << " from " << sender->toString() << ":" << port << "\n";
        }
    }

    return 0;
}
