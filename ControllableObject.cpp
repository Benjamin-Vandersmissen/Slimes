//
// Created by benji on 02.10.17.
//

#include <iostream>
#include "ControllableObject.h"

void ControllableObject::keyPressed(sf::Keyboard::Key key) {
    if(!controlled)
        return;
    if (key == sf::Keyboard::Space) {
        if (nrJumps > 0) {
            setImpulse({0, -10});
            nrJumps--;
        }
    }
    if (key == sf::Keyboard::LShift){
        Projectile* projectile = new Projectile(m_Position.x+getSize().width/2, m_Position.y+getSize().height/2, this);
        window->addObject(projectile);
        projectile->setImpulse({facing*20.0f,0});
    }
}

void ControllableObject::keyboard() {
    if(!controlled)
        return;
    bool keyLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool keyRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    if(!keyLeft && !keyRight){
        return;
    }
    else if (keyLeft && !keyRight)
        facing = -1;
    else if(keyRight && !keyLeft)
        facing = 1;
    int dx = (keyRight-keyLeft) * m_Speed;
    window->moveObjectRel(this, dx, 0);
}

bool ControllableObject::isControlled() {
    return controlled;
}

ControllableObject::ControllableObject(float x, float y, int speed) : Object(x, y, speed){

}

bool ControllableObject::collision(Object &object) {
    bool retvalue = Object::collision(object);
    if(retvalue){
        if(object.getType() == "Key"){
            //Pickup key
            object.markForDeletion();
        }
        bool collision = Object::collisionDown(object);
        if(collision)
            nrJumps = maxNrJumps;
    }
    return retvalue;
}

void ControllableObject::toggleControlled() {
    if (controlled) {
        controlled = false;
        m_Sprite.setColor({127,127,127});
    }else{
        controlled = true;
        m_Sprite.setColor({255,255,255});
    }
}

bool ControllableObject::wouldCollide(Object &object) {
    std::vector<std::string> types = {"Key", "Wall"};
    if(std::find(types.begin(), types.end(), object.getType()) == types.end()){
        return false;
    }
    return true;
}
