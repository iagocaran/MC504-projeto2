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
#define CHEFS 3
#define INGREDIENTS 10
#define INGREDIENTS_IN_RECEIPT 4
#define RECEIPTS 10

typedef enum {WAITING, STARTING, PREPARING, COOKING, DELIVERED} meal_status;
typedef enum {CARROT, TOMATOE, RICE, MEAT, EGG, POTATO, LETTUCE, ONION, GARLIC,BUTTER } ingredients_list;

const char* possible_status[] = {"WAITING", "STARTING", "PREPARING", "COOKING", "DELIVERED"};
const char* ingredients_name[] = {"CARROT", "TOMATO", "RICE", "MEAT", "EGG", "POTATO", "LETTUCE", "ONION", "GARLIC","BUTTER"};

const char* chefs[] = {"-","REMY", "AUGUST","JACAN","BIDU","MAG"};

typedef struct {
  int id;
  ingredients_list ingredients[INGREDIENTS_IN_RECEIPT];
  int quantity[INGREDIENTS_IN_RECEIPT];
} Receipt;
typedef struct {
  int number;
  int chef; // who is responsible for this order
  Receipt receipt;
  meal_status status; //maybe we can use it to update progress
} Order;

Receipt receipts[RECEIPTS];
Order orders[ORDERS];
int storage[] = {10,10,10,10,10,10,10,10,10,10};

sem_t *sem_order;
sem_t *sem_storage;
// sem_t sem_oven; // to be used in the future

int get_next_order() {
    for(int i = 0; i < ORDERS; i++)
        if(orders[i].status == WAITING)
            return i;
    
    return -1;
}

