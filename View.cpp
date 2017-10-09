//
// Created by uauser on 10/9/17.
//

#include "View.h"

void View::followObject(Object *obj) {
    m_Object = obj;
    setCenter(m_Object->getPosition());
}

Object *View::followedObject() {
    return m_Object;
}

void View::updateView() {
    if(m_Object){
        setCenter(m_Object->getPosition());
    }
}
