//
// Created by benji on 26.09.17.
//

#include "Window.h"

Window::Window(unsigned int w, unsigned int h) {
    window = new sf::RenderWindow(sf::VideoMode(w,h), "TEST");
    window->setFramerateLimit(60);
    objects = {new Slime(10,10,5), new Slime(100, 10, 5)};
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
                }
                default:
                    break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            moveObjectDir(controlledObject, 3);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            moveObjectDir(controlledObject, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            moveObjectDir(controlledObject, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            moveObjectDir(controlledObject,2);
        }
        window->clear();
        for(Object* object : objects){
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
        Object* obj = moveObject(object, object->getPosition().x+a, object->getPosition().y+b);
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
                object->applyImpulse({0,-0.5});
                break;
            case 1: // move Right
                object->applyImpulse({0.2,0});
                break;
            case 2 : // move Down
                object->applyImpulse({0,0.2});
                break;
            case 3 : // move Left
                object->applyImpulse({-0.2,0});
                break;
            default:
                return nullptr;
        }
        return moveObjectRel(object, object->getDirection().x, object->getDirection().y);
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
