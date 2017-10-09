//
// Created by benji on 07.10.17.
//

#ifndef SLIMES_TILESET_H
#define SLIMES_TILESET_H


#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Tileset {
private:
    sf::Texture* texture;
    std::vector<sf::Sprite*> sprites;

public:
    Tileset(sf::Texture *texture);

    int addSprite(int x, int y, int w, int h);

    std::vector<sf::Sprite*> generateSprites(int* grid, int w, int h, int rastersize = 64);

    virtual ~Tileset();
};


#endif //SLIMES_TILESET_H
