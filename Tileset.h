//
// Created by benji on 07.10.17.
//

#ifndef SLIMES_TILESET_H
#define SLIMES_TILESET_H


#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Tile : public sf::Sprite{
public:
    Tile();

    Tile(const sf::Texture &texture);

    Tile(const sf::Texture &texture, const sf::IntRect &rectangle);
};

class Tileset {
private:
    sf::Texture* texture;
    std::vector<Tile*> sprites;

public:
    Tileset(sf::Texture *texture);

    size_t addSprite(int x, int y, int w, int h);

    std::vector<Tile*> generateSprites(int* grid, int w, int h, int rastersize = 64);

    virtual ~Tileset();
};


#endif //SLIMES_TILESET_H
