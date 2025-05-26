#pragma once

class Player {
public:
    void update();
    void draw();
    void handleInput(int ch);

private:
    int x = 10;
    int y = 10;
};

