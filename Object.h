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
    sf::Sprite m_Sprite = sf::Sprite();
    sf::Vector2f m_Position;
    bool _delete = false;
    int m_Speed;
    bool m_Gravity = false;
    sf::Vector2f m_Direction = {0,0};
    int depth = 0;
public:
    Window* window = nullptr;

    Object();

    Object(float x, float y);

    Object(float x, float y, int speed);

    void completeInit(sf::Texture *texture);

    virtual std::string getType() = 0;

    void sprite(sf::Sprite sprite);

    void move(float x, float y);

    bool collision(sf::FloatRect boundingBox);

    virtual bool collision(Object& object);

    bool collision(Object& object, sf::FloatRect& ret);

    bool collisionRight(Object& object);

    bool collisionLeft(Object& object);

    bool collisionUp(Object& object);

    bool collisionDown(Object& object);

    const sf::Vector2f &getPosition() const;

    bool containsPoint(sf::Vector2f point);

    sf::FloatRect bounds();

    virtual Object* clone() = 0;

    virtual void keyPressed(sf::Keyboard::Key key);

    virtual void keyReleased(sf::Keyboard::Key key);

    virtual void keyboard();

    virtual void step();

    void markForDeletion();

    bool markedForDeletion();

    bool hasGravity();

    void applyImpulse(sf::Vector2f impulse);

    void setImpulse(sf::Vector2f impulse);

    const sf::Vector2f &getDirection() const;

    virtual bool wouldCollide(Object& object);

    sf::FloatRect getSize();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    int getDepth() const;
};

bool compareDepth(Object* obj1, Object* obj2);


#endif //SLIMES_OBJECT_H
