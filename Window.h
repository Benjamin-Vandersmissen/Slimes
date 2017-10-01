//
// Created by benji on 26.09.17.
//

#ifndef SLIMES_WINDOW_H
#define SLIMES_WINDOW_H
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Room.h"
#include <algorithm>
class Window {
private:
    sf::RenderWindow* window;
    std::vector<Object*> objects;
    float gravity = 0.3;
public:
    Window(unsigned int w, unsigned int h);

    void loop();

    void addObject(Object* object);

    /**
     * Will try to move an object to a specified location
     * If there is already another object there, it will not move the object and instead return the colliding object
     * */
    Object* moveObject(Object* object, float x, float y);

    Object* moveObjectRel(Object* object, float x, float y);

    Object* moveObjectTick(Object *object);

    Object* objectAt(sf::Vector2f position);

    void loadRoom(Room &room);

    void applyGravity(Object *object);
};


#endif //SLIMES_WINDOW_H
