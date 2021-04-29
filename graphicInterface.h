#ifndef PROJETO2_GRAPHICINTERFACE_H
#define PROJETO2_GRAPHICINTERFACE_H

#include <string.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

typedef struct graphicInterface {
    SDL_Window * window;
    SDL_Renderer * renderer;
} graphicInterface;

typedef char * string;

typedef struct SpriteSheet {
    int width;
    int height;
    int horizontalFrames;
    int verticalFrames;
    SDL_Texture * texture;
} SpriteSheet;

graphicInterface display;

void init();
SDL_Texture * loadTexture(string path);
void closeGUI();
SpriteSheet * loadSpriteSheet(string path);
void drawSprite(int x, int y, SpriteSheet * template, int line, int column);

#endif //PROJETO2_GRAPHICINTERFACE_H
