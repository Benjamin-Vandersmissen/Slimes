//
// Created by benji on 08.10.17.
//

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(unsigned int delay) {
    this->delay = sf::milliseconds(delay);
    clock = sf::Clock();
}

void AnimatedSprite::start() {
    clock.restart();
}

void AnimatedSprite::addSprite(sf::Sprite *sprite) {
    sprites.push_back(sprite);
}

void AnimatedSprite::addSprite(sf::Texture *texture, sf::IntRect rect) {
    sprites.push_back(new sf::Sprite(*texture, rect));
}

void AnimatedSprite::position(sf::Vector2f position) {
    for(sf::Sprite* sprite : sprites){
        sprite->setPosition(position);
    }
}

void AnimatedSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    unsigned long index = (clock.getElapsedTime().asMilliseconds()/delay.asMilliseconds()) % sprites.size();
    target.draw(*sprites[index], states);
}

AnimatedSprite::~AnimatedSprite() {
    for(sf::Sprite* sprite: sprites){
        delete sprite;
    }
}
