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
        case 'w':
        case KEY_UP:
            y--;
            break;
        case 's':
        case KEY_DOWN:
            y++;
            break;
        case 'a':
        case KEY_LEFT:
            x--;
            break;
        case 'd':
        case KEY_RIGHT:
            x++;
            break;
    }
}

