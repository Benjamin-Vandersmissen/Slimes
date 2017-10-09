//
// Created by benji on 26.09.17.
//

#ifndef SLIMES_WINDOW_H
#define SLIMES_WINDOW_H
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Room.h"
#include <algorithm>
class Object;
class Room;
class View;
class Window : public sf::Drawable{
private:
    sf::RenderWindow* window;
    std::vector<Object*> objects;
    float gravity = 0.3;
    Room* room = NULL;
    std::vector<sf::Sprite*> sprites;
    View* m_View = nullptr;
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

    std::vector<Object*> objectsAt(sf::Vector2f position);

    std::vector<Object*> objectsAt(sf::FloatRect boundingBox);

    void loadRoom(Room &room);

    void applyGravity(Object *object);

    void reloadRoom();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    View* getView();

    void updateView();
};


#endif //SLIMES_WINDOW_H
