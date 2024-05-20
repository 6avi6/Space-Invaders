#include "Game.hpp"

Game::Game(sf::RenderWindow *window) : window(window), isRunning(true),sideToMoveEnemies(1) {
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        float tempx = 7.0f;
        float tempy = 0.0f;
        this->player->move(tempx, tempy);
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        float tempx = -7.0f;
        float tempy = 0.0f;
        this->player->move(tempx,tempy);
    }
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
 

    if (this->enemies.empty()) {
        
        this->intLevel();
    }




    //Drawing enemies
    /*
    for (const auto& enemy : enemies) {
        enemy->draw(this->window);
    }
    */

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
    //this->player->draw(this->window);

    
    //this->drawRockWalls();

    //supportLine(this->window);
    this->draw();
    setMoveEnemiesColumn();
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
    float tempy = 0;
    float tempx=((this->window->getSize().x / 2) - (this->player->getPlayerSprite().getLocalBounds().getSize().x / 2));
    this->player->setPosition(tempx,tempy);
    
    this->initRockWalls();
    this->setEnemies();
    graphicalObjects.push_back(this->player);
}

void Game::draw()
{
    this->window->draw(this->scoreOfPlayer);
    for (const auto& object : graphicalObjects) {
        object->draw(window); // Call the draw method on each GraphicalObject
    }
}

void Game::initPlayer(std::string texturePath)
{
    player = std::make_shared<Player>(this->window->getSize().x/2, this->window->getSize().y*0.85, texturePath);

}

void Game::spawnEnemy(float xPos, float yPos, const std::string& texturePath) {
    this->enemyNumber++;
    std::shared_ptr<Enemy> newEnemy = std::make_shared<Enemy>(xPos, yPos, texturePath,this->level);
    enemies.push_back(newEnemy);
    graphicalObjects.push_back(newEnemy);
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
        float XsizeOfEnemy = Texture.getSize().x * 2;
        int NumberOfEnemeisColumns = (this->window->getSize().x * 0.8) / XsizeOfEnemy;
        float spacingBetweenColumns = ((this->window->getSize().x * 0.8) - (NumberOfEnemeisColumns * XsizeOfEnemy)) / NumberOfEnemeisColumns;

        float YsizeOfEnemy = Texture.getSize().y * 2;
        int NumberOfEnemeisRows = (this->window->getSize().y * 0.4) / XsizeOfEnemy;
        float spacingBetweenRows = ((this->window->getSize().y * 0.4) - (NumberOfEnemeisRows * YsizeOfEnemy)) / NumberOfEnemeisRows;


        for (int column = 0; column < NumberOfEnemeisColumns; column++) {
            for (int row = 0; row < NumberOfEnemeisRows; row++) {
                this->spawnEnemy((float(this->window->getSize().x) * 0.1) + column * (XsizeOfEnemy + spacingBetweenColumns), row * (YsizeOfEnemy + spacingBetweenRows) + (float(this->window->getSize().y) * 0.2), enemyTexturePath);
            }

        }

    }

   
}

void Game::setMoveEnemiesColumn() {
    // Random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Define the range for the random number
    std::uniform_int_distribution<> dis(1, 40-2*level);
    int randomNumber = dis(gen);
    //std::cout << sideToMoveEnemies << "Random number between 1 and 1000: " << randomNumber << std::endl;
    
    // Initialize variables
    bool isAnyEnemyOutsideXBounds = false;
    float moveX = 1.5 * sideToMoveEnemies;
    float moveY = 0;
    if (randomNumber == 30)
        moveY = 10;

    // Loop through enemies
    for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it) {
        // Check if the enemy is within the X bounds of the window
        bool isEnemyWithinXBounds = ((*it)->getPosition().x + moveX > 0) &&
                                    ((*it)->getPosition().x + (*it)->getShape().getGlobalBounds().width + moveX < window->getSize().x);

        // Move the enemy if it's within the X bounds
        if (isEnemyWithinXBounds) {
            (*it)->move(moveX, moveY);
        } else {
            isAnyEnemyOutsideXBounds = true;
        }
    }

    // Update movement direction if any enemy is outside the X bounds
    if (isAnyEnemyOutsideXBounds) {
        sideToMoveEnemies *= -1;
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
        if (this->player->playerWeapon->collisionDetection((*it)->getShape())) {
            score++;
            this->scoreOfPlayer.setString("Score: " + std::to_string(this->score));

            auto enemyPtr = *it; // Save the shared_ptr for removal

            // Remove the enemy from both vectors
            auto removeFromVector = [](auto& vec, const auto& item) {
                vec.erase(std::remove(vec.begin(), vec.end(), item), vec.end());
                };
            removeFromVector(graphicalObjects, enemyPtr);
            removeFromVector(enemies, enemyPtr);
            //it = this->enemies.erase(it);
        }
        else {
            ++it;
        }
    }
    for (auto it = this->enemies.begin(); it != this->enemies.end();) {
        if ((*it)->getPosition().y+ (*it)->getShape().getGlobalBounds().getSize().y>= window->getSize().y) {
            this->player->playerHitted();

            if (this->player->getPlayerHealth() <= 0)
            {
                //std::cout << "Game Over" << std::endl;
                this->isRunning = false;
            }
            auto enemyPtr = *it; // Save the shared_ptr for removal

            // Remove the enemy from both vectors
            auto removeFromVector = [](auto& vec, const auto& item) {
                vec.erase(std::remove(vec.begin(), vec.end(), item), vec.end());
                };
            removeFromVector(graphicalObjects, enemyPtr);
            removeFromVector(enemies, enemyPtr);
        }
        else {
            ++it;
        }
    }


}

