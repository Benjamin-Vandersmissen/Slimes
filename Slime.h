//
// Created by benji on 26.09.17.
//

#ifndef SLIMES_SLIME_H
#define SLIMES_SLIME_H

#include "SFML/Window.hpp"
#include "ControllableObject.h"
#include "Projectile.h"

class Slime : public ControllableObject
{
private:
    static sf::Texture* texture;
public:

    Slime(float x, float y, int speed);

    virtual std::string getType();

    bool collision(Object& object);

    Object* clone();

};


#endif //SLIMES_SLIME_H
