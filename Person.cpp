//
// Created by uauser on 10/2/17.
//

#include "Person.h"

sf::Texture* Person::texture = NULL;

Person::Person(float x, float y, int speed) : ControllableObject(x, y, speed) {
    controlled = true;
    maxNrJumps = 1;
    nrJumps = maxNrJumps;
    if(!texture){
        texture = new sf::Texture;
        texture->loadFromFile("./player.png");
    }
    completeInit(texture);
    m_Gravity = true;

}

std::string Person::getType() {
    return "Person";
}

bool Person::collision(Object &object) {
    if(!wouldCollide(object))
        return false;
    bool retValue = ControllableObject::collision(object);
    if(retValue){
        if(Object::collisionDown(object) || Object::collisionUp(object)){
            this->m_Direction.y = 0;
        }
    }
    return retValue;
}

Object *Person::clone() {
    return new Person(m_Position.x, m_Position.y, m_Speed);
}
