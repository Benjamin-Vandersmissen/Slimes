//
// Created by benji on 02.10.17.
//

#ifndef SLIMES_CONTROLLABLEOBJECT_H
#define SLIMES_CONTROLLABLEOBJECT_H
#include "Object.h"
#include "Window.h"
#include "Projectile.h"

class Projectile;
class ControllableObject : public Object{
protected:
    bool controlled = false;
    int facing = 1;
    int maxNrJumps = 2;
    int nrJumps = maxNrJumps;
public:
    ControllableObject(float x, float y, int speed);

    virtual void keyPressed(sf::Keyboard::Key key);

    virtual void keyboard();

    bool isControlled();

    void toggleControlled();

    virtual bool collision(Object& object);

    virtual bool wouldCollide(Object& object);
};


#endif //SLIMES_CONTROLLABLEOBJECT_H
