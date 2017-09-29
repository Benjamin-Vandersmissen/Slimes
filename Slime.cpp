//
// Created by benji on 26.09.17.
//

#include <iostream>
#include "Slime.h"

sf::Texture* Slime::texture = nullptr;

Slime::Slime(float x, float y, int speed) : MoveableObject(x, y, speed)
{
    if(!texture){
        texture = new sf::Texture;
        texture->loadFromFile("./slime.png");
    }
    gravity = true;

    sf::Sprite sprite1;
    sprite1.setTexture(*texture);
    sprite(sprite1);
}

std::string Slime::getType() {
    return "Slime";
}

bool Slime::collision(Object &object) {
    bool retValue = Object::collision(object);
    if (object.getType() == "Slime"){
        //Collision with another slime => slimes will pass through each other
        return false;
    }
    else if (object.getType() == "Wall"){
        if (retValue){
            //Bounce back from wall
            if(collisionLeft(object) || collisionRight(object))
                direction.x = (std::abs(direction.x) > 1) ? -direction.x / 5 : 0;
            if (collisionDown(object) || collisionUp(object))
                direction.y = (std::abs(direction.y) > 1) ? -direction.y / 5 : 0;
        }
        return retValue;
    }
    else{
        return retValue;
    }
}

Object *Slime::clone() {
    return new Slime(0, 0, speed);
}

void Slime::keyPressed(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Space){
        setImpulse({0,-10});
    }
    if (key == sf::Keyboard::LShift){
        Projectile* projectile = new Projectile(position.x, position.y, this);
        window->addObject(projectile);
        projectile->setImpulse({facing*20,0});
    }
}

void Slime::keyboard() {
    bool keyLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool keyRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    if(!keyLeft && !keyRight){
        return;
    }
    else if (keyLeft && !keyRight)
        facing = -1;
    else if(keyRight && !keyLeft)
        facing = 1;
    int dx = (keyRight-keyLeft) * speed;
    window->moveObjectRel(this, dx, 0);
}
