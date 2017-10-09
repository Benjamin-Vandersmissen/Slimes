//
// Created by benji on 26.09.17.
//

#include <iostream>
#include "Slime.h"

sf::Texture* Slime::texture = nullptr;

Slime::Slime(float x, float y, int speed) : ControllableObject(x, y, speed)
{
    if(!texture){
        texture = new sf::Texture;
        texture->loadFromFile("./slime.png");
    }
    m_Gravity = true;
    m_Sprite.setTexture(*texture);
}

std::string Slime::getType() {
    return "Slime";
}

bool Slime::collision(Object &object) {
    bool retValue = ControllableObject::collision(object);
    if (!wouldCollide(object)){
        //Collision with another slime => slimes will pass through each other
        return false;
    }
    else if (object.getType() == "Wall"){
        if (retValue){
            //Bounce back from wall
            if(collisionLeft(object) || collisionRight(object))
                m_Direction.x = (std::abs(m_Direction.x) > 1) ? -m_Direction.x / 5 : 0;
            if (collisionDown(object) || collisionUp(object))
                m_Direction.y = (std::abs(m_Direction.y) > 1) ? -m_Direction.y / 5 : 0;
        }
        return retValue;
    }
    else{
        return retValue;
    }
}

Object *Slime::clone() {
    return new Slime(m_Position.x, m_Position.y, m_Speed);
}

