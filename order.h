#ifndef PROJETO2_ORDER_H
#define PROJETO2_ORDER_H

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
    int nOptions;
    int maxOptional;
} recipeTemplate;

typedef ingredient order[6];

recipeTemplate recipes[] = {
        { { bread, meat }, { tomato, lettuce, cheese }, 3, 2 },
        { { noodles, tomato }, { cheese, onions, meat }, 3, 2 },
        { { dough, lettuce }, { cheese, tomato, onions }, 3, 2 },
};

order * getOrder();
order * out = calloc(1, sizeof(order));
order **order_queue;
int n_orders;
sem_t *sem_order;
sem_t *sem_ingredients[9];

recipeTemplate recipes[4];

order * getOrder();
void fill_queue();

order * get_next_order();
#endif //PROJETO2_ORDER_H
