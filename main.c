#ifdef WIN32
    #include <windows.h>
    #define sleep(X)(Sleep(X))
    #define random()(rand())
#else
    #include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <SDL.h>
#include <SDL_image.h>
#include "graphicInterface.h"

#define ORDERS 10
#define CHEFS 2
// typedef struct {
//   char** ingredients;
// } Receipt;

typedef enum { WAITING, STARTING, PREPARING, COOKING, DELIVERED } meal_status;

const char * possible_status[] = { "WAITING", "STARTING", "PREPARING", "COOKING", "DELIVERED" };

typedef struct {
  int number;
  int chef; // who is responsible for this order
  meal_status status; //maybe we can use it to update progress
//   Receipt ingredients;
} Order;

Order orders[ORDERS];

sem_t *sem_order;
// sem_t sem_oven; // to be used in the future

int get_next_order() {
    for(int i = 0; i < ORDERS; i++)
        if(orders[i].status == WAITING)
            return i;
    
    return -1;
}

int get_ingredients() {
    sleep(random()%3);
    return 1;
}

int cut_ingredients() {
    sleep(random()%3);
    return 1; 
}

int cook_meal() {
    sleep(random()%3);
    return 1;
}

int deliver_meal() {
    sleep(random()%3);
    return 1;
}

void show_status() {
    printf("\n-------------------------------------------------\n");
    for(int i=0;i<ORDERS;i++){
        printf("order id: %d; ",orders[i].number);
        printf("chef id: %d; ",orders[i].chef);
        printf("status: %s\n",possible_status[orders[i].status]);
    }
    printf("\n-------------------------------------------------\n");
}

void* t_chef(void* v) {
    int id = *(int*) v;
    
    typedef int (*function)(void);
    function functions[4] = { &get_ingredients, &cut_ingredients, &cook_meal, &deliver_meal };

    while(1) {
        sem_wait(sem_order);
        int next_order = get_next_order();

        if(next_order < 0) {
            sem_post(sem_order);
            return NULL;
        }

        orders[next_order].chef = id;
        orders[next_order].status = STARTING;
        sem_post(sem_order);

        for(int i = 0; i < 4; i++) {
            sem_wait(sem_order);
            functions[i]();
            orders[next_order].status = i + 1;
            sem_post(sem_order);
        }

        sleep(random() % 3);
    }
}

void* t_status(){
    while(1){
        sem_wait(sem_order);
        show_status();
        sem_post(sem_order);
        sleep(1);
    }
}

int main() {
    pthread_t thr_chefs[CHEFS], thr_status;
    int id_chef[CHEFS];

    init();

#ifdef WIN32
    sem_order = malloc(sizeof(sem_t));
    sem_init(sem_order, 0, 1);
#else
    sem_order = sem_open("sem_order", O_CREAT | O_EXCL, 0644, 1);
#endif

    sem_wait(sem_order);
    
    // creating orders queue
    for(int i=0;i<ORDERS;i++)
        orders[i] = (Order) { .number=i, .chef=-1, .status=0 };
    
    sem_post(sem_order);
    
    for (int i = 0; i < CHEFS; i++) {
        id_chef[i] = i;
        pthread_create(&thr_chefs[i], NULL, t_chef, (void*) &id_chef[i]);
    }

    pthread_create(&thr_status, NULL, t_status,NULL);

    for (int i = 0; i < CHEFS; i++) 
        pthread_join(thr_chefs[i], NULL);

    pthread_cancel(thr_status);
    pthread_join(thr_status, NULL);

    SDL_Texture * img = loadTexture("assets/chef.png");
    SDL_RenderCopy(display.renderer, img, NULL, NULL);
    SDL_RenderPresent(display.renderer);

    SDL_Delay(3000);

    close();

    return EXIT_SUCCESS;
}

