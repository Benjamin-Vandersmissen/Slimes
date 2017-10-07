//
// Created by benji on 07.10.17.
//

#include <iostream>
#include "Tileset.h"

Tileset::Tileset(sf::Texture *texture) : texture(texture) {}

int Tileset::addSprite(int x, int y, int w, int h) {
    sf::Sprite* sprite = new sf::Sprite(*texture);
    sprite->setTextureRect({x,y,w,h});
    sprites.push_back(sprite);
    return sprites.size();
}

std::vector<sf::Sprite *> Tileset::generateSprites(int *grid, int w, int h, int rastersize) {
    std::vector<sf::Sprite*> returnSprites;
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            if(grid[x+w*y] == 0)
                continue;
            sf::Sprite* sprite = new sf::Sprite(*sprites[grid[x+w*y] - 1]->getTexture(), sprites[grid[x+w*y]-1]->getTextureRect());
            sprite->setPosition({x*rastersize, y*rastersize});
            returnSprites.push_back(sprite);
        }
    }
    return returnSprites;
}
