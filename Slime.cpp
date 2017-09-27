//
// Created by benji on 26.09.17.
//

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
    else{
        return retValue;
    }
}
