//
// Created by benji on 02.10.17.
//

#ifndef SLIMES_CLIMBSLIME_H
#define SLIMES_CLIMBSLIME_H


#include "Slime.h"

class ClimbSlime : public Slime
{
protected:
    static sf::Texture* texture;
public:
    ClimbSlime(float x, float y, int speed);

    void keyPressed(sf::Keyboard::Key key);

    void keyboard();

    Object* clone();

    std::string getType();
};


#endif //SLIMES_CLIMBSLIME_H
