//
// Created by uauser on 10/11/17.
//

#ifndef SLIMES_DOOR_H
#define SLIMES_DOOR_H

#include "Object.h"


class Door : public Object{
private:
    static sf::Texture* texture;
public:
    Door(float x, float y);

    std::string getType();

    Object* clone();
};


#endif //SLIMES_DOOR_H
