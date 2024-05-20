#ifndef ROCKWALL_H
#define ROCKWALL_H

#include <SFML/Graphics.hpp>
#include "iostream"
#include "GraphicalObject.h"
class RockWall : public GraphicalObject {
public:
	RockWall(int xPostion, int yPostion);
	void hitted();
	const int getHealt();
	void setPosition(float& x, float& y) override;
	void draw(sf::RenderWindow* window) override;
	const sf::Sprite& getShape() override;
private:
	int health;
	

	sf::Texture rockTexture;
	sf::Sprite rock;
	void initTexture();


};


#endif // !ROCKWALL_H
