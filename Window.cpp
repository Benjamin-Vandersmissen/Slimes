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
        if (!window->hasFocus())
            continue;
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
                    int size = objects.size();
                    for(int i = 0; i < size; i++){
                        Object* object = objects[i];
                        object->keyPressed(event.key.code);
                    }
                }
                default:
                    break;
            }
        }
        for(Object* object : objects){
            object->keyboard();
            object->step();
            if (object->hasGravity()){
                applyGravity(object);
            }
        }
        window->clear();
        for(auto it = objects.begin(); it != objects.end(); ){
            if((*it)->markedForDeletion()){
                delete *it;
                it = objects.erase(it);
            }
            else{
                ++it;
            }
        }
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

Object *Window::moveObjectTick(Object *object) {
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
        obj->window = this;
    }
}

void Window::addObject(Object *object) {
    objects.push_back(object);
}

void Window::applyGravity(Object *object) {
    if (object->hasGravity()) {
        bool hasSupport = objectAt({object->bounds().left, object->bounds().top+object->bounds().height+1}) != NULL; //Support bottom left
        hasSupport |= objectAt({object->bounds().left+object->bounds().width-1, object->bounds().top+object->bounds().height+1}) != NULL;//suport bottom right
        if (!hasSupport) {
            object->applyImpulse({0, gravity});
        }
        moveObjectTick(object);
    }
}
