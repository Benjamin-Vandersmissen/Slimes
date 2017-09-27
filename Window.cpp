//
// Created by benji on 26.09.17.
//

#include <iostream>
#include "Window.h"

Window::Window(unsigned int w, unsigned int h) {
    window = new sf::RenderWindow(sf::VideoMode(w,h), "TEST");
    window->setFramerateLimit(60);
    objects = {new Slime(10,10,5), new Wall(300,100), new Wall(300,164), new Wall(300, 228), new Wall(236,228), new Wall(172, 228), new Wall(108,228)};
    controlledObject = (MoveableObject*) objects[0];
}

void Window::loop() {
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                {
                    window->close();
                    break;
                }

                case sf::Event::KeyPressed:
                {
                    if (event.key.code == sf::Keyboard::Space){
                        controlledObject->setImpulse({0,-10});
                    }
                }
                default:
                    break;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            moveObjectDir(controlledObject, 3);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            moveObjectDir(controlledObject, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            moveObjectDir(controlledObject, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            moveObjectDir(controlledObject,2);
        }
        for(Object* object : objects){
            if (object->isMoveable()){
                MoveableObject* movObject = (MoveableObject*) object;
                if (movObject->hasGravity()) {
                    bool hasSupport = objectAt({movObject->bounds().left, movObject->bounds().top+movObject->bounds().height+1}) != NULL; //Support bottom left
                    hasSupport |= objectAt({movObject->bounds().left+movObject->bounds().width, movObject->bounds().top+movObject->bounds().height+1}) != NULL;//suport bottom right
                    if (!hasSupport) {
                        movObject->applyImpulse({0, gravity});
                    }
                    moveObjectTick(movObject);
                }
            }
        }
        window->clear();
        for(Object* object : objects)
        {
            object->draw(*window);
        }
        window->display();
    }

}

Object *Window::moveObject(Object *object, float x, float y) {
    for(Object* object1 : objects){
        if (object->collision(*object1) && object1 != object){
            return object1;
        }
    }
    object->move(x, y);
    return nullptr;
}

Object *Window::moveObjectRel(Object *object, float x, float y) {
    float a = 0, b = 0;
    float dx, dy;
    dx = x / std::max(std::abs(x),std::abs(y));
    dy = y / std::max(std::abs(x),std::abs(y));
    while(std::abs(a) < std::abs(x) || std::abs(b) < std::abs(y)){
        Object* obj = moveObject(object, object->getPosition().x+dx, object->getPosition().y+dy);
        if (obj){
            object->moveRel(-dx, -dy);
            return obj;
        }
        a += dx;
        b += dy;
    }
    return nullptr;
}

Object *Window::moveObjectDir(MoveableObject *object, unsigned int direction) {
    if(object->hasGravity()){
        switch (direction) {
            case 0 : // move Up
                object->setImpulse({0,-3});
                break;
            case 1: // move Right
                object->setImpulse({3,0});
                break;
            case 2 : // move Down
                object->setImpulse({0,3});
                break;
            case 3 : // move Left
                object->setImpulse({-3,0});
                break;
            default:
                break;
        }
        return nullptr;
    }
    else {
        switch (direction) {
            case 0 : // move Up
                return moveObjectRel(object, 0, -object->getSpeed());
            case 1: // move Right
                return moveObjectRel(object, object->getSpeed(), 0);
            case 2 : // move Down
                return moveObjectRel(object, 0, object->getSpeed());
            case 3 : // move Left
                return moveObjectRel(object, -object->getSpeed(), 0);
            default:
                return nullptr;
        }
    }
}

Object *Window::moveObjectTick(MoveableObject *object) {
    return moveObjectRel(object, object->getDirection().x, object->getDirection().y);
}

Object *Window::objectAt(sf::Vector2f position) {
    for(Object* object : objects){
        if (object->containsPoint(position))
            return object;
    }
    return nullptr;
}
