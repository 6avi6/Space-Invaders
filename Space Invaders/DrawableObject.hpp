#ifndef DRAWABLEOBJECT_HPP
#define DRAWABLEOBJECT_HPP

#include <SFML/Graphics.hpp>

class DrawableObject {
public:
    virtual ~DrawableObject() {}

    // Pure virtual function to draw the object
    virtual void draw(sf::RenderWindow& window) = 0;

    // Virtual function to initialize the object
    virtual void initDrawableObject() {}
};

#endif // DRAWABLEOBJECT_HPP