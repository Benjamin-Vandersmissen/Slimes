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
    return new WallSlime(m_Position.x, m_Position.y, m_Speed);
}

std::string WallSlime::getType() {
    return "WallSlime";
}

