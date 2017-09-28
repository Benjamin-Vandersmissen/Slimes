//
// Created by benji on 27.09.17.
//

#ifndef SLIMES_WALL_H
#define SLIMES_WALL_H

#include "Object.h"

class Wall : public Object{
private:
    static sf::Texture* texture;
public:
    Wall(float x, float y);

    std::string getType();

    Object* clone();
};


#endif //SLIMES_WALL_H
