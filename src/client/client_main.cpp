#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Client Window");

    sf::UdpSocket socket;
    socket.bind(sf::Socket::AnyPort);

    sf::Packet packet;
    packet << "Hello from client";

    auto serverIp = sf::IpAddress::resolve("127.0.0.1").value();
    unsigned short serverPort = 54000;
    socket.send(packet, serverIp, serverPort);

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.display();
    }
}
