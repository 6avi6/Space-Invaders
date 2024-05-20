#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "iostream"
#include "Weapon.hpp"
#include "MoveableGraphicalObject.h"

class Enemy:public MoveableGraphicalObject {
public:

    Enemy(float xPos, float yPos, const std::string& texturePath,int levelBonus);

    void setPosition(float& x, float& y);
    sf::Vector2f getPosition() const;

    //first abstract class
    void draw(sf::RenderWindow* window) override;
    const sf::Sprite& getShape() override;
    //second abstract class
    void move(float& x, float& y) override;

    Weapon* enemyWeapon;
private:
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;

   
};

#endif // ENEMY_HPP
