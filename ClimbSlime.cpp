//
// Created by benji on 02.10.17.
//

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

    
    
    
    bool leftTopLeft = window->objectAt({position.x-1, position.y}) != nullptr;
    bool topTopLeft = window->objectAt({position.x, position.y-1}) != nullptr;
    bool rightTopRight = window->objectAt({position.x+_sprite.getLocalBounds().width, position.y}) != nullptr;
    bool topTopRight = window->objectAt({position.x+_sprite.getLocalBounds().width-1, position.y-1}) != nullptr;
    bool leftBottomLeft = window->objectAt({position.x-1, position.y+_sprite.getLocalBounds().height-1}) != nullptr;
    bool bottomBottomLeft = window->objectAt({position.x, position.y+_sprite.getLocalBounds().height}) != nullptr;
    bool rightBottomRight = window->objectAt({position.x+_sprite.getLocalBounds().width, position.y+_sprite.getGlobalBounds().height-1}) != nullptr;
    bool bottomBottomRight = window->objectAt({position.x+_sprite.getLocalBounds().width-1, position.y+_sprite.getGlobalBounds().height}) != nullptr;
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


