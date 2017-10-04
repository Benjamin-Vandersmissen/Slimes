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
        //TODO: change texture to dedicated texture
        texture->loadFromFile("./slime.png");
    }
    _sprite.setTexture(*texture);
}

Object *WallSlime::clone() {
    return new WallSlime(position.x, position.y, speed);
}

std::string WallSlime::getType() {
    return "WallSlime";
}

