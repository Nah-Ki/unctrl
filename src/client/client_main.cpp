#include "game.hpp"
#include "game_state.hpp"
#include <iostream>
#include <termios.h>
#include <unistd.h>

int client_main() {
    std::cout << "[Client] Starting...\n";
    net_init_client("127.0.0.1", 12345);  // connect to localhost:12345

    while (true) {
        // 1. Get input (non-blocking keypress)
        char c;
        if (read(STDIN_FILENO, &c, 1) > 0) {
            net_send_input(c);
        }

        // 2. Receive state
        char buffer[512];
        int len = net_receive_state(buffer, sizeof(buffer));
        if (len > 0) {
            GameState state = GameState::deserialize(buffer, len);

            // 3. Render basic output
            system("clear");
            for (int i = 0; i < state.playerCount; ++i) {
                std::cout << "Player " << i << ": (" << state.players[i].x << ", " << state.players[i].y << ")\n";
            }
        }

        usleep(16000); // ~60 FPS
    }

    return 0;
}

