//
// Created by uauser on 10/10/17.
//

#include "Key.h"

sf::Texture* Key::texture = nullptr;

Key::Key(float x, float y) : Object(x, y) {
    depth = 7;
    if(!texture){
        texture = new sf::Texture();
        texture->loadFromFile("./tiles.png", sf::IntRect(3456,576,64,64));
    }
    completeInit(texture);
}

std::string Key::getType() {
    return "Key";
}

Object *Key::clone() {
    return new Key(m_worldPosition.x,m_worldPosition.y);
}
