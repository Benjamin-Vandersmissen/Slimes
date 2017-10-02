//
// Created by uauser on 10/2/17.
//

#ifndef SLIMES_PERSON_H
#define SLIMES_PERSON_H

#include "Object.h"
class Person : public Object{
protected:
    bool controlled = true;
    static sf::Texture* texture;
public:
    Person(float x, float y, int speed);

    std::string getType();

    bool collision(Object& object);

    Object* clone();
};


#endif //SLIMES_PERSON_H
