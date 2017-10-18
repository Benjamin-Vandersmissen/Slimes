//
// Created by benji on 28.09.17.
//

#ifndef SLIMES_ROOM_H
#define SLIMES_ROOM_H

#include <map>
#include "Object.h"
#include "View.h"
#include "Tileset.h"

class Object;
class View;

class Room {
private:
    unsigned int width, height, rastersize;

    std::map<int, Object*> allocatedObjects;

    std::vector<Object*> objects;

    std::vector<Tile*> tiles;

    View* m_View = nullptr;
public:
    Room(unsigned int width, unsigned int height, unsigned int rastersize = 64);

    unsigned long long int allocateObject(Object *object);

    void populateObjects(int* array);

    const std::vector<Object *> getObjects();

    sf::Vector2u size() const;

    sf::Vector2f viewSize() const;

    void addObject(Object* object);

    void setTiles(std::vector<Tile *> tiles);

    const std::vector<Tile *> &getTiles() const;

    void setView(float x, float y, float w, float h);

    void setView(Object* object, float w, float h);

    View *getView() const;
};


#endif //SLIMES_ROOM_H
