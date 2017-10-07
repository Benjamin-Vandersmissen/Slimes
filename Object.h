//
// Created by benji on 26.09.17.
//

#ifndef SLIMES_OBJECT_H
#define SLIMES_OBJECT_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Window.h"
class Window;

class Object : public sf::Drawable{
protected:
    sf::Sprite _sprite = sf::Sprite();
    sf::Vector2f position;
    bool _delete = false;
    int speed;
    bool gravity = false;
    sf::Vector2f direction = {0,0};
public:
    Window* window = nullptr;

    Object();

    Object(float x, float y);

    Object(float x, float y, int speed);

    void completeInit(sf::Texture *texture);

    virtual std::string getType() = 0;

    void sprite(sf::Sprite sprite);

    void move(float x, float y);

    void moveRel(float x, float y);

    bool collision(sf::FloatRect boundingBox);

    virtual bool collision(Object& object);

    bool collision(Object& object, sf::FloatRect& ret);

    bool collisionRight(Object& object);

    bool collisionLeft(Object& object);

    bool collisionUp(Object& object);

    bool collisionDown(Object& object);

    const sf::Vector2f &getPosition() const;

    virtual bool isMoveable();

    bool containsPoint(sf::Vector2f point);

    sf::FloatRect bounds();

    virtual Object* clone() = 0;

    virtual void keyPressed(sf::Keyboard::Key key);

    virtual void keyReleased(sf::Keyboard::Key key);

    virtual void keyboard();

    virtual void step();

    void markForDeletion();

    bool markedForDeletion();

    int getSpeed() const;

    bool hasGravity();

    void applyImpulse(sf::Vector2f impulse);

    void setImpulse(sf::Vector2f impulse);

    const sf::Vector2f &getDirection() const;

    virtual bool wouldCollide(Object& object);

    sf::FloatRect getSize();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif //SLIMES_OBJECT_H
