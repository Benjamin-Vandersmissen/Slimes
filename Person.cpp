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
    _sprite.setTexture(*texture);
    gravity = true;

}

std::string Person::getType() {
    return "Person";
}

bool Person::collision(Object &object) {
    if(!wouldCollide(object))
        return false;
    bool retValue = ControllableObject::collision(object);
    if(retValue){
        if(Object::collisionDown(object)){
            this->direction.y = 0;
        }
    }
    return retValue;
}

Object *Person::clone() {
    return new Person(position.x, position.y, speed);
}
