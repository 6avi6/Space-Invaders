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
private:
    
    void initWeapon();

    sf::Sprite playerSprite;
    sf::Texture playerTexture;
    
};

#endif // PLAYER_HPP
