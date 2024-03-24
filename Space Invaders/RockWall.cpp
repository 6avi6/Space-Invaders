#include "RockWall.hpp"

RockWall::RockWall(int xPostion, int yPostion) :
	health(5)
{
	this->initTexture();
    this->rock.scale(2, 2);
    this->rock.setPosition(xPostion,yPostion);
}

void RockWall::hitted()
{
    --this->health;
    this->initTexture();
}

const int RockWall::getHealt()
{
    return this->health;
}

void RockWall::render(sf::RenderWindow* window)
{
    window->draw(this->rock);
}

const sf::Sprite RockWall::getShape()
{
    return this->rock;
}

void RockWall::initTexture()
{
    if (!this->rockTexture.loadFromFile("Assets/Texture/PlayerWall/wall"+ std::to_string(health) + "Texture.png")) {
        // Handle error if loading fails
        // For now, let's just print an error message
        std::cout << "ROCKWALL::INITROCKWALL()::'Failed to load player texture!'" << std::endl;
    }

    this->rock.setTexture(this->rockTexture);
    
   
}


