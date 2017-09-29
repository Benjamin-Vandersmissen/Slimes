//
// Created by benji on 29.09.17.
//

#ifndef SLIMES_PROJECTILE_H
#define SLIMES_PROJECTILE_H

#include "MoveableObject.h"

class Projectile : public MoveableObject{
private:
    Object* owner;
    static sf::Texture* texture;
public:
    Projectile(float x, float y, Object* owner);

    std::string getType();

    Object* clone();

    bool collision(Object& object);
};


#endif //SLIMES_PROJECTILE_H
