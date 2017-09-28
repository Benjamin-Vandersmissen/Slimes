//
// Created by benji on 26.09.17.
//

#ifndef SLIMES_WINDOW_H
#define SLIMES_WINDOW_H
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "MoveableObject.h"
#include "Room.h"

class Window {
private:
    sf::RenderWindow* window;
    std::vector<Object*> objects;
    MoveableObject* controlledObject;
    float gravity = 0.3;
public:
    Window(unsigned int w, unsigned int h);

    void loop();

    /**
     * Will try to move an object to a specified location
     * If there is already another object there, it will not move the object and instead return the colliding object
     * */
    Object* moveObject(Object* object, float x, float y);

    Object* moveObjectRel(Object* object, float x, float y);

    Object* moveObjectTick(MoveableObject* object);

    Object* objectAt(sf::Vector2f position);

    void loadRoom(Room &room);
};


#endif //SLIMES_WINDOW_H
