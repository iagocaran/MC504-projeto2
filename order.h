#ifndef PROJETO2_ORDER_H
#define PROJETO2_ORDER_H

#ifdef WIN32
    #ifndef random
        #define random()(rand())
    #endif
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <string.h>

#define ORDERS 10

typedef enum ingredient {
    null = 0,
    tomato,
    lettuce,
    cheese,
    meat,
    onions,
    noodles,
    bread,
    dough
} ingredient;

typedef struct recipeTemplate {
    ingredient required[2];
    ingredient optional[4];
} recipeTemplate;

typedef ingredient order[6];

order * getOrder();
order **order_queue;
int n_orders;
sem_t *sem_order;
sem_t *sem_ingredients[9];

recipeTemplate recipes[3];

void fill_queue();

order * get_next_order();
#endif //PROJETO2_ORDER_H
