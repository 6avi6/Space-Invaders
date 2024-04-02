#ifndef GAME_HPP
#define GAME_HPP

#include "Window.hpp"
#include "Player.hpp"
#include"Enemy.hpp"
#include "RockWall.hpp"
//import <iostream>;
#include <random>
#include <thread>
class Game {
public:
    Game(sf::RenderWindow *window);
    ~Game();

    void run();
    const int getScore();
private:
    sf::RenderWindow *window;
    bool isRunning;
    int clock; //count to 60 and reset to 0
    void processEvents();
    void update();
    void render();
        
    int level;
    void intLevel();

    std::shared_ptr<Player> player;
    void initPlayer(std::string texturePath);
    bool playerFired;
    int playerReload;
    int playerCounterReload;

    std::vector<std::shared_ptr<Enemy>> enemies; // Vector of enemies using smart pointers
    std::string enemyTexturePath;
    void spawnEnemy(float xPos, float yPos, const std::string& texturePath); // Function to spawn enemies
    void setEnemies();
    int enemyReload;
    int enemyNumber;
    void randomEnemyShoot();
    void checkAndHandleEnemyCollison();
    void checkIfPlayerIsHit();

    int score;
    
    sf::Font fontslkscre;
    sf::Text scoreOfPlayer;
    void initFonts();

    std::vector<std::shared_ptr<RockWall>> rockWalls;
    void initRockWalls();
    void drawRockWalls();
    void checkIfEnemyHittedRockWall();
};

#endif //GAME_HPP