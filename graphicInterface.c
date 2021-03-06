#include "graphicInterface.h"

void initGUI() {
    SDL_Init(SDL_INIT_VIDEO);
    display.window = SDL_CreateWindow(
            "SDL2Test",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            10 * 64,
            10 * 64,
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

SpriteSheet * loadSpriteSheet(string path, SpriteSheetType type) {
    SpriteSheet * sprite = malloc(sizeof(SpriteSheet));
    if (type == Character) {
        sprite->width = 832;
        sprite->height = 1344;
        sprite->horizontalFrames = 13;
        sprite->verticalFrames = 21;
    } else {
        sprite->width = 256;
        sprite->height = 256;
        sprite->horizontalFrames = 8;
        sprite->verticalFrames = 8;
    }
    sprite->texture = loadTexture(path);
    return sprite;
}

void drawSprite(int x, int y, SpriteSheet * template, int line, int column) {
    SDL_Rect clip = {
            template->width / template->horizontalFrames * column,
            template->height / template->verticalFrames * line,
            template->width / template->horizontalFrames,
            template->height / template->verticalFrames };
    SDL_Rect renderQuad = { x, y, template->width / template->horizontalFrames * 2, template->height / template->verticalFrames * 2 };

    SDL_RenderCopy(display.renderer, template->texture, &clip, &renderQuad);
}

void closeGUI() {
    SDL_DestroyWindow(display.window);
    IMG_Quit();
    SDL_Quit();
}
