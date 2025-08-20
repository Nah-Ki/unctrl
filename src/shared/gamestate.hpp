
#pragma once
#include <SFML/System.hpp>
#include <map>

struct PlayerState {
    sf::Vector2f position;
    sf::Vector2f velocity;
};

struct GameState {
    std::map<int, PlayerState> players;
};
