//
// Created by uauser on 10/10/17.
//

#ifndef SLIMES_KEY_H
#define SLIMES_KEY_H

#include "Object.h"


class Key : public Object{
private:
    static sf::Texture* texture;

public:
    Key(float x, float y);

    std::string getType();

    Object* clone();
};


#endif //SLIMES_KEY_H
