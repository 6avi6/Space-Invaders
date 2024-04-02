 #ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

class Weapon {
public:
    Weapon(const std::string& texturePath, int directionofBulletUp,int bulletSpeed);
    void clearMagazine();
    void addNewBullet(float xPostion, float yPostion);
    void draw(sf::RenderWindow* window);
    bool detectCollison(sf::Sprite target);
    
private:
    int directionofBulletUp;//if it s true bullets fly up if false bullets fly down
    int bulletSpeed;
    
    
    sf::Texture bulletsTexture;
    std::vector<std::shared_ptr<sf::Sprite>> bullets;

};

#endif // WEAPON_HPP
