#ifdef WIN32
    #include <windows.h>
    #define sleep(X)(Sleep(X))
    #ifndef random()
        #define random()(rand())
    #endif
#else
    #include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <SDL.h>
#include "graphicInterface.h"
#include "map.h"
#include "chef.h"

#define CHEFS 2

int main() {
    // getOrder();
    // getOrder();
    // getOrder();
    // getOrder();
    fill_queue();

    pthread_t thr_chefs[CHEFS], thr_status;
    int id_chef[CHEFS];

    init();

#ifdef WIN32
    sem_order = malloc(sizeof(sem_t));
    // sem_storage = malloc(sizeof(sem_t));
    sem_init(sem_order, 0, 1);
    // sem_init(sem_storage, 0, 1);
#else
    sem_order = sem_open("sem_order", O_CREAT | O_EXCL, 0644, 1);
    // sem_storage = sem_open("sem_storage",O_CREAT | O_EXCL, 0644,1);
#endif

    for (int i = 0; i < CHEFS; i++) {
        chef *new_chef = malloc(sizeof(chef));
        new_chef->id = i+1;
        new_chef->status = 0;
        pthread_create(&thr_chefs[i], NULL, t_chef, (void*) &new_chef);
    }

    // pthread_create(&thr_status, NULL, t_status,NULL);

    for (int i = 0; i < CHEFS; i++)
        pthread_join(thr_chefs[i], NULL);

    // pthread_cancel(thr_status);
    // pthread_join(thr_status, NULL);

    SpriteSheet * img = loadSpriteSheet("assets/chef.png", Character);

    initializeKitchen();

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    default:
                        break;
                }
            }
        }

        SDL_RenderClear(display.renderer);
        drawMap(&kitchen);
        // drawSprite(0, 0, img, 2, 0);
        SDL_RenderPresent(display.renderer);
    }

    SDL_DestroyTexture(kitchen.spriteSheet->texture);
    free(kitchen.spriteSheet);
    closeGUI();
    SDL_DestroyTexture(img->texture);
    free(img);

    return EXIT_SUCCESS;
}

