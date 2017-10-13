//
// Created by uauser on 10/11/17.
//

#include "Door.h"

sf::Texture* Door::texture = nullptr;

Door::Door(float x, float y) : Object(x, y) {
    depth = -10;
    if(!texture){
        texture = new sf::Texture();
        texture->loadFromFile("./tiles.png",sf::IntRect(448,1408,64,64));
    }
    completeInit(texture);
}

std::string Door::getType() {
    return "Door";
}

Object *Door::clone() {
    return new Door(m_Position.x ,m_Position.y);
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
}