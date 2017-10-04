//
// Created by uauser on 10/4/17.
//

#ifndef SLIMES_WALLSLIME_H
#define SLIMES_WALLSLIME_H

#include "Slime.h"

class WallSlime : public Slime{
private:
    static sf::Texture* texture;

public:
    WallSlime(float x, float y, int speed);

    Object* clone();

    std::string getType();

};


#endif //SLIMES_WALLSLIME_H
