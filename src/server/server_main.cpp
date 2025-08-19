#include <SFML/Network.hpp>
#include <iostream>

int main() {
    sf::UdpSocket socket;
    socket.bind(54000);

    std::cout << "Server running on port 54000...\n";

    while (true) {
        sf::Packet packet;
        sf::IpAddress sender;
        unsigned short port;

        if (socket.receive(packet, sender, port) == sf::Socket::Done) {
            int type;
            packet >> type;

            if (type == 0) {
                std::cout << "Received HELLO from " << sender << ":" << port << "\n";
            }
        }
    }
}

