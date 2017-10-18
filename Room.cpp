//
// Created by benji on 28.09.17.
//

#include <iostream>
#include "Room.h"

Room::Room(unsigned int width, unsigned int height, unsigned int rastersize) : width(width), height(height), rastersize(rastersize) {
    m_View = new View;
    m_View->setCenter(width/2.0f, height/2.0f);
    m_View->setSize(width, height);
}

unsigned long long int Room::allocateObject(Object *object) {
    allocatedObjects.insert({allocatedObjects.size()+1, object});
    return allocatedObjects.size();
}

void Room::populateObjects(int *array) {
    for(int y = 0; y < height; y += rastersize){
        for(int x = 0; x < width; x += rastersize){
            int rasterx, rastery, rasterwidth;
            rasterx = x/rastersize;
            rastery = y/rastersize;
            rasterwidth = width/rastersize;
            int obj = array[rasterx+rasterwidth*rastery];
            if(allocatedObjects.find(obj) != allocatedObjects.end()){
                Object* object = allocatedObjects[obj]->clone();
                object->move(x,y);
                objects.push_back(object);
            }
        }
    }
}

const std::vector<Object *> Room::getObjects(){
    return objects;
}

sf::Vector2u Room::size() const {
    return sf::Vector2u(width, height);
}

void Room::addObject(Object *object) {
    objects.push_back(object);
}

void Room::setTiles(std::vector<Tile *> tiles) {
    this->tiles = tiles;
}

const std::vector<Tile *> &Room::getTiles() const {
    return tiles;
}

void Room::setView(float x, float y, float w, float h) {
    if(m_View)
        delete m_View;
    m_View = new View;
    m_View->setCenter(x,y);
    m_View->setSize(w, h);
}

void Room::setView(Object *object, float w, float h) {
    if(m_View)
        delete m_View;
    m_View = new View;
    m_View->followObject(object);
    m_View->setSize(w,h);
}

View *Room::getView() const {
    return m_View;
}

sf::Vector2f Room::viewSize() const {
    return m_View->getSize();
}
