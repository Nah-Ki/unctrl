#include "game.hpp"
#include "player.hpp"
#include <ncurses.h>
#include <unistd.h>

Player player;

void Game::init() {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(100); // non-blocking getch
}

void Game::run() {
    bool running = true;
    while (running) {
        clear();
        player.update();
        player.draw();
        refresh();

        int ch = getch();
        if (ch == 'q') running = false;
        player.handleInput(ch);

        usleep(16000); // ~60fps
    }
}

void Game::cleanup() {
    endwin();
}

