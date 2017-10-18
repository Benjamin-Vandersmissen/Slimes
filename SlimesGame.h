//
// Created by uauser on 10/18/17.
//

#ifndef SLIMES_SLIMESGAME_H
#define SLIMES_SLIMESGAME_H
#include "Game.h"

class SlimesGame : public Game{
public:
    SlimesGame(unsigned int w, unsigned int h);

    void handleEvent(sf::Event& event);
};


#endif //SLIMES_SLIMESGAME_H
