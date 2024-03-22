#include "Game.hpp"

Game::Game(sf::RenderWindow *window) : window(window), isRunning(true) {
    this->enemyTexturePath = "Assets/Texture/enemyTexture.png";
    this->initPlayer("Assets/Texture/playerTexture.png");
    this->setEnemies();
    this->clock = 0;
    this->enemyReload = 60;
    
    this->initFonts();
    this->initRockWalls();
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
        if (event.type == sf::Event::Closed) {
            this->isRunning = false;
            this->window->close();
        }
        if (event.key.code == sf::Keyboard::Escape)
            this->isRunning = false;

    }


    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
       this->player->playerWeapon->addNewBullet(this->player->getPlayerSprite().getPosition().x+(this->player->getPlayerSprite().getLocalBounds().getSize().x/2)-2, this->player->getPlayerSprite().getPosition().y);



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
        enemy->draw(this->window);
    }
    

    this->checkAndHandleEnemyCollison();
    this->checkIfPlayerIsHit();
    this->checkIfEnemyHittedRockWall();
    this->randomEnemyShoot();

    if (this->enemies.empty())
        this->isRunning = false;

    if (this->clock < 61)
        this->clock++;
    else
        this->clock = 0;
    //Drawing player
    this->player->draw(this->window);

    this->window->draw(this->scoreOfPlayer);
    this->drawRockWalls();
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

void Game::randomEnemyShoot()
{
    if (this->enemyReload < this->clock) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, this->enemies.size() - 1);
        int rand = distribution(gen);
        this->enemies[rand]->enemyWeapon->addNewBullet(this->enemies[rand]->getPosition().x+ (this->enemies[rand]->getShape().getGlobalBounds().getSize().x/2), this->enemies[rand]->getPosition().y);
    }
}


void Game::checkAndHandleEnemyCollison() {

    for (auto it = this->enemies.begin(); it != this->enemies.end();) {

        if (this->player->playerWeapon->detectCollison((*it)->getShape()))
        {
            score++;
            this->scoreOfPlayer.setString("Score: " + std::to_string(this->score));
            it=this->enemies.erase(it);
        }
        else
        ++it;
        }


}

void Game::checkIfPlayerIsHit() {

    for (auto it = this->enemies.begin(); it != this->enemies.end();) {

        if ((*it)->enemyWeapon->detectCollison((this->player->getPlayerSprite())))
        {
            this->player->playerHitted();

            if (this->player->getPlayerHealth() <= 0)
            {
                std::cout << "You lose" << std::endl;
                this->isRunning = false;
            }
        }
       
        else
            ++it;
    }


}

void Game::initFonts()
{
    score = 0;
    if (!fontslkscre.loadFromFile("Assets/Fonts/slkscre.ttf")) { // Replace "arial.ttf" with the path to your font file
        // Error handling: Failed to load font
        std::cout << "GAME::INITFONTS()::'font SYNNova loading failure'" << std::endl;
    }

    // Use the font in your text
    this->scoreOfPlayer.setFont(fontslkscre);
    this->scoreOfPlayer.setCharacterSize(24);
    this->scoreOfPlayer.setString("Score: " + std::to_string(this->score));
    scoreOfPlayer.setPosition(30, 30);
    scoreOfPlayer.setFillColor(sf::Color::White);
}

void Game::initRockWalls()
{
    float spacing = (this->window->getSize().x - 200.f) / 5;
    for (int i = 0; i < 5; i++) {
        std::shared_ptr<RockWall> newRock = std::make_shared<RockWall>(100.f+i*spacing, this->window->getSize().y * 0.75);
        this->rockWalls.push_back(newRock);
    }
    
}

void Game::drawRockWalls()
{
        for (const auto& rock : this->rockWalls) {
            rock->render(window);
        }
   
}

void Game::checkIfEnemyHittedRockWall()
{

    for (auto it = this->enemies.begin(); it != this->enemies.end();) {

        for (auto rock = this->rockWalls.begin(); rock != this->rockWalls.end();) {

            if ((*it)->enemyWeapon->detectCollison((*rock)->getShape()))
            {
                (*rock)->hitted();
                if ((*rock)->getHealt() == 1) {
                    rock = this->rockWalls.erase(rock);
                }
            }
            else
                ++rock;
        }
        ++it;
    }

}
