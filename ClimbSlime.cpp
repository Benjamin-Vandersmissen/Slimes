//
// Created by benji on 02.10.17.
//

#include <iostream>
#include "ClimbSlime.h"

sf::Texture* ClimbSlime::texture = nullptr;

ClimbSlime::ClimbSlime(float x, float y, int speed) : Slime(x, y, speed) {
    maxNrJumps = 0;
    nrJumps = maxNrJumps;
    if(!texture){
        texture = new sf::Texture;
        texture->loadFromFile("./climbSlime.png");
    }
    m_Sprite.setTexture(*texture);
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

    
    
    
    Object* objectLeftTopLeft = window->objectAt({m_Position.x-1, m_Position.y});
    Object* objectTopTopLeft = window->objectAt({m_Position.x, m_Position.y-1});
    Object* objectRightTopRight = window->objectAt({m_Position.x+m_Sprite.getLocalBounds().width, m_Position.y});
    Object* objectTopTopRight = window->objectAt({m_Position.x+m_Sprite.getLocalBounds().width-1, m_Position.y-1});
    Object* objectLeftBottomLeft = window->objectAt({m_Position.x-1, m_Position.y+m_Sprite.getLocalBounds().height-1});
    Object* objectBottomBottomLeft = window->objectAt({m_Position.x, m_Position.y+m_Sprite.getLocalBounds().height});
    Object* objectRightBottomRight = window->objectAt({m_Position.x+m_Sprite.getLocalBounds().width, m_Position.y+m_Sprite.getGlobalBounds().height-1});
    Object* objectBottomBottomRight = window->objectAt({m_Position.x+m_Sprite.getLocalBounds().width-1, m_Position.y+m_Sprite.getGlobalBounds().height});

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
        int dy = (keyDown - keyUp)*m_Speed;
        window->moveObjectRel(this, 0, dy);
        m_Gravity = false;
        m_Direction.y = 0; //reset all gravity
     }
    else{
        m_Gravity = true;
    }
}

Object *ClimbSlime::clone() {
    return new ClimbSlime(m_Position.x, m_Position.y, m_Speed);
}

std::string ClimbSlime::getType() {
    return "ClimbSlime";
}


