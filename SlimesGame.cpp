//
// Created by uauser on 10/18/17.
//

#include "SlimesGame.h"

SlimesGame::SlimesGame(unsigned int w, unsigned int h) : Game(w, h) {}

void SlimesGame::handleEvent(sf::Event &event) {
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
            size_t size = objects.size();
            for(size_t i = 0; i < size; i++){
                Object* object = objects[i];
                object->keyPressed(event.key.code);
            }
        }
        default:
            break;
    }
}
