//
// Created by benji on 02.10.17.
//

#include "ControllableObject.h"

void ControllableObject::keyPressed(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Space){
        setImpulse({0,-10});
    }
    if (key == sf::Keyboard::LShift){
        Projectile* projectile = new Projectile(position.x, position.y, this);
        window->addObject(projectile);
        projectile->setImpulse({facing*20,0});
    }
}

void ControllableObject::keyboard() {
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

bool ControllableObject::isControlled() {
    return controlled;
}

ControllableObject::ControllableObject(int x, int y, int speed) : Object(x,y,speed){

}
