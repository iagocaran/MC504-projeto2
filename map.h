#ifndef PROJETO2_MAP_H
#define PROJETO2_MAP_H

#include "graphicInterface.h"

typedef struct Tile {
    int i;
    int j;
} Tile;

typedef struct Map {
    Tile * tiles;
    SpriteSheet * spriteSheet;
    int width;
    int height;
} Map;

Map kitchen;

void initializeKitchen() {
    kitchen.width = 10;
    kitchen.height = 18;
    kitchen.tiles = malloc(kitchen.width * kitchen.height * sizeof(Tile));
    kitchen.spriteSheet = loadSpriteSheet("assets/interior.png", Tileset);
    Tile t[] = {
            { 1, 2 }, { 3, 2 }, { 3, 2 }, { 3, 2 }, { 3, 2 }, { 3, 2 }, { 3, 2 }, { 3, 2 }, { 3, 2 }, { 0, 2 },
            { 4, 1 }, { 1, 4 }, { 1, 4 }, { 1, 4 }, { 1, 4 }, { 1, 4 }, { 1, 4 }, { 1, 4 }, { 1, 4 }, { 2, 1 },
            { 4, 1 }, { 1, 4 }, { 1, 4 }, { 1, 4 }, { 1, 4 }, { 1, 4 }, { 1, 4 }, { 1, 4 }, { 1, 4 }, { 2, 1 },
            { 4, 1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 2, 1 },
            { 4, 1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 2, 1 },
            { 4, 1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 2, 1 },
            { 4, 1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 2, 1 },
            { 4, 1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 2, 1 },
            { 4, 1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 2, 1 },
            { 4, 1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 2, 1 },
            { 4, 1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 2, 1 },
            { 4, 1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 2, 1 },
            { 4, 1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 2, 1 },
            { 4, 1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 2, 1 },
            { 4, 1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 2, 1 },
            { 4, 1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 2, 1 },
            { 4, 1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 2, 1 },
            { 1, 1 }, { 3, 0 }, { 3, 0 }, { 3, 0 }, { 3, 0 }, { 3, 0 }, { 3, 0 }, { 3, 0 }, { 3, 0 }, { 0, 1 }
    };
    memcpy(kitchen.tiles, t, sizeof(t));
}

void drawMap(Map * map) {
    for (int j = 0; j < map->height; ++j) {
        for (int i = 0; i < map->width; ++i) {
            drawSprite(0 + map->spriteSheet->width / map->spriteSheet->horizontalFrames * i,
                       0 + map->spriteSheet->height / map->spriteSheet->verticalFrames * j,
                       map->spriteSheet, map->tiles[j * map->width + i].j, map->tiles[j * map->width + i].i);
        }
    }
}

#endif //PROJETO2_MAP_H
