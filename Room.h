//
// Created by benji on 28.09.17.
//

#ifndef SLIMES_ROOM_H
#define SLIMES_ROOM_H

#include <map>
#include "Object.h"

class Object;

class Room {
private:
    unsigned int width, height, rastersize;

    std::map<int, Object*> allocatedObjects;

    std::vector<Object*> objects;
public:
    Room(unsigned int width, unsigned int height, unsigned int rastersize = 64);

    unsigned long long int allocateObject(Object *object);

    void populateObjects(int* array);

    const std::vector<Object *> getObjects() const;

    sf::Vector2u size() const;
};


#endif //SLIMES_ROOM_H
