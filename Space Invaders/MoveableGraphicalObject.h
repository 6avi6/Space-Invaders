#ifndef MOVEABLEGRAPHICALOBJECT_H
#define MOVEABLEGRAPHICALOBJECT_H

#include <SFML/Graphics.hpp>
#include <string>
#include "GraphicalObject.h"

class MoveableGraphicalObject : public GraphicalObject {
public:
    virtual ~MoveableGraphicalObject() {} // Default virtual destructor

    virtual void move(float& x, float& y) = 0; // Method for moving the object
    virtual bool collisionDetection(const sf::Sprite& anotherObject) {
        return false;
    }; // Method for collision detection

};


#endif // !MOVEABLEGRAPHICALOBJECT_H

