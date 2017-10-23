//
// Created by uauser on 10/2/17.
//

#include <iostream>
#include "Person.h"
#include "Door.h"

sf::Texture* Person::texture = NULL;

Person::Person(float x, float y, int speed) : ControllableObject(x, y, speed) {
    depth = 10;
    controlled = true;
    maxNrJumps = 1;
    nrJumps = maxNrJumps;
    if(!texture){
        texture = new sf::Texture;
        texture->loadFromFile("./player.png");
    }
    completeInit(texture);
    m_Gravity = true;
    m_Sprite.setColor({255,255,255});
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

void Person::keyPressed(sf::Keyboard::Key key) {
    ControllableObject::keyPressed(key);
    if(key == sf::Keyboard::Up){
        std::vector<Object*> objects = window->objectsAt(m_Sprite.getGlobalBounds());
        Door* door = nullptr;
        for(Object* object : objects){
            if(object->getType() == "Door"){
                door = reinterpret_cast<Door*>(object);
            }
        }
        if(door != nullptr){
            Door* secondDoor = door->findMatchingDoor();
            if(secondDoor != nullptr){
                this->move(secondDoor->getPosition().x, secondDoor->getPosition().y);
            }
        }
    }
}
