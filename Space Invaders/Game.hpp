#ifndef GAME_HPP
#define GAME_HPP

#include "Window.hpp"

class Game {
public:
    Game(sf::RenderWindow window);
    ~Game();

    void run();

private:
    sf::RenderWindow *window;
    bool isRunning;

    void processEvents();
    void update();
    void render();
};

#endif //GAME_HPP