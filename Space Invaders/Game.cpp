#include "Game.hpp"

Game::Game(sf::RenderWindow *window) : window(window), isRunning(true) {
    this->enemyTexturePath = "Assets/Texture/enemyTexture.png";
    this->initPlayer("Assets/Texture/playerTexture.png");
    //this->setEnemies();
    this->clock = 0;
    this->enemyReload = 57;
    this->playerReload = 10;
    this->playerFired = false;
    this->playerCounterReload = 0;
    this->initFonts();
    
    this->level = 0;
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


    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this->playerFired == false) {
            this->player->playerWeapon->addNewBullet(this->player->getPlayerSprite().getPosition().x + (this->player->getPlayerSprite().getLocalBounds().getSize().x / 2) - 2, this->player->getPlayerSprite().getPosition().y);
            this->playerFired = true;

        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->movePlayer(1);


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->player->movePlayer(-1);

}

void Game::update() {
    // Update game logic here
}

void supportLine(sf::RenderWindow *window){
    // Create a line for the y-axis
    sf::VertexArray yAxisLine(sf::Lines, 2);
    yAxisLine[0].position = sf::Vector2f(window->getSize().x / 2, 0);    // Start of line
    yAxisLine[1].position = sf::Vector2f(window->getSize().x / 2, window->getSize().y); // End of line
    yAxisLine[0].color = sf::Color::Red;
    yAxisLine[1].color = sf::Color::Red;

    sf::VertexArray border1AxisLine(sf::Lines, 2);
    border1AxisLine[0].position = sf::Vector2f(window->getSize().x * 0.1, 0);    // Start of line
    border1AxisLine[1].position = sf::Vector2f(window->getSize().x * 0.1, window->getSize().y); // End of line
    border1AxisLine[0].color = sf::Color::White;
    border1AxisLine[1].color = sf::Color::White;

    sf::VertexArray border2AxisLine(sf::Lines, 2);
    border2AxisLine[0].position = sf::Vector2f(window->getSize().x * 0.9, 0);    // Start of line
    border2AxisLine[1].position = sf::Vector2f(window->getSize().x * 0.9, window->getSize().y); // End of line
    border2AxisLine[0].color = sf::Color::White;
    border2AxisLine[1].color = sf::Color::White;

    // Create a line for the x-axis
    sf::VertexArray xAxisLine(sf::Lines, 2);
    xAxisLine[0].position = sf::Vector2f(0, window->getSize().y / 2);    // Start of line
    xAxisLine[1].position = sf::Vector2f(window->getSize().x, window->getSize().y / 2); // End of line
    xAxisLine[0].color = sf::Color::Blue;
    xAxisLine[1].color = sf::Color::Blue;
    window->draw(yAxisLine);
    window->draw(xAxisLine);
    window->draw(border2AxisLine);
    window->draw(border1AxisLine);
}

void Game::render() {
    

   

    window->clear();
    // Drawn game

    if (this->enemies.empty()) {
        
        this->intLevel();
    }




    //Drawing enemies
    for (const auto& enemy : enemies) {
        enemy->draw(this->window);
    }
    

    this->checkAndHandleEnemyCollison();
    this->checkIfPlayerIsHit();
    this->checkIfEnemyHittedRockWall();
    this->randomEnemyShoot();

   
    if (this->clock < 61)
        this->clock++;
    else
        this->clock = 0;

    if (this->playerFired) {
        this->playerCounterReload++;
        
    }

    if (this->playerCounterReload > this->playerReload) {
        this->playerFired = false;
        this->playerCounterReload = 0;
    }
    //Drawing player
    this->player->draw(this->window);

    this->window->draw(this->scoreOfPlayer);
    this->drawRockWalls();

    //supportLine(this->window);

    window->display();
}

