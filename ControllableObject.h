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
public:
    ControllableObject(int x, int y, int speed);

    void keyPressed(sf::Keyboard::Key key);

    void keyboard();

    bool isControlled();

};


#endif //SLIMES_CONTROLLABLEOBJECT_H
