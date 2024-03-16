#include "Game.hpp"

Game::Game(sf::RenderWindow window) : window(&window), isRunning(true) {}

Game::~Game() {}

void Game::run() {
    while (isRunning && window->isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isRunning = false;
            window->close();
        }
    }
}

void Game::update() {
    // Update game logic here
}

void Game::render() {
    window->clear();
    // Draw game objects here
    window->display();
}
