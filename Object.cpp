//
// Created by benji on 26.09.17.
//

#include <iostream>
#include "Object.h"

void Object::sprite(sf::Sprite sprite){
    this->m_Sprite = sprite;
    this->m_Sprite.setPosition(m_Position);
}

Object::Object(float x, float y) : m_Position({x,y}){

}

Object::Object(float x, float y, int speed) : m_Speed(speed){
    m_Gravity = true;
    move(x,y);
}

void Object::move(float x, float y) {
    m_Position.x = x;
    m_Position.y = y;
    this->m_Sprite.setPosition(x,y);
}

bool Object::collision(sf::FloatRect boundingBox) {
    return m_Sprite.getGlobalBounds().intersects(boundingBox);
}

bool Object::collision(Object &object) {
    if (&object == this)
        return false;
    return collision(object.m_Sprite.getGlobalBounds());
}

const sf::Vector2f &Object::getPosition() const {
    return m_Position;
}

bool Object::containsPoint(sf::Vector2f point) {
    return m_Sprite.getGlobalBounds().contains(point);
}

sf::FloatRect Object::bounds() {
    return m_Sprite.getGlobalBounds();
}

bool Object::collision(Object &object, sf::FloatRect &ret) {
    if(&object == this)
        return false;
    return (object.m_Sprite.getGlobalBounds().intersects(m_Sprite.getGlobalBounds(), ret));
}

bool Object::collisionRight(Object &object) {
    sf::FloatRect overlap;
    if(collision(object, overlap)){
        bool retValue = overlap.left + overlap.width == m_Sprite.getGlobalBounds().left + m_Sprite.getGlobalBounds().width ;
        retValue &= overlap.height > 1;
        return retValue;
    }
    return false;
}

bool Object::collisionLeft(Object &object) {
    sf::FloatRect overlap;
    if(collision(object, overlap)){
        bool retValue = overlap.left == m_Sprite.getGlobalBounds().left;
        retValue &= overlap.height > 1;
        return retValue;
    }
    return false;
}

bool Object::collisionUp(Object &object) {
    sf::FloatRect overlap;
    if(collision(object, overlap)){
        bool retValue = overlap.top == m_Sprite.getGlobalBounds().top;
        retValue &= overlap.width > 1;
        return retValue;
    }
    return false;
}

bool Object::collisionDown(Object &object) {
    sf::FloatRect overlap;
    if(collision(object, overlap)){
        bool retValue = overlap.top +overlap.height == m_Sprite.getGlobalBounds().top + m_Sprite.getGlobalBounds().height;
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

bool Object::hasGravity() {
    return m_Gravity;
}

void Object::applyImpulse(sf::Vector2f impulse) {
    m_Direction += impulse;
}

void Object::setImpulse(sf::Vector2f impulse) {
    m_Direction = impulse;
}

const sf::Vector2f &Object::getDirection() const {
    return m_Direction;
}

Object::Object() {
    m_Position = {0,0};
    m_Speed = 0;
}

void Object::step() {

}

bool Object::wouldCollide(Object &object) {
    return true;
}

sf::FloatRect Object::getSize() {
    return m_Sprite.getLocalBounds();
}

void Object::completeInit(sf::Texture *texture) {
    m_Sprite.setTexture(*texture);
    m_Sprite.setPosition(m_Position.x, m_Position.y);
}

void Object::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_Sprite, states);
}

