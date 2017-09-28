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
    sf::Sprite sprite1;
    sprite1.setTexture(*texture);
    sprite(sprite1);
}

std::string Wall::getType() {
    return "Wall";
}