//
// Created by benji on 29.09.17.
//

#include <iostream>
#include "Projectile.h"

sf::Texture* Projectile::texture = nullptr;

Projectile::Projectile(float x, float y, Object* owner) : Object(x, y, 0), owner(owner) {
    if(!texture){
        texture = new sf::Texture;
        texture->loadFromFile("projectile.png");
    }
    gravity = true;

    _sprite.setTexture(*texture);
}

std::string Projectile::getType() {
    return "Projectile";
}

Object *Projectile::clone() {
    return new Projectile(position.x, position.y, owner);
}

bool Projectile::collision(Object &object) {
    if(&object  == owner)
        return false;
    bool retValue = Object::collision(object);
    if(retValue){
        markForDeletion();
    }
    return retValue;
}
