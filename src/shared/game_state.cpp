#include "game_state.hpp"
#include <sstream>

std::string GameState::serialize() const {
    std::ostringstream oss;
    oss << playerCount << "\n";
    for (int i = 0; i < playerCount; ++i)
        oss << players[i].x << " " << players[i].y << "\n";
    return oss.str();
}

GameState GameState::deserialize(const char* data, size_t len) {
    GameState state;
    std::istringstream iss(std::string(data, len));
    iss >> state.playerCount;
    for (int i = 0; i < state.playerCount; ++i)
        iss >> state.players[i].x >> state.players[i].y;
    return state;
}

