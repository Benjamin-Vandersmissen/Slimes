//
// Created by uauser on 10/2/17.
//

#ifndef SLIMES_PERSON_H
#define SLIMES_PERSON_H

#include "ControllableObject.h"
class Person : public ControllableObject{
protected:
    static sf::Texture* texture;
public:
    Person(float x, float y, int speed);

    std::string getType();

    bool collision(Object& object);

    Object* clone();
};


#endif //SLIMES_PERSON_H