void Game::intLevel()
{
    this->level++;
    this->enemyReload -= 2;
    //std::cout <<"Level: "<< this->level << "Reload: "<<this->enemyReload << std::endl;
    this->player->playerWeapon->clearMagazine();

    sf::Text levelInfo;
    levelInfo.setFont(this->fontslkscre);
    levelInfo.setFillColor(sf::Color::White);
    levelInfo.setString("Level "+std::to_string(this->level));
    levelInfo.setCharacterSize(40);
    levelInfo.setOrigin(levelInfo.getLocalBounds().getSize().x/2, levelInfo.getLocalBounds().getSize().y / 2);
    levelInfo.setPosition(this->window->getSize().x/2, this->window->getSize().y / 2);

    window->clear();
    this->window->draw(levelInfo);
    window->display();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    window->clear();
    this->player->setPostion(this->window->getSize().x/2-(this->player->getPlayerSprite().getLocalBounds().getSize().x/2));
    
    this->initRockWalls();
    this->setEnemies();
}

void Game::initPlayer(std::string texturePath)
{
    player = std::make_shared<Player>(this->window->getSize().x/2, this->window->getSize().y*0.85, texturePath);

}

void Game::spawnEnemy(float xPos, float yPos, const std::string& texturePath) {
    this->enemyNumber++;
    std::shared_ptr<Enemy> newEnemy = std::make_shared<Enemy>(xPos, yPos, texturePath,this->level);
    enemies.push_back(newEnemy);
}

void Game::setEnemies() {
    sf::Texture Texture;
    if (!Texture.loadFromFile(enemyTexturePath)) {
        // Handle error if loading fails
        // For now, let's just print an error message
        std::cout << "ENEMY::ENEMY(float xPos, float yPos, const std::string& texturePath)::'Failed to load enemy texture!'" << std::endl;
    }
    else {
        //setting postion of enemies
        float XsizeOfEnemy = Texture.getSize().x * 1.5;
        int NumberOfEnemeisColumns = (this->window->getSize().x * 0.8) / XsizeOfEnemy;
        float spacingBetweenColumns = ((this->window->getSize().x * 0.8) - (NumberOfEnemeisColumns * XsizeOfEnemy)) / NumberOfEnemeisColumns;

        float YsizeOfEnemy = Texture.getSize().y * 1.5;
        int NumberOfEnemeisRows = (this->window->getSize().y * 0.4) / XsizeOfEnemy;
        float spacingBetweenRows = ((this->window->getSize().y * 0.4) - (NumberOfEnemeisRows * YsizeOfEnemy)) / NumberOfEnemeisRows;


        for (int column = 0; column < NumberOfEnemeisColumns; column++) {
            for (int row = 0; row < NumberOfEnemeisRows; row++) {
                this->spawnEnemy((float(this->window->getSize().x) * 0.1) + column * (XsizeOfEnemy + spacingBetweenColumns), row * (YsizeOfEnemy + spacingBetweenRows) + (float(this->window->getSize().y) * 0.2), enemyTexturePath);
            }

        }

    }

   
}

void Game::randomEnemyShoot()
{
    if (this->enemyReload < this->clock) {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, this->enemyNumber);
        int rand = distribution(gen);
        if (rand < this->enemies.size())
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

const int Game::getScore()
{
    return this->score;
}

void Game::initFonts()
{
    score = 0;
    if (!fontslkscre.loadFromFile("Assets/Fonts/slkscre.ttf")) { // Replace "arial.ttf" with the path to your font file
        // Error handling: Failed to load font
        std::cout << "GAME::INITFONTS()::'font slkscre loading failure'" << std::endl;
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
    this->rockWalls.clear();
        sf::Texture Texture;
        if (!Texture.loadFromFile("Assets/Texture/PlayerWall/wall5Texture.png")) {
        // Handle error if loading fails
        // For now, let's just print an error message
        std::cout << "GAME::INITROCKWALLS()::'Failed to load wall texture!'" << std::endl;
    }
        else {
            int number_of_rocks = 5;
            float spacing = ((this->window->getSize().x * 0.8) - (Texture.getSize().x * 1.5 * number_of_rocks)) / number_of_rocks;
            for (int i = 0; i < number_of_rocks; i++) {
                std::shared_ptr<RockWall> newRock = std::make_shared<RockWall>((this->window->getSize().x * 0.1) + i * (spacing + (Texture.getSize().x * 2)), this->window->getSize().y * 0.7);
                this->rockWalls.push_back(newRock);
            }
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
