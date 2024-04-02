#include "Weapon.hpp"

Weapon::Weapon(const std::string& texturePath, int directionofBulletUp,int bulletSpeed):
    directionofBulletUp(directionofBulletUp), bulletSpeed(bulletSpeed)
{
    if (!bulletsTexture.loadFromFile(texturePath)) {
        // Handle error if loading fails
        
        std::cout << "Failed to load weapon texture!" << std::endl;
        return;
    }

    
    
}

void Weapon::clearMagazine()
{
    this->bullets.clear();
}



void Weapon::addNewBullet(float xPostion, float yPostion)
{
    
        std::shared_ptr<sf::Sprite> bullet = std::make_shared<sf::Sprite>(bulletsTexture);
        bullet->setPosition(xPostion, yPostion);
        this->bullets.push_back(bullet);
    
}

void Weapon::draw(sf::RenderWindow* window) {
    

    for (auto it = bullets.begin(); it != bullets.end();) {
        // Move the sprite
        (*it)->setPosition((*it)->getPosition().x, (*it)->getPosition().y + (this->directionofBulletUp * this->bulletSpeed));

        // Draw the sprite
        window->draw(*(*it));

        // Check if the sprite is outside the window
        if ((*it)->getPosition().x < 0 || (*it)->getPosition().y < 0 ||
            (*it)->getPosition().x > window->getSize().x || (*it)->getPosition().y > window->getSize().y) {
            // Delete the sprite from the vector
            it = bullets.erase(it);
        }
        else {
            // Move to the next sprite
            ++it;
        }
    }
}

bool Weapon::detectCollison(sf::Sprite target)
{
    for (auto it = this->bullets.begin(); it != this->bullets.end();) {

        //if target is shooted
        if ((*it)->getGlobalBounds().intersects(target.getGlobalBounds())) {
            it = this->bullets.erase(it);
            return true;
        }

        ++it;
    }
    return false;

}

