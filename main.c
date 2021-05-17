#ifdef WIN32
    #include <windows.h>
    #define sleep(X)(Sleep(X))
    #define random()(rand())
#else
    #include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>
#include "graphicInterface.h"
#include "map.h"
#include "chef.h"
#include "order.h"

#define CHEFS 2

int main() {

    pthread_t thr_chefs[CHEFS], thr_status;
    int id_chef[CHEFS];

    init();

#ifdef WIN32
    sem_order = malloc(sizeof(sem_t));
    sem_init(sem_order, 0, 1);
    for(int i=0;i<9;i++){
        sem_ingredients[i] = malloc(sizeof(sem_t));
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
        printf("-------------------- %d\n",(*order_queue[0])[4]);
        printf("-------------------- %d\n",(*order_queue[0])[5]);
        printf("----------------------------------------\n");

    for (int i = 0; i < CHEFS; i++) {
        chef *new_chef = malloc(sizeof(chef));
        new_chef->id = i+1;
        new_chef->status = 0;
        pthread_create(&thr_chefs[i], NULL, t_chef, (void*) &new_chef);
    }

    for (int i = 0; i < CHEFS; i++)
        pthread_join(thr_chefs[i], NULL);

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

