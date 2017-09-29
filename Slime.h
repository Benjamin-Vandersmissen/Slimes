//
// Created by benji on 26.09.17.
//

#ifndef SLIMES_SLIME_H
#define SLIMES_SLIME_H

#include "SFML/Window.hpp"
#include "MoveableObject.h"
#include "Projectile.h"
#include "Window.h"

class Slime : public MoveableObject
{
private:
    static sf::Texture* texture;
    int facing = 1;
public:

    Slime(float x, float y, int speed);

    virtual std::string getType();

    bool collision(Object& object);

    Object* clone();

    void keyPressed(sf::Keyboard::Key key);

    void keyboard();
};


#endif //SLIMES_SLIME_H
