#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class GraphicalObject {
    
public:
    virtual ~GraphicalObject() {} // Default virtual destructor

    virtual void draw(sf::RenderWindow* window) = 0; // Method for drawing the object

    virtual void setPosition(float& x, float& y) = 0;

    virtual const sf::Sprite& getShape() = 0; // Method for returning a reference to the sf::Sprite object

};

#endif // GRAPHICALOBJECT_H
