//
// Created by uauser on 10/11/17.
//

#ifndef SLIMES_DOOR_H
#define SLIMES_DOOR_H

#include "Object.h"


class Door : public Object{
private:
    static sf::Texture* texture;

    unsigned int m_ID;
public:
    Door(float x, float y);

    Door(float x, float y, unsigned int ID);

    std::string getType();

    Object* clone();

    unsigned int getID() const;

    void setID(unsigned int ID);

    Door* findMatchingDoor();
};


#endif //SLIMES_DOOR_H
