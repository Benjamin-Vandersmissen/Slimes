//
// Created by benji on 26.09.17.
//

#ifndef SLIMES_WINDOW_H
#define SLIMES_WINDOW_H
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Slime.h"

class Window {
private:
    sf::RenderWindow* window;
    std::vector<sf::Texture*> textures;
    std::vector<Object*> objects;
    MoveableObject* controlledObject;
public:
    Window(unsigned int w, unsigned int h);

    void loop();

    /**
     * Will try to move an object to a specified location
     * If there is already another object there, it will not move the object and instead return the colliding object
     * */
    Object* moveObject(Object* object, float x, float y);

    Object* moveObjectRel(Object* object, float x, float y);

    Object* moveObjectDir(MoveableObject* object, unsigned int direction);
};


#endif //SLIMES_WINDOW_H
