#ifndef ROCKWALL_H
#define ROCKWALL_H

#include <SFML/Graphics.hpp>
#include "iostream"

class RockWall {
public:
	RockWall(int xPostion, int yPostion);
	void hitted();
	const int getHealt();
	void render(sf::RenderWindow* window);
	const sf::Sprite getShape();
private:
	int health;
	

	sf::Texture rockTexture;
	sf::Sprite rock;
	void initTexture();


};


#endif // !ROCKWALL_H
