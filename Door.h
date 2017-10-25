//
// Created by uauser on 10/11/17.
//

#ifndef SLIMES_DOOR_H
#define SLIMES_DOOR_H

#include "Object.h"


class Door : public Object{
private:
    static sf::Texture* lockedTexture;

    static sf::Texture* unlockedTexture;

    bool locked = true;

    unsigned int m_ID;
public:
    Door(float x, float y);

    Door(float x, float y, unsigned int ID);

    std::string getType();

    Object* clone();

    unsigned int getID() const;

    void setID(unsigned int ID);

    Door* findMatchingDoor();

    bool isLocked() const;

    void unlock();
};


#endif //SLIMES_DOOR_H
