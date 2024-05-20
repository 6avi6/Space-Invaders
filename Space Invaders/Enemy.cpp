#include "Enemy.hpp"

Enemy::Enemy(float xPos, float yPos, const std::string& texturePath,int levelBonus) {
    if (!enemyTexture.loadFromFile(texturePath)) {
        // Handle error if loading fails
        // For now, let's just print an error message
        std::cout << "ENEMY::ENEMY(float xPos, float yPos, const std::string& texturePath)::'Failed to load enemy texture!'" << std::endl;
    }

    this->enemySprite.setTexture(enemyTexture);

    this->enemySprite.setPosition(xPos, yPos);
    this->enemySprite.scale(1.5, 1.5);
    this->enemySprite.setOrigin(0,0);

    this->enemyWeapon = new Weapon("Assets/Texture/bulletTexture.png", 1, 2+(1*levelBonus));
}

void Enemy::setPosition(float& x, float& y) {
    enemySprite.setPosition(x, y);
}

sf::Vector2f Enemy::getPosition() const {
    return enemySprite.getPosition();
}

void Enemy::draw(sf::RenderWindow* window) {
    window->draw(enemySprite);
    this->enemyWeapon->draw(window);
}

const sf::Sprite  & Enemy::getShape()
{
    return this->enemySprite;
}

void Enemy::move(float& x, float& y)
{   
    this->enemySprite.setPosition(
        this->enemySprite.getPosition().x + x,
        this->enemySprite.getPosition().y + y);
}
