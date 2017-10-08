//
// Created by benji on 08.10.17.
//

#ifndef SLIMES_ANIMATEDSPRITE_H
#define SLIMES_ANIMATEDSPRITE_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class AnimatedSprite : public sf::Drawable{
private:
    std::vector<sf::Sprite*> sprites;
    sf::Time delay;
    sf::Clock clock;
public:

    AnimatedSprite(unsigned int delay);

    void start();

    void addSprite(sf::Sprite* sprite);

    void addSprite(sf::Texture* texture, sf::IntRect rect);

    void position(sf::Vector2f position);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif //SLIMES_ANIMATEDSPRITE_H
