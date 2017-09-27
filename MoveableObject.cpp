//
// Created by benji on 26.09.17.
//

#include "MoveableObject.h"

MoveableObject::MoveableObject(float x, float y, int speed) : Object(x, y), speed(speed) {}

int MoveableObject::getSpeed() const {
    return speed;
}

bool MoveableObject::isMoveable() {
    return true;
}

bool MoveableObject::hasGravity() {
    return gravity;
}

void MoveableObject::applyImpulse(sf::Vector2f impulse) {
    direction += impulse;
}

const sf::Vector2f &MoveableObject::getDirection() const {
    return direction;
}

void MoveableObject::setImpulse(sf::Vector2f impulse) {
    direction = impulse;
}
