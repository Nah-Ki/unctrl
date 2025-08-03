#pragma once
#include <string>

struct Player {
    int x = 0, y = 0;

    void processInput(char c) {
        if (c == 'w') y--;
        if (c == 's') y++;
        if (c == 'a') x--;
        if (c == 'd') x++;
    }
};

struct GameState {
    Player players[4];
    int playerCount = 1;

    std::string serialize() const;
    static GameState deserialize(const char* data, size_t len);
};

