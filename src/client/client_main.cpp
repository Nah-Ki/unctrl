#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Client Window");
    sf::UdpSocket socket;
    socket.bind(sf::Socket::AnyPort);

    sf::IpAddress serverIp = "127.0.0.1";
    unsigned short serverPort = 54000;

    // Send HELLO packet
    sf::Packet packet;
    packet << static_cast<int>(0); // HELLO
    socket.send(packet, serverIp, serverPort);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.display();
    }
}

