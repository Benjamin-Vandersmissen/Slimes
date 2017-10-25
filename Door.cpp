//
// Created by uauser on 10/11/17.
//

#include <iostream>
#include "Door.h"

sf::Texture* Door::lockedTexture = nullptr;

sf::Texture* Door::unlockedTexture = nullptr;

Door::Door(float x, float y) : Object(x, y) {
    depth = -10;
    if(!lockedTexture){
        unlockedTexture = new sf::Texture();
        unlockedTexture->loadFromFile("./tiles.png",sf::IntRect(448,1408,64,64));
        lockedTexture = new sf::Texture();
        lockedTexture->loadFromFile("./tiles.png", sf::IntRect(384,1408,64,64));
    }
    completeInit(lockedTexture);
}

std::string Door::getType() {
    return "Door";
}

Object *Door::clone() {
    return new Door(m_worldPosition.x ,m_worldPosition.y, m_ID);
}

unsigned int Door::getID() const {
    return m_ID;
}

void Door::setID(unsigned int ID) {
    m_ID = ID;
}

Door *Door::findMatchingDoor() {
    for(Object* object : window->getObjects()){
        if(object->getType() == "Door"){
            Door* door = reinterpret_cast<Door*>(object);
            if(door->getID() == m_ID && door != this){
                return door;
            }
        }
    }
    return nullptr;
}

Door::Door(float x, float y, unsigned int ID) : Object(x,y), m_ID(ID){
    completeInit(lockedTexture);
}

bool Door::isLocked() const {
    return locked;
}

void Door::unlock() {
    locked = false;
    completeInit(unlockedTexture);
    Door* deur = findMatchingDoor();
    findMatchingDoor()->locked = false;
    findMatchingDoor()->completeInit(unlockedTexture);
}
