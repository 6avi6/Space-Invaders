#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "iostream"
#include "Weapon.hpp"
class Player {
public:
    Player(int xPos, int yPos, const std::string& playerTexturePath);

    void draw(sf::RenderWindow* window);
    void movePlayer(int direction);

    Weapon* playerWeapon;

    const sf::Sprite getPlayerSprite();
    const int getPlayerHealth();
    void playerHitted();
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
