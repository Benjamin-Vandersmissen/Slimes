//
// Created by benji on 26.09.17.
//

#ifndef SLIMES_OBJECT_H
#define SLIMES_OBJECT_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
class Window;

class Object {
protected:
    sf::Sprite _sprite;
    sf::Vector2f position;
    bool _delete = false;
public:
    Window* window = nullptr;

    Object(float x, float y);

    virtual std::string getType() = 0;

    void sprite(sf::Sprite sprite);

    void draw(sf::RenderWindow &window);

    void move(float x, float y);

    void moveRel(float x, float y);

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

    void markForDeletion();

    bool markedForDeletion();

};


#endif //SLIMES_OBJECT_H
