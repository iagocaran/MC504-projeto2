#include "chef.h"
#ifdef WIN32
    #include <windows.h>
    #define sleep(X)(Sleep(1000 * X))
    #ifndef random
        #define random()(rand())
    #endif
#else
    #include <unistd.h>
#endif
#include <semaphore.h>
#include <stdio.h>

int get_ingredients(order *order){
    for (int i = 0; i < 6; i++) {
        if ((*order)[i] == null)
            break;
        printf("ingredient:%d\n", (*order)[i]);
        sem_wait(sem_ingredients[(*order)[i]]);
        sleep(random() % 3 + 1);
        sem_post(sem_ingredients[(*order)[i]]);
    }
    return 1;
}

int cut_ingredients() {
    sleep(random()%3+1);
    return 1;
}

int cook_meal() {
    sleep(random()%3+1);
    return 1;
}

int deliver_meal() {
    sleep(random()%3+1);
    return 1;
}

void* t_chef(void* info) {
    chef* chef_info = (chef*) info;
    running[chef_info->id] = true;

    typedef int (*function)();
    function functions[3] = { &cut_ingredients, &cook_meal, &deliver_meal };

    while (1) {
        printf("chef: %d\n", chef_info->id);
        sem_wait(sem_order);
        printf("getting next order\n");        
        order* next_order = get_next_order();
        printf("orders remaining: %d\n", n_orders);
        if(next_order == NULL || n_orders == 0) {
            running[chef_info->id] = false;
            sem_post(sem_order);
            return NULL;
        }

        sem_post(sem_order);
        chef_info->status = 1;

        get_ingredients(next_order);

        chef_info->status = 2;
        

        for(int i = 0; i < 3; i++) {
            functions[i]();
            chef_info->status = i + 2;
            sleep(1);
        }

        sleep(random() % 3);
    }
}