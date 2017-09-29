//
// Created by benji on 26.09.17.
//

#include <iostream>
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
    if (&object == this)
        return false;
    return (object._sprite.getGlobalBounds().intersects(_sprite.getGlobalBounds()));
}

const sf::Vector2f &Object::getPosition() const {
    return position;
}

bool Object::isMoveable() {
    return false;
}

bool Object::containsPoint(sf::Vector2f point) {
    return _sprite.getGlobalBounds().contains(point);
}

sf::FloatRect Object::bounds() {
    return _sprite.getGlobalBounds();
}

bool Object::collision(Object &object, sf::FloatRect &ret) {
    if(&object == this)
        return false;
    return (object._sprite.getGlobalBounds().intersects(_sprite.getGlobalBounds(), ret));
}

bool Object::collisionRight(Object &object) {
    sf::FloatRect overlap;
    if(collision(object, overlap)){
        bool retValue = overlap.left + overlap.width == _sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width ;
        retValue &= overlap.height > 1;
        return retValue;
    }
    return false;
}

bool Object::collisionLeft(Object &object) {
    sf::FloatRect overlap;
    if(collision(object, overlap)){
        bool retValue = overlap.left == _sprite.getGlobalBounds().left;
        retValue &= overlap.height > 1;
        return retValue;
    }
    return false;
}

bool Object::collisionUp(Object &object) {
    sf::FloatRect overlap;
    if(collision(object, overlap)){
        bool retValue = overlap.top == _sprite.getGlobalBounds().top;
        retValue &= overlap.width > 1;
        return retValue;
    }
    return false;
}

bool Object::collisionDown(Object &object) {
    sf::FloatRect overlap;
    if(collision(object, overlap)){
        bool retValue = overlap.top +overlap.height == _sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height;
        retValue &= overlap.width > 1;
        return retValue;
    }
    return false;}

void Object::keyPressed(sf::Keyboard::Key key) {

}

void Object::keyReleased(sf::Keyboard::Key key) {

}

void Object::keyboard() {

}

void Object::markForDeletion() {
    _delete = true;
}

bool Object::markedForDeletion() {
    return _delete;
}