int get_ingredients(Receipt *receipt){
   int total_needed=0;
   for(int i=0; i<INGREDIENTS_IN_RECEIPT;i++)
        total_needed += receipt->quantity[i];
    
    while(total_needed > 0) {
        
        for(int i=0; i<INGREDIENTS_IN_RECEIPT;i++){
            sem_wait(sem_storage);
            //quantity in storage > 0
            if(storage[receipt->ingredients[i]] > 0) {
                //quantity in storage (-3) = quantity in storage (4) - quantity needed (7) 
                storage[receipt->ingredients[i]] = storage[receipt->ingredients[i]] - receipt->quantity[i];
                //quantity still needed
                if(storage[receipt->ingredients[i]] >= 0){
                    total_needed -= receipt->quantity[i];
                    receipt->quantity[i] = 0; //got all needed
                }
                else {
                    total_needed -= receipt->quantity[i] + storage[receipt->ingredients[i]];
                    receipt->quantity[i] = storage[receipt->ingredients[i]] * -1; //still need something
                }
            }
            sem_post(sem_storage);
            sleep(random()%3);
        }


        sleep(random()%3);
  }
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
void show_status(){
    printf("\n ---------------- ORDER STATUS ----------------            INGREDIENTS REMAINING \n");
    for(int i=0;i<ORDERS;i++){
        printf("| order id: %2d; ",orders[i].number);
        printf("chef: %6s; ",chefs[orders[i].chef]);
        printf("status: %9s |",possible_status[orders[i].status]);
        if(i > INGREDIENTS-1)
            printf("         | %8s            |\n","");
        else
            printf("         | %8s: %2d        |\n",ingredients_name[i],storage[i]);
    }
    printf(" ----------------------------------------------           ---------------------\n");
}

void* t_chef(void* v) {
    int id = *(int*) v;
    
    typedef int (*function)(void);
    function functions[3] = { &cut_ingredients, &cook_meal, &deliver_meal}; 

    while(1) {
        sem_wait(sem_order);
        int next_order = get_next_order();
        
        if(next_order < 0) {
            sem_post(sem_order);
            return NULL;
        }
        
        orders[next_order].chef = id;
        orders[next_order].status = STARTING;
        Receipt to_do = orders[next_order].receipt;
        sem_post(sem_order);

        get_ingredients(&to_do);
        

        for(int i = 0; i < 3; i++) {
            sem_wait(sem_order);
            functions[i]();
            orders[next_order].status = i + 2;
            sem_post(sem_order);
            sleep(1);
        }

        sleep(random() % 3);
    }
}
void* t_refill(){
    while(1){
        sem_wait(sem_storage);
        for(int i=0;i<INGREDIENTS;i++){
            if(storage[i] <= 0)
                storage[i] = 10;
        }
        sem_post(sem_storage);
        sleep(random() % 5);
    }
}
void* t_status() {
    while(1){
        sem_wait(sem_order);
        sem_wait(sem_storage);
        show_status();
        sem_post(sem_order);
        sem_post(sem_storage);
        sleep(1);
    }
}
int value_in_array(ingredients_list array[INGREDIENTS_IN_RECEIPT],int value,int size){
    for(int i=0; i< size; i++){
        if(array[i] == value)
            return 1;
    }
    return 0;
}
int main() {
    pthread_t thr_chefs[CHEFS], thr_status, thr_refill;
    int id_chef[CHEFS];

    init();

#ifdef WIN32
    sem_order = malloc(sizeof(sem_t));
    sem_storage = malloc(sizeof(sem_t));
    sem_init(sem_order, 0, 1);
    sem_init(sem_storage, 0, 1);
#else
    sem_order = sem_open("sem_order", O_CREAT | O_EXCL, 0644, 1);
    sem_storage = sem_open("sem_storage",O_CREAT | O_EXCL, 0644,1);
#endif
    
    //creating receipts
    for(int i=0; i<RECEIPTS; i++){
        int ingredients[INGREDIENTS_IN_RECEIPT],quantities[INGREDIENTS_IN_RECEIPT];
        receipts[i].id = i;
        for(int j=0;j<INGREDIENTS_IN_RECEIPT;j++){
            int ingredient;
            do {
                ingredient = random()%10;
            } while(value_in_array(receipts[i].ingredients,ingredient,INGREDIENTS_IN_RECEIPT) == 1);
            receipts[i].ingredients[j] = ingredient;
            receipts[i].quantity[j] = random()%10;
        }
    }

    // printf("--------------------------RECEIPTS--------------------------\n");
    // for (int i=0; i<RECEIPTS; i++){
    //     printf("id: %d\n",receipts[i].id);
    //     for(int j=0;j<INGREDIENTS_IN_RECEIPT;j++){
    //         printf("\t%s:%d\n",ingredients_name[receipts[i].ingredients[j]],receipts[i].quantity[j]);
    //     }
    //     printf("-----------------------------------------------------------\n");
    // }
        
    sem_wait(sem_order);
    
    // creating orders queue
    for(int i=0;i<ORDERS;i++){
        orders[i] = (Order) { .number=i, .chef=0, .status=0 };
        Receipt receipt = receipts[random()%10];
        orders[i].receipt.id =  receipt.id;
        for(int j=0;j<INGREDIENTS_IN_RECEIPT;j++){
            orders[i].receipt.ingredients[j]=receipt.ingredients[j];
            orders[i].receipt.quantity[j]=receipt.quantity[j];
        }
    }
    
    sem_post(sem_order);

    
    for (int i = 0; i < CHEFS; i++) {
        id_chef[i] = i+1;
        pthread_create(&thr_chefs[i], NULL, t_chef, (void*) &id_chef[i]);
    }

    pthread_create(&thr_status, NULL, t_status,NULL);
    pthread_create(&thr_refill, NULL, t_refill,NULL);

    for (int i = 0; i < CHEFS; i++) 
        pthread_join(thr_chefs[i], NULL);

    pthread_cancel(thr_status);
    pthread_join(thr_status, NULL);
    
    pthread_cancel(thr_refill);
    pthread_join(thr_refill, NULL);

    SDL_Texture * img = loadTexture("assets/chef.png");
    SDL_RenderCopy(display.renderer, img, NULL, NULL);
    SDL_RenderPresent(display.renderer);

    SDL_Delay(3000);
    bool quit = false;
    bool launched = false;
    while(!quit){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT)
                quit = true;
        }
        // if(!launched){
        //      for (int i = 0; i < CHEFS; i++) 
        //     pthread_join(thr_chefs[i], NULL);

        // pthread_cancel(thr_status);
        // pthread_join(thr_status, NULL);
        // }
    }

    closeGUI();

    return EXIT_SUCCESS;
}

