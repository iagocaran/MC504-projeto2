#ifdef WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <SDL.h>
#include "graphicInterface.h"
#include "map.h"
#include "chef.h"

#define CHEFS 2

int main(int argc, char ** argv) {
    pthread_t thr_chefs[CHEFS];
    running = calloc(CHEFS, sizeof(bool));

    initGUI();

#ifdef WIN32
    sem_order = malloc(sizeof(sem_t));
    sem_init(sem_order, 0, 1);
    for(int i=0;i<9;i++){
        sem_ingredients[i] = calloc(1, sizeof(sem_t));
        sem_init(sem_ingredients[i], 0, 1);
    }
#else
    sem_order = sem_open("sem_order", O_CREAT | O_EXCL, 0644, 1);
    char name[18] = "sem_ingredients_";
    for(int i=0;i<9;i++){
        name[16] = i + '0';
        name[17]='\0';
        sem_ingredients[i] = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
    }
#endif
    sem_wait(sem_order);
    fill_queue();
    sem_post(sem_order);
    printf("-------------------- %d\n",(*order_queue[0])[0]);
    printf("-------------------- %d\n",(*order_queue[0])[1]);
    printf("-------------------- %d\n",(*order_queue[0])[2]);
    printf("-------------------- %d\n",(*order_queue[0])[3]);
    printf("----------------------------------------\n");

    chef chefs[CHEFS];
    for (int i = 0; i < CHEFS; i++) {
        chef * new_chef = &chefs[i];
        new_chef->id = i + 1;
        new_chef->status = WAITING;
        string filepath = "assets/chef0.png";
        filepath[11] = '0' + i;
        new_chef->img = loadSpriteSheet(filepath, Character);
        pthread_create(&thr_chefs[i], NULL, t_chef, (void*) new_chef);
    }

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
        for (int i = 0; i < CHEFS; ++i) {
            drawChef(&chefs[i]);
        }
        drawMap(&kitchenU);
        for (int i = 0; i < CHEFS; ++i) {
            drawOrder(&chefs[i], kitchen.spriteSheet);
        }
        SDL_RenderPresent(display.renderer);

        bool finished = true;
        for (int i = 0; i < CHEFS; i++) {
            if (running[i])
                finished = false;
        }
        if (finished) {
            for (int i = 0; i < CHEFS; i++)
                pthread_join(thr_chefs[i], NULL);
            quit = true;
        }
    }

    SDL_DestroyTexture(kitchen.spriteSheet->texture);
    free(kitchen.spriteSheet);
    closeGUI();

    return EXIT_SUCCESS;
}

