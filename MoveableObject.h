//
// Created by benji on 26.09.17.
//

#ifndef SLIMES_CONTROLABLEOBJECT_H
#define SLIMES_CONTROLABLEOBJECT_H
#include "Object.h"

class MoveableObject : public Object{
protected:
    int speed;
public:
    MoveableObject(float x, float y, int speed);

    int getSpeed() const;
};


#endif //SLIMES_CONTROLABLEOBJECT_H
