#include "Game.hpp"

Game::Game(sf::RenderWindow *window) : window(window), isRunning(true) {
    enemyTexturePath = "Assets/Texture/enemyTexture.png";
    this->initPlayer("Assets/Texture/playerTexture.png");
    this->setEnemies();
}

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
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed ) {
            this->isRunning = false;
            this->window->close();
        }
        if (event.key.code == sf::Keyboard::Escape)
            this->isRunning = false;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->movePlayer(1);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->player->movePlayer(-1);
    
}

void Game::update() {
    // Update game logic here
}

void Game::render() {
    window->clear();
    // Drawn game

    //Drawing enemies
    for (const auto& enemy : enemies) {
        enemy->draw(window);
    }

    //Drawing player
    player->draw(window);

    window->display();
}

void Game::initPlayer(std::string texturePath)
{
    player = std::make_shared<Player>(this->window->getSize().x/2, this->window->getSize().y*0.85, texturePath);

}

void Game::spawnEnemy(float xPos, float yPos, const std::string& texturePath) {
   
    std::shared_ptr<Enemy> newEnemy = std::make_shared<Enemy>(xPos, yPos, texturePath);
    enemies.push_back(newEnemy);
}

void Game::setEnemies() {
    sf::Texture Texture;
    if (!Texture.loadFromFile(enemyTexturePath)) {
        // Handle error if loading fails
        // For now, let's just print an error message
        std::cout << "ENEMY::ENEMY(float xPos, float yPos, const std::string& texturePath)::'Failed to load enemy texture!'" << std::endl;
    }
    //baisics sp
    for (float columns = (float(this->window->getSize().x) * 0.1); columns < (this->window->getSize().x * 0.8); columns += Texture.getSize().x * 1.4) {
        for (float rows = (float(this->window->getSize().y) * 0.2); rows < (this->window->getSize().y * 0.5); rows += Texture.getSize().y * 1.4)
            this->spawnEnemy(columns, rows, enemyTexturePath);

    }

}

