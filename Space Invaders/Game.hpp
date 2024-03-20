#ifndef GAME_HPP
#define GAME_HPP

#include "Window.hpp"
#include "Player.hpp"
#include"Enemy.hpp"
class Game {
public:
    Game(sf::RenderWindow *window);
    ~Game();

    void run();

private:
    sf::RenderWindow *window;
    bool isRunning;

    void processEvents();
    void update();
    void render();

    std::shared_ptr<Player> player;
    void initPlayer(std::string texturePath);

    std::vector<std::shared_ptr<Enemy>> enemies; // Vector of enemies using smart pointers
    std::string enemyTexturePath;
    void spawnEnemy(float xPos, float yPos, const std::string& texturePath); // Function to spawn enemies
    void setEnemies();

    void checkAndHandleEnemyCollison();
};

#endif //GAME_HPP