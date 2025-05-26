#include "player.hpp"
#include <ncurses.h>

void Player::update() {
    // Placeholder for future logic
}

void Player::draw() {
    mvprintw(y, x, "@");
}

void Player::handleInput(int ch) {
    switch(ch) {
        case KEY_UP:    y--; break;
        case KEY_DOWN:  y++; break;
        case KEY_LEFT:  x--; break;
        case KEY_RIGHT: x++; break;
    }
}

