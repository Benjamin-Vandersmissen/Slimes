//
// Created by benji on 26.09.17.
//

#ifndef SLIMES_OBJECT_H
#define SLIMES_OBJECT_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Object {
protected:
    sf::Sprite _sprite;
    sf::Vector2f position;
    bool gravity = false;
    sf::Vector2f direction = {0,0};
public:
    Object(float x, float y);

    virtual std::string getType() = 0;

    void sprite(sf::Sprite sprite);

    void draw(sf::RenderWindow &window);

    void move(float x, float y);

    void moveRel(float x, float y);

    virtual bool collision(Object& object);

    const sf::Vector2f &getPosition() const;

    bool hasGravity();

    void applyImpulse(sf::Vector2f impulse);

    const sf::Vector2f &getDirection() const;
};


#endif //SLIMES_OBJECT_H
