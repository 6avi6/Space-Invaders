#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "iostream"
#include "Weapon.hpp"

class Enemy {
public:
    Enemy(float xPos, float yPos, const std::string& texturePath);

    void setPosition(float xPos, float yPos);
    sf::Vector2f getPosition() const;

    void draw(sf::RenderWindow* window);
    const sf::Sprite getShape();

    Weapon* enemyWeapon;
private:
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;

   
};

#endif // ENEMY_HPP
