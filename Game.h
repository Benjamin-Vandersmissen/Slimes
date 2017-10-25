//
// Created by benji on 26.09.17.
//

#ifndef SLIMES_GAME_H
#define SLIMES_GAME_H
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Room.h"
#include <algorithm>
class Object;
class Room;
class View;
class Tile;
class Game : public sf::Drawable{
protected:
    sf::RenderWindow* window;
    std::vector<Object*> worldObjects;
    std::vector<Object*> viewObjects;
    float gravity = 0.3;
    Room* room = nullptr;
    std::vector<Tile*> tiles;
    View* m_View = nullptr;
public:
    Game(unsigned int w, unsigned int h);

    void loop();

    virtual void handleEvent(sf::Event& event){

    }

    void deleteMarkedObjects();

    virtual void step();

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

    void drawWorld(sf::RenderTarget& target, sf::RenderStates states) const;

    void drawView(sf::RenderTarget& target, sf::RenderStates states) const;

    void drawToView(Object *object);

    View* getView();

    void updateView();

    virtual ~Game();

    void updateDepth();

    const std::vector<Object *> &getObjects() const;
};



#endif //SLIMES_GAME_H
