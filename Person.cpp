//
// Created by uauser on 10/2/17.
//

#include "Person.h"

sf::Texture* Person::texture = NULL;

Person::Person(float x, float y, int speed) : Object(x, y, speed) {
    if(!texture){
        texture = new sf::Texture;
        texture->loadFromFile("./person.png");
    }
    gravity = true;

}

std::string Person::getType() {
    return "Person";
}

bool Person::collision(Object &object) {
    return Object::collision(object);
}

Object *Person::clone() {
    return new Person(position.x, position.y, speed);
}
