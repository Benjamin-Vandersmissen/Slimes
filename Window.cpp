//
// Created by benji on 26.09.17.
//

#include <iostream>
#include "Window.h"

Window::Window(unsigned int w, unsigned int h) {
    window = new sf::RenderWindow(sf::VideoMode(w,h), "Slimes BETA V0.00000001");
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
                    if(event.key.code == sf::Keyboard::R)
                        reloadRoom();
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
        updateView();
        for(auto it = objects.begin(); it != objects.end(); ){
            if((*it)->markedForDeletion()){
                if(m_View->followedObject() == *it)
                    m_View->followObject(nullptr);
                delete *it;
                it = objects.erase(it);
            }
            else{
                ++it;
            }
        }
        window->draw(*this);
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
    for(Object* object: objects){
        if(object->containsPoint(position))
            return object;
    }
    return nullptr;
}

std::vector<Object *> Window::objectsAt(sf::Vector2f position) {
    std::vector<Object*> temp;
    for(Object* object : objects){
        if (object->containsPoint(position))
            temp.push_back(object);
    }
    return temp;
}

void Window::loadRoom(Room &room) {
    this->room = &room;
    window->close();
    window->create(sf::VideoMode(static_cast<unsigned int>(room.viewSize().x), static_cast<unsigned int>(room.viewSize().y)), "Slimes BETA v0.00000001");
    window->setFramerateLimit(60);
    sprites = room.getSprites();
    reloadRoom();
}

void Window::addObject(Object *object) {
    objects.push_back(object);
    object->move(object->getPosition().x, object->getPosition().y); //Move the sprite to the right m_Position
    object->window = this;
}

void Window::applyGravity(Object *object) {
    if (object->hasGravity()) {
        Object* bottomLeft = objectAt({object->bounds().left, object->bounds().top+object->bounds().height+1}); //Support bottom left
        bool hasSupport;
        Object* bottomRight = objectAt({object->bounds().left+object->bounds().width-1, object->bounds().top+object->bounds().height+1});//support bottom right
        hasSupport = (bottomLeft == NULL ? false : object->wouldCollide(*bottomLeft) ) || (bottomRight == NULL ? false : object->wouldCollide(*bottomRight));
        if (!hasSupport) {
            object->applyImpulse({0, gravity});
        }
        moveObjectTick(object);
    }
}

std::vector<Object *> Window::objectsAt(sf::FloatRect boundingBox) {
    std::vector<Object*> temp;
    for(Object* object : objects){
        if(object->collision(boundingBox))
            temp.push_back(object);
    }
    return temp;
}

void Window::reloadRoom() {
    for(Object* object : objects){
        delete object;
    }
    objects = {};

    delete m_View;
    m_View = new View;
    m_View->setSize(room->getView()->getSize());
    m_View->setCenter(room->getView()->getCenter());

    std::vector<Object*> temp = room->getObjects();
    for(Object* object : temp){
        Object* newObject = object->clone();
        if(room->getView()->followedObject() == object){
            m_View->followObject(newObject);
        }
        objects.push_back(newObject);
    }
    updateDepth();
    updateView();
    for(Object* obj: objects){
        obj->window = this;
    }
}

void Window::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(sf::Sprite* sprite : sprites){
        target.draw(*sprite, states);
    }
    for(Object* object : objects){
        target.draw(*object, states);
    }
}

View *Window::getView() {
    return m_View;
}

void Window::updateView() {
    this->m_View->updateView();
    this->window->setView(*m_View);
}

Window::~Window() {
    for(Object* object: objects){
        delete object;
    }
    delete m_View;
}

void Window::updateDepth() {
    std::sort(objects.begin(), objects.end(), compareDepth);

}

const std::vector<Object *> &Window::getObjects() const {
    return objects;
}

