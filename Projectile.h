//
// Created by benji on 29.09.17.
//

#ifndef SLIMES_PROJECTILE_H
#define SLIMES_PROJECTILE_H

#include "Object.h"
#include "ControllableObject.h"
class ControllableObject;
class Projectile : public Object{
private:
    ControllableObject* owner;
    static sf::Texture* texture;
public:
    Projectile(float x, float y, ControllableObject *owner);

    std::string getType();

    Object* clone();

    bool collision(Object& object);
};


#endif //SLIMES_PROJECTILE_H
