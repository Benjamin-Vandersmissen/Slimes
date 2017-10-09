//
// Created by benji on 29.09.17.
//

#include <iostream>
#include "Projectile.h"

sf::Texture* Projectile::texture = nullptr;

Projectile::Projectile(float x, float y, ControllableObject *owner) : Object(x, y, 0), owner(owner) {
    if(!texture){
        texture = new sf::Texture;
        texture->loadFromFile("projectile.png");
    }
    gravity = true;
    completeInit(texture);
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
        std::vector<std::string> objectNames = {"Slime", "Person", "ClimbSlime", "WallSlime"};
        if(std::find(objectNames.begin(), objectNames.end(), object.getType()) != objectNames.end()){
            if(owner->isControlled()){
                ControllableObject* obj = (ControllableObject*) &object;
                obj->toggleControlled();
                if(window->getView()->followedObject() == owner){
                    window->getView()->followObject(obj);
                }
                owner->toggleControlled();
                if(owner->getType() == "WallSlime") {
                    std::vector<Object *> objects = window->objectsAt(owner->bounds());
                    if (objects.size() == 1 && objects[0] == owner) {
                        owner->markForDeletion();
                        window->addObject(new Wall(owner->getPosition().x, owner->getPosition().y));
                    }
                }
            }
        }
        markForDeletion();
    }
    return retValue;
}
