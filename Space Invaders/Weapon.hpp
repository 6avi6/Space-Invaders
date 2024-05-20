 #ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "MoveableGraphicalObject.h"

class Weapon : MoveableGraphicalObject {
public:
    Weapon(const std::string& texturePath, int directionofBulletUp,int bulletSpeed);
    void clearMagazine();
    void addNewBullet(float xPostion, float yPostion);
    void draw(sf::RenderWindow* window) override;
    bool collisionDetection(const sf::Sprite& anotherObject) override;
    
   
private:
    void setPosition(float& x, float& y) override;
    const sf::Sprite& getShape() override;
    void move(float& x, float& y) override;
    int directionofBulletUp;//if it s true bullets fly up if false bullets fly down
    int bulletSpeed;
    
    
    sf::Texture bulletsTexture;
    std::vector<std::shared_ptr<sf::Sprite>> bullets;

};

#endif // WEAPON_HPP
