//
// Created by benji on 26.09.17.
//

#include "Object.h"

void Object::sprite(sf::Sprite sprite){
    this->_sprite = sprite;
    this->_sprite.setPosition(position);
}

void Object::draw(sf::RenderWindow &window) {
    window.draw(_sprite);
}

Object::Object(float x, float y) : position({x,y}){

}

void Object::move(float x, float y) {
    position.x = x;
    position.y = y;
    this->_sprite.setPosition(x,y);
}

void Object::moveRel(float x, float y) {
    move(position.x + x, position.y+y);
}

bool Object::collision(Object &object) {
    return (object._sprite.getGlobalBounds().intersects(_sprite.getGlobalBounds()));
}

const sf::Vector2f &Object::getPosition() const {
    return position;
}
