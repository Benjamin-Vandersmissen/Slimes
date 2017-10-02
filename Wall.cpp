//
// Created by benji on 27.09.17.
//

#include "Wall.h"

sf::Texture* Wall::texture = nullptr;

Wall::Wall(float x, float y) : Object(x, y) {
    if(!texture){
        texture = new sf::Texture;
        texture->loadFromFile("Wall.png");
    }
    _sprite.setTexture(*texture);
}

std::string Wall::getType() {
    return "Wall";
}

Object *Wall::clone() {
    return new Wall(position.x, position.y);
}
