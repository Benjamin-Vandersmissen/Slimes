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
    m_Gravity = true;
    completeInit(texture);
}

std::string Projectile::getType() {
    return "Projectile";
}

Object *Projectile::clone() {
    return new Projectile(m_Position.x, m_Position.y, owner);
}

bool Projectile::collision(Object &object) {
    if(&object  == owner)
        return false;
    bool retValue = Object::collision(object);
    if(retValue){
        if(willSwitch(object)){
            ControllableObject* obj = reinterpret_cast<ControllableObject*>(&object);
            owner->toggleControlled();
            owner->onSwitchFrom();

            obj->toggleControlled();
            obj->onSwitchTo();

            window->updateDepth();
            if(window->getView()->followedObject() == owner){
                window->getView()->followObject(obj);
            }
        }
        markForDeletion();
    }
    return retValue;
}

bool Projectile::willSwitch(Object &object) {
    std::vector<std::string> objectNames = {"Slime", "Person", "ClimbSlime", "WallSlime"};
    return std::find(objectNames.begin(), objectNames.end(), object.getType()) != objectNames.end() && owner->isControlled();
}
