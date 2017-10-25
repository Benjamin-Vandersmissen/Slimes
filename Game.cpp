//
// Created by benji on 26.09.17.
//

#include <iostream>
#include "Game.h"

Game::Game(unsigned int w, unsigned int h) {
    window = new sf::RenderWindow(sf::VideoMode(w,h), "Slimes BETA V0.00000001");
    window->setFramerateLimit(60);
}

void Game::loop() {
    while (window->isOpen())
    {
        if (!window->hasFocus())
            continue;
        sf::Event event;
        while (window->pollEvent(event))
        {
            handleEvent(event);
        }
        step();
        window->clear();
        updateView();
        deleteMarkedObjects();
        window->draw(*this);
        window->display();
    }

}

Object *Game::moveObject(Object *object, float x, float y) {
    sf::Vector2f origPosition = object->getPosition();
    object->move(x,y);
    for(Object* object1 : worldObjects){
        if (object->collision(*object1) && object1 != object){
            object->move(origPosition.x, origPosition.y);
            return object1;
        }
    }
    return nullptr;
}

Object *Game::moveObjectRel(Object *object, float x, float y) {
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

Object *Game::moveObjectTick(Object *object) {
    return moveObjectRel(object, object->getDirection().x, object->getDirection().y);
}

Object *Game::objectAt(sf::Vector2f position) {
    for(Object* object: worldObjects){
        if(object->containsPoint(position))
            return object;
    }
    return nullptr;
}

std::vector<Object *> Game::objectsAt(sf::Vector2f position) {
    std::vector<Object*> temp;
    for(Object* object : worldObjects){
        if (object->containsPoint(position))
            temp.push_back(object);
    }
    return temp;
}

void Game::loadRoom(Room &room) {
    this->room = &room;
    window->close();
    window->create(sf::VideoMode(static_cast<unsigned int>(room.viewSize().x), static_cast<unsigned int>(room.viewSize().y)), "Slimes BETA v0.00000001");
    window->setFramerateLimit(60);
    tiles = room.getTiles();
    reloadRoom();
}

void Game::addObject(Object *object) {
    worldObjects.push_back(object);
    object->move(object->getPosition().x, object->getPosition().y); //Move the sprite to the right m_worldPosition
    object->window = this;
}

void Game::applyGravity(Object *object) {
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

std::vector<Object *> Game::objectsAt(sf::FloatRect boundingBox) {
    std::vector<Object*> temp;
    for(Object* object : worldObjects){
        if(object->collision(boundingBox))
            temp.push_back(object);
    }
    return temp;
}

void Game::reloadRoom() {
    for(Object* object : worldObjects){
        delete object;
    }
    worldObjects = {};

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
        worldObjects.push_back(newObject);
    }
    updateDepth();
    updateView();
    for(Object* obj: worldObjects){
        obj->window = this;
    }
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    drawWorld(target, states);
}

View *Game::getView() {
    return m_View;
}

void Game::updateView() {
    this->m_View->updateView();
    this->window->setView(*m_View);
}

Game::~Game() {
    for(Object* object: worldObjects){
        delete object;
    }
    delete m_View;
}

void Game::updateDepth() {
    std::sort(worldObjects.begin(), worldObjects.end(), compareDepth);
}

const std::vector<Object *> &Game::getObjects() const {
    return worldObjects;
}

void Game::deleteMarkedObjects() {
    for(auto it = worldObjects.begin(); it != worldObjects.end(); ){
        if((*it)->markedForDeletion()){
            if(m_View->followedObject() == *it)
                m_View->followObject(nullptr);
            delete *it;
            it = worldObjects.erase(it);
        }
        else{
            ++it;
        }
    }
}

void Game::step() {
    for(Object* object : worldObjects){
        object->keyboard();
        object->step();
        if (object->hasGravity()){
            applyGravity(object);
        }
    }
}

void Game::drawWorld(sf::RenderTarget &target, sf::RenderStates states) const {
    for(Tile* tile : tiles){
        target.draw(*tile, states);
    }
    for(Object* object : worldObjects){
        target.draw(*object, states);
    }
}

void Game::drawView(sf::RenderTarget &target, sf::RenderStates states) const {
    for(Object* object: viewObjects){
        target.draw(*object, states);
    }
}

void Game::drawToView(Object *object) {
    viewObjects.push_back(object);
}