void Game::checkIfPlayerIsHit() {

    for (auto it = this->enemies.begin(); it != this->enemies.end();) {

        if ((*it)->enemyWeapon->collisionDetection((this->player->getPlayerSprite())) ||
            (*it)->getShape().getGlobalBounds().intersects(this->player->getPlayerSprite().getGlobalBounds()))
        {
            this->player->playerHitted();

            if (this->player->getPlayerHealth() <= 0)
            {
                //std::cout << "Game Over" << std::endl;
                this->isRunning = false;
            }
            auto enemyPtr = *it; // Save the shared_ptr for removal

            // Remove the enemy from both vectors
            auto removeFromVector = [](auto& vec, const auto& item) {
                vec.erase(std::remove(vec.begin(), vec.end(), item), vec.end());
                };
            removeFromVector(graphicalObjects, enemyPtr);
            removeFromVector(enemies, enemyPtr);
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
                graphicalObjects.push_back(newRock);
                this->rockWalls.push_back(newRock);
                
            }
        }
}

void Game::drawRockWalls()
{
        for (const auto& rock : this->rockWalls) {
            rock->draw(window);
        }
   
}

void Game::checkIfEnemyHittedRockWall() {
    for (auto it = this->enemies.begin(); it != this->enemies.end(); ) {
        bool collisionDetected = false; // Flag to track if a collision was detected
        for (auto rock = this->rockWalls.begin(); rock != this->rockWalls.end(); ++rock) {
            if ((*it)->getShape().getGlobalBounds().intersects((*rock)->getShape().getGlobalBounds())) {
                // Collision detected
                collisionDetected = true;

                auto enemyPtr = *it; // Save the shared_ptr for removal

                // Remove the enemy from both vectors
                auto removeFromVector = [](auto& vec, const auto& item) {
                    vec.erase(std::remove(vec.begin(), vec.end(), item), vec.end());
                    };
                removeFromVector(graphicalObjects, enemyPtr);
                removeFromVector(enemies, enemyPtr);
                (*rock)->hitted();
                if ((*rock)->getHealt() == 1) {
                    auto rockWallPtr = *rock;  // Save the shared_ptr for removal

                    // Remove rock wall from both vectors
                    auto removeFromVector = [](auto& vec, const auto& item) {
                        vec.erase(std::remove(vec.begin(), vec.end(), item), vec.end());
                        };
                    removeFromVector(graphicalObjects, rockWallPtr);
                    removeFromVector(rockWalls, rockWallPtr);

                    // Update iterator after removal
                    //rock = this->rockWalls.erase(rock);


                }
                else {
                    ++rock;
                }
                break; // Break out of the inner loop since the enemy has been removed
            }
        }
        if (!collisionDetected) {
            // No collision detected, move to the next enemy
            ++it;
        }
    }


    for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it) {
        for (auto rock = this->rockWalls.begin(); rock != this->rockWalls.end(); ) {
            if ((*it)->enemyWeapon->collisionDetection((*rock)->getShape())) {
                (*rock)->hitted();
                if ((*rock)->getHealt() == 1) {
                    auto rockWallPtr = *rock;  // Save the shared_ptr for removal

                    // Remove rock wall from both vectors
                    auto removeFromVector = [](auto& vec, const auto& item) {
                        vec.erase(std::remove(vec.begin(), vec.end(), item), vec.end());
                        };
                    removeFromVector(graphicalObjects, rockWallPtr);
                    removeFromVector(rockWalls, rockWallPtr);

                    // Update iterator after removal
                    //rock = this->rockWalls.erase(rock);


                }
                else {
                    ++rock;
                }
            }
            else {
                ++rock;
            }
        }

    }
}