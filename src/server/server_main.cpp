#server

#include "../shared/net.hpp"
#include "../shared/game_state.hpp"
#include <iostream>
#include <vector>
#include <unistd.h> // sleep

int server_main() {
    std::cout << "[Server] Starting...\n";
    net_init_server(12345);  // bind to port 12345

    GameState state;
    std::vector<ClientInfo> clients;

    while (true) {
        // 1. Receive input
        char input;
        sockaddr_in addr;
        int received = net_receive_input(&input, &addr);
        if (received > 0) {
            // Add client if new
            net_add_client_if_new(clients, addr);

            // Example: just update player 0
            state.players[0].processInput(input);
        }

        // 2. Send state to all clients
        std::string data = state.serialize();
        for (const auto& c : clients) {
            net_send_state(data.c_str(), data.size(), c.addr);
        }

        usleep(16000); // ~60 FPS
    }

    return 0;
}

