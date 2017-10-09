//
// Created by benji on 28.09.17.
//

#ifndef SLIMES_ROOM_H
#define SLIMES_ROOM_H

#include <map>
#include "Object.h"
#include "View.h"

class Object;
class View;

class Room {
private:
    unsigned int width, height, rastersize;

    std::map<int, Object*> allocatedObjects;

    std::vector<Object*> objects;

    std::vector<sf::Sprite*> sprites;

    View* m_View = nullptr;

    View* m_View2 = nullptr;
public:
    Room(unsigned int width, unsigned int height, unsigned int rastersize = 64);

    unsigned long long int allocateObject(Object *object);

    void populateObjects(int* array);

    const std::vector<Object *> getObjects();

    sf::Vector2u size() const;

    void addObject(Object* object);

    void setSprites(std::vector<sf::Sprite*> sprites);

    const std::vector<sf::Sprite *> &getSprites() const;

    void setView(float x, float y, float w, float h);

    void setView(Object* object, float w, float h);

    View *getView() const;
};


#endif //SLIMES_ROOM_H
