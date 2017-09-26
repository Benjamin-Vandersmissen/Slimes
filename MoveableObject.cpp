//
// Created by benji on 26.09.17.
//

#include "MoveableObject.h"

MoveableObject::MoveableObject(float x, float y, int speed) : Object(x, y), speed(speed) {}

int MoveableObject::getSpeed() const {
    return speed;
}
