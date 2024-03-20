#include "Player.hpp"

Player::Player(int xPos, int yPos, const std::string& playerTexturePath) {
    if (!playerTexture.loadFromFile(playerTexturePath)) {
        // Handle error if loading fails
        // For now, let's just print an error message
        std::cout << "PLAYER::PLAYER(int xPos, int yPos, const std::string& playerTexturePath)::'Failed to load player texture!'" << std::endl;
    }

    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(xPos, yPos);
    this->initWeapon();
}

void Player::draw(sf::RenderWindow *window) {
    //collison detection and handling with window frame 
    while (this->playerSprite.getPosition().x + this->playerSprite.getLocalBounds().getSize().x > window->getSize().x)
        this->playerSprite.setPosition(this->playerSprite.getPosition().x - 1, playerSprite.getPosition().y);

    while (this->playerSprite.getPosition().x < 0)
        this->playerSprite.setPosition(this->playerSprite.getPosition().x + 1, playerSprite.getPosition().y);

    window->draw(this->playerSprite);
    this->playerWeapon->draw(window);
}

void Player::movePlayer(int direction=0)
{
        this->playerSprite.setPosition(playerSprite.getPosition().x + 7.f * direction, playerSprite.getPosition().y);

       
}

void Player::initWeapon()
{
    this->playerWeapon = new Weapon("Assets/Texture/bulletTexture.png", -1,15);
}

const sf::Sprite Player::getPlayerSprite()
{
    return this->playerSprite;
}


