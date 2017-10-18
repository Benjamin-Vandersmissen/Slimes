//
// Created by benji on 07.10.17.
//

#include <iostream>
#include "Tileset.h"

Tile::Tile() {}

Tile::Tile(const sf::Texture &texture) : Sprite(texture) {}

Tile::Tile(const sf::Texture &texture, const sf::IntRect &rectangle) : Sprite(texture, rectangle) {}

Tileset::Tileset(sf::Texture *texture) : texture(texture) {}

size_t Tileset::addSprite(int x, int y, int w, int h) {
    Tile* sprite = new Tile(*texture);
    sprite->setTextureRect({x,y,w,h});
    sprites.push_back(sprite);
    return sprites.size();
}

std::vector<Tile *> Tileset::generateSprites(int *grid, int w, int h, int rastersize) {
    std::vector<Tile*> returnSprites;
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            if(grid[x+w*y] == 0)
                continue;
            Tile* sprite = new Tile(*sprites[grid[x+w*y] - 1]->getTexture(), sprites[grid[x+w*y]-1]->getTextureRect());
            sprite->setPosition({x*rastersize, y*rastersize});
            returnSprites.push_back(sprite);
        }
    }
    return returnSprites;
}

Tileset::~Tileset() {
    for(sf::Sprite* sprite : sprites){
        delete sprite;
    }
}
