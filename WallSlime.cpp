//
// Created by uauser on 10/4/17.
//

#include "WallSlime.h"

sf::Texture* WallSlime::texture = NULL;

WallSlime::WallSlime(float x, float y, int speed) : Slime(x, y, speed) {
    maxNrJumps = 1;
    nrJumps = 1;
    if(!texture){
        texture = new sf::Texture;
        texture->loadFromFile("./wallSlime.png");
    }
    completeInit(texture);
}

Object *WallSlime::clone() {
    return new WallSlime(m_worldPosition.x, m_worldPosition.y, m_Speed);
}

std::string WallSlime::getType() {
    return "WallSlime";
}

void WallSlime::onSwitchFrom() {
    ControllableObject::onSwitchFrom();
    std::vector<Object *> objects = window->objectsAt(bounds());
    if (objects.size() == 1 && objects[0] == this) {
        markForDeletion();
        window->addObject(new Wall(m_worldPosition.x, m_worldPosition.y));
    }
}

