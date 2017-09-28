//
// Created by benji on 26.09.17.
//

#include <iostream>
#include "Window.h"

Window::Window(unsigned int w, unsigned int h) {
    window = new sf::RenderWindow(sf::VideoMode(w,h), "TEST");
    window->setFramerateLimit(60);
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

        bool keyLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        bool keyRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        moveObjectRel(controlledObject, (keyRight-keyLeft)*controlledObject->getSpeed(), 0);
        for(Object* object : objects){
            if (object->isMoveable()){
                MoveableObject* movObject = (MoveableObject*) object;
                if (movObject->hasGravity()) {
                    bool hasSupport = objectAt({movObject->bounds().left, movObject->bounds().top+movObject->bounds().height+1}) != NULL; //Support bottom left
                    hasSupport |= objectAt({movObject->bounds().left+movObject->bounds().width-1, movObject->bounds().top+movObject->bounds().height+1}) != NULL;//suport bottom right
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
    sf::Vector2f origPosition = object->getPosition();
    object->move(x,y);
    for(Object* object1 : objects){
        if (object->collision(*object1) && object1 != object){
            object->move(origPosition.x, origPosition.y);
            return object1;
        }
    }
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
            return obj;
        }
        a += dx     ;
             b += dy;
    }
    return nullptr;
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

void Window::loadRoom(Room &room) {
    objects = room.getObjects();
    window->close();
    window->create(sf::VideoMode(room.size().x, room.size().y), "TEST");
    window->setFramerateLimit(60);
    for(Object* obj: objects){
        if (obj->isMoveable())
            controlledObject = (MoveableObject*) obj;
    }
}
