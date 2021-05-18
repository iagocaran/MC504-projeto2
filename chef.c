#include "chef.h"
#ifdef WIN32
    #include <windows.h>
    #define sleep(X)(Sleep(1000 * (X)))
    #ifndef random
        #define random()(rand())
    #endif
#else
    #include <unistd.h>
#endif
#include <semaphore.h>
#include <stdio.h>

int get_ingredients(chef * chef_info, order *order){
    for (int i = 0; i < 4; i++) {
        if ((*order)[i] == null)
            break;
        printf("ingredient:%d\n", (*order)[i]);
        chef_info->ingredient = (*order)[i];
        sem_wait(sem_ingredients[(*order)[i]]);
        sleep(random() % 3 + 2);
        sem_post(sem_ingredients[(*order)[i]]);
    }
    return 1;
}

int cut_ingredients() {
    sleep(random() % 3 + 2);
    return 1;
}

int cook_meal() {
    sleep(random() % 3 + 2);
    return 1;
}

int deliver_meal() {
    sleep(random() % 3 + 2);
    return 1;
}

void* t_chef(void* info) {
    chef* chef_info = (chef*) info;
    running[chef_info->id] = true;

    typedef int (*function)();
    function functions[3] = { &cut_ingredients, &cook_meal, &deliver_meal };

    sleep(random() % 3 + 3);

    while (1) {
        printf("chef: %d\n", chef_info->id - 1);
        sem_wait(sem_order);
        printf("getting next order\n");        
        order* next_order = get_next_order();
        printf("orders remaining: %d\n", n_orders);
        if(next_order == NULL || n_orders == 0) {
            running[chef_info->id - 1] = false;
            sem_post(sem_order);
            return NULL;
        }

        chef_info->status = STARTING;
        sem_post(sem_order);
        chef_info->status = GET_INGREDIENT;
        get_ingredients(chef_info, next_order);

        for(int i = 0; i < 3; i++) {
            chef_info->status += 1;
            functions[i]();
            // sleep(3);
        }

        chef_info->status = WAITING;
        sleep(random() % 3 + 3);
    }
}

void drawChef(chef * target) {
    int x = 5, y = 8, l = 2, c = 0;
    switch (target->status) {
        case WAITING:
        case STARTING:
            switch (target->id - 1) {
                case 0:
                    x = 4;
                    y = 5;
                    break;
                case 1:
                    x = 6;
                    y = 5;
                    break;
            }
            break;
        case GET_INGREDIENT:
            switch (target->ingredient) {
                case null:
                    break;
                case tomato:
                    x = 1;
                    y = 6;
                    break;
                case lettuce:
                    x = 2;
                    y = 6;
                    break;
                case cheese:
                    x = 7;
                    y = 3;
                    l = 0;
                    c = 0;
                    break;
                case meat:
                    x = 8;
                    y = 3;
                    l = 0;
                    c = 0;
                    break;
                case onions:
                    x = 3;
                    y = 6;
                    break;
                case noodles:
                    x = 8;
                    y = 6;
                    break;
                case bread:
                    x = 6;
                    y = 6;
                    break;
                case dough:
                    x = 7;
                    y = 6;
                    break;
            }
            break;
        case CUTTING:
            x = 5;
            y = 3;
            l = 0;
            c = 0;
            break;
        case COOKING:
            x = 3;
            y = 3;
            l = 0;
            c = 0;
            break;
        case DELIVERING:
            x = 5;
            y = 6;
            l = 6;
            c = 1;
            break;
    }
    drawSprite(x * 64 - 32, y * 64 - 64, target->img, l, c);
}
