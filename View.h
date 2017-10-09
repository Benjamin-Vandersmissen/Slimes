//
// Created by uauser on 10/9/17.
//

#ifndef SLIMES_VIEW_H
#define SLIMES_VIEW_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Object.h"

class Object;

class View : public sf::View{
private:
    Object* m_Object = NULL;
public:
    void followObject(Object* obj);

    Object* followedObject();

    void updateView();
};


#endif //SLIMES_VIEW_H
