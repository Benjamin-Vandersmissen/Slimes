//
// Created by benji on 26.09.17.
//

#ifndef SLIMES_CONTROLABLEOBJECT_H
#define SLIMES_CONTROLABLEOBJECT_H
#include "Object.h"

class MoveableObject : public Object{
protected:
    int speed;
    bool gravity = false;
    sf::Vector2f direction = {0,0};
public:
    MoveableObject(float x, float y, int speed);

    bool isMoveable();

    int getSpeed() const;

    bool hasGravity();

    void applyImpulse(sf::Vector2f impulse);

    void setImpulse(sf::Vector2f impulse);

    const sf::Vector2f &getDirection() const;

};


#endif //SLIMES_CONTROLABLEOBJECT_H
