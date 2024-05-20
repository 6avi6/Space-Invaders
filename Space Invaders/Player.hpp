#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "iostream"
#include "Weapon.hpp"
#include "MoveableGraphicalObject.h"

class Player : public MoveableGraphicalObject {
public:
    Player(int xPos, int yPos, const std::string& playerTexturePath);

    void draw(sf::RenderWindow* window) override;


    Weapon* playerWeapon;

    const sf::Sprite getPlayerSprite();
    void setPosition(float& x, float& y) override;
    const int getPlayerHealth();
    void playerHitted();

    const sf::Sprite& getShape() override;
    void move(float& x, float& y) override;
private:
    int playerHealth;
    void initWeapon();
    void drawHealthBar(sf::RenderWindow* window);
    sf::Sprite playerSprite;
    sf::Texture playerTexture;

    sf::Sprite healthBar;
    sf::Texture healthBarTexture;
    
};

#endif // PLAYER_HPP
