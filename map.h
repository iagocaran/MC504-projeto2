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
    kitchen.height = 10;
    kitchen.tiles = malloc(2 * kitchen.width * kitchen.height * sizeof(Tile));
    kitchen.spriteSheet = loadSpriteSheet("assets/restaurant.png", Tileset);
    Tile t[] = {
            { 1, 1 }, { 3, 2 }, { 3, 2 }, { 3, 2 }, { 3, 2 }, { 3, 2 }, { 3, 2 }, { 3, 2 }, { 3, 2 }, { 0, 1 },
            { 4, 1 }, { 1, 2 }, { 1, 2 }, { 1, 2 }, { 1, 2 }, { 1, 2 }, { 1, 2 }, { 1, 2 }, { 1, 2 }, { 2, 1 },
            { 4, 1 }, { 1, 2 }, { 1, 2 }, { 1, 2 }, { 1, 2 }, { 1, 2 }, { 1, 2 }, { 1, 2 }, { 1, 2 }, { 2, 1 },
            { 4, 1 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 2, 1 },
            { 4, 1 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 2, 1 },
            { 4, 1 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 2, 1 },
            { 4, 1 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 2, 1 },
            { 4, 1 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 2, 1 },
            { 4, 1 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 0, 2 }, { 2, 1 },
            { 1, 0 }, { 3, 0 }, { 3, 0 }, { 4, 0 }, { 0, 2 }, { 0, 2 }, { 2, 0 }, { 3, 0 }, { 3, 0 }, { 0, 0 },

            { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 },
            { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 },
            { -1, -1 }, { 0, 3 }, { 1, 3 }, { 2, 3 }, { 1, 3 }, { 3, 3 }, { 1, 3 }, { 3, 6 }, { 4, 6 }, { -1, -1 },
            { -1, -1 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 0, 4 }, { 3, 7 }, { 4, 7 }, { -1, -1 },
            { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 },
            { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 },
            { -1, -1 }, { 0, 6 }, { 1, 6 }, { 2, 6 }, { 1, 3 }, { 1, 3 }, { 5, 6 }, { 6, 6 }, { 7, 6 }, { -1, -1 },
            { -1, -1 }, { 0, 7 }, { 1, 7 }, { 2, 7 }, { 1, 4 }, { 1, 4 }, { 5, 7 }, { 6, 7 }, { 7, 7 }, { -1, -1 },
            { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 },
            { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 },
    };
    memcpy(kitchen.tiles, t, sizeof(t));
}

void drawMap(Map * map) {
    for (int l = 0; l < 2; ++l) {
        for (int j = 0; j < map->height; ++j) {
            for (int i = 0; i < map->width; ++i) {
                int index = l * map->width * map->height + j * map->width + i;
                if (map->tiles[index].j == -1 || map->tiles[index].i == -1) continue;
                drawSprite(0 + map->spriteSheet->width / map->spriteSheet->horizontalFrames * i * 2,
                           0 + map->spriteSheet->height / map->spriteSheet->verticalFrames * j * 2,
                           map->spriteSheet, map->tiles[index].j, map->tiles[index].i);
            }
        }
    }
}

#endif //PROJETO2_MAP_H