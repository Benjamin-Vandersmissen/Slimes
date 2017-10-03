//
// Created by benji on 02.10.17.
//

#include <iostream>
#include "ClimbSlime.h"

sf::Texture* ClimbSlime::texture = nullptr;

ClimbSlime::ClimbSlime(float x, float y, int speed) : Slime(x, y, speed) {
    if(!texture){
        texture = new sf::Texture;
        texture->loadFromFile("./climbSlime.png");
    }
    _sprite.setTexture(*texture);
}

void ClimbSlime::keyPressed(sf::Keyboard::Key key) {
    if(!controlled)
        return;
    if(key == sf::Keyboard::LShift){
        ControllableObject::keyPressed(key);
    }
}

void ClimbSlime::keyboard() {
    if(!controlled)
        return;
    ControllableObject::keyboard();
    bool keyLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool keyRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    bool keyUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    bool keyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    bool hasHold = false;

    /**
     *      TTL    TTR
     *  LTL ########## RTR
     *      #        #
     *      #        #
     *      #        #
     *      #        #
     *      #        #
     *  LBL ########## RBR
     *      BBL    BBR
     *      
     * */

    
    
    
    Object* objectLeftTopLeft = window->objectAt({position.x-1, position.y});
    Object* objectTopTopLeft = window->objectAt({position.x, position.y-1});
    Object* objectRightTopRight = window->objectAt({position.x+_sprite.getLocalBounds().width, position.y});
    Object* objectTopTopRight = window->objectAt({position.x+_sprite.getLocalBounds().width-1, position.y-1});
    Object* objectLeftBottomLeft = window->objectAt({position.x-1, position.y+_sprite.getLocalBounds().height-1});
    Object* objectBottomBottomLeft = window->objectAt({position.x, position.y+_sprite.getLocalBounds().height});
    Object* objectRightBottomRight = window->objectAt({position.x+_sprite.getLocalBounds().width, position.y+_sprite.getGlobalBounds().height-1});
    Object* objectBottomBottomRight = window->objectAt({position.x+_sprite.getLocalBounds().width-1, position.y+_sprite.getGlobalBounds().height});

    bool leftTopLeft = objectLeftTopLeft == nullptr ? false : this->wouldCollide(*objectLeftTopLeft);
    bool topTopLeft = objectTopTopLeft == nullptr ? false : this->wouldCollide(*objectTopTopLeft);
    bool rightTopRight = objectRightTopRight == nullptr ? false : this->wouldCollide(*objectRightTopRight);
    bool topTopRight = objectTopTopRight == nullptr ? false : this->wouldCollide(*objectTopTopRight);
    bool leftBottomLeft = objectLeftBottomLeft == nullptr ? false : this->wouldCollide(*objectLeftBottomLeft);
    bool bottomBottomLeft = objectBottomBottomLeft == nullptr ? false : this->wouldCollide(*objectBottomBottomLeft);;
    bool rightBottomRight = objectRightBottomRight == nullptr ? false : this->wouldCollide(*objectRightBottomRight);;
    bool bottomBottomRight = objectBottomBottomRight == nullptr ? false : this->wouldCollide(*objectBottomBottomRight);;

    hasHold = hasHold || ((leftTopLeft || leftBottomLeft) && keyLeft);
    hasHold = hasHold || ((rightTopRight || rightBottomRight) && keyRight);
    hasHold = hasHold || ((topTopLeft || topTopRight) && keyUp);

    if(hasHold){
        int dy = (keyDown - keyUp)*speed;
        window->moveObjectRel(this, 0, dy);
        gravity = false;
        direction.y = 0; //reset all gravity
     }
    else{
        gravity = true;
    }
}

Object *ClimbSlime::clone() {
    return new ClimbSlime(position.x, position.y, speed);
}

std::string ClimbSlime::getType() {
    return "ClimbSlime";
}


