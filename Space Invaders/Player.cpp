#include "Player.hpp"

Player::Player(int xPos, int yPos, const std::string& playerTexturePath):
playerHealth(5)
{
    if (!this->playerTexture.loadFromFile(playerTexturePath)) {
        // Handle error if loading fails
        // For now, let's just print an error message
        std::cout << "PLAYER::PLAYER(int xPos, int yPos, const std::string& playerTexturePath)::'Failed to load player texture!'" << std::endl;
    }

    this->playerSprite.setTexture(this->playerTexture);
    
    this->playerSprite.setPosition(xPos- (this->playerTexture.getSize().x/2), yPos);
    
    this->initWeapon();

    if (!this->healthBarTexture.loadFromFile("Assets/Texture/heartTexture.png")) {
        // Handle error if loading fails
        // For now, let's just print an error message
        std::cout << "PLAYER::PLAYER(int xPos, int yPos, const std::string& playerTexturePath)::'Failed to load heart texture!'" << std::endl;
    }
    this->healthBar.setTexture(this->healthBarTexture);
    this->healthBar.scale(3, 3);
    this->healthBar.setOrigin(this->healthBar.getLocalBounds().getSize().x, 0);
}

void Player::draw(sf::RenderWindow *window) {
    //collison detection and handling with window frame 
    //right barrier
    while (this->playerSprite.getPosition().x + this->playerSprite.getLocalBounds().getSize().x > window->getSize().x*0.9)
        this->playerSprite.setPosition(this->playerSprite.getPosition().x - 1, playerSprite.getPosition().y);
    //left barrier
    while (this->playerSprite.getPosition().x < window->getSize().x * 0.1)
        this->playerSprite.setPosition(this->playerSprite.getPosition().x + 1, playerSprite.getPosition().y);

    window->draw(this->playerSprite);
    
    this->playerWeapon->draw(window);
    this->drawHealthBar(window);
}

void Player::movePlayer(int direction=0)
{
        this->playerSprite.setPosition(playerSprite.getPosition().x + 7.f * direction, playerSprite.getPosition().y);

       
}

void Player::initWeapon()
{
    this->playerWeapon = new Weapon("Assets/Texture/bulletTexture.png", -1,8);
}

void Player::drawHealthBar(sf::RenderWindow* window)
{   
    sf::Vector2f healthBarPlacment = sf::Vector2f(window->getSize().x-30.f, 40.f);
    this->healthBar.setPosition(healthBarPlacment.x, healthBarPlacment.y);
    for (int i = 0; i < this->getPlayerHealth(); i++) {
        window->draw(this->healthBar);
        healthBarPlacment.x = healthBarPlacment.x-3* this->healthBar.getLocalBounds().getSize().x;
        this->healthBar.setPosition(healthBarPlacment.x, healthBarPlacment.y);

    }
}

const sf::Sprite Player::getPlayerSprite()
{
    return this->playerSprite;
}

void Player::setPostion(int xPos)
{
    this->playerSprite.setPosition(xPos, this->playerSprite.getPosition().y);
}

const int Player::getPlayerHealth()
{
    return this->playerHealth;
}

void Player::playerHitted()
{
    --this->playerHealth;
}


