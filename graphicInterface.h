#ifndef PROJETO2_GRAPHICINTERFACE_H
#define PROJETO2_GRAPHICINTERFACE_H

#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

typedef struct graphicInterface {
    SDL_Window * window;
    SDL_Renderer * renderer;
} graphicInterface;

typedef char * string;

graphicInterface display;

void init();
SDL_Texture * loadTexture(string path);
void close();

#endif //PROJETO2_GRAPHICINTERFACE_H
