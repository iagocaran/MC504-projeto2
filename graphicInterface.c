#include "graphicInterface.h"

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    display.window = SDL_CreateWindow(
            "SDL2Test",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            0
    );

    display.renderer = SDL_CreateRenderer(display.window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(display.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(display.renderer);
    SDL_RenderPresent(display.renderer);

    IMG_Init(IMG_INIT_PNG);
}

SDL_Texture * loadTexture(string path) {
    SDL_Texture * newTexture = NULL;
    SDL_Surface * loadedSurface = IMG_Load(path);
    newTexture = SDL_CreateTextureFromSurface(display.renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

SDL_Surface * loadImg(string path) {
    SDL_Surface * optimizedSurface = NULL;
    SDL_Surface * loadedSurface = IMG_Load(path);

}

void closeGUI() {
    SDL_DestroyWindow(display.window);
    IMG_Quit();
    SDL_Quit();
}
