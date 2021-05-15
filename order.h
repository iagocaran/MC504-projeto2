#ifndef PROJETO2_ORDER_H
#define PROJETO2_ORDER_H

#include <stdlib.h>
#include <stdbool.h>

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
int n_orders = ORDERS;
sem_t *sem_order;

order * getOrder() {
    order * out = (order*) calloc(1, sizeof(order));
    int recipe = random() % 4;
    (*out)[0] = recipes[recipe].required[0];
    (*out)[1] = recipes[recipe].required[1];
    int optionals = random() % (recipes[recipe].maxOptional + 1);
    bool choose[4] = { false, false, false, false};
    for (int i = 0; i < optionals; i++) {
        do {
            int t = random() % (recipes[recipe].nOptions);
            if (!choose[t]) {
                (*out)[i + 2] = recipes[recipe].optional[t];
                choose[t] = true;
            }
        } while ((*out)[i + 2] == null);
    }
    return out;
}
void fill_queue(){
    order_queue = (order**) malloc(ORDERS * sizeof(order*));
    for(int i=0; i< ORDERS; i++){
        order_queue[i] = (order*) malloc(sizeof(order));
        order_queue[i] = getOrder();
    }
}

order * get_next_order() {
    if(n_orders == 0) return NULL;

    order * next_order;

    memcpy(next_order,order_queue[0],sizeof(order));
    n_orders = n_orders - 1;
    for(int i=1;i<n_orders;i++)
        order_queue[i-1] = order_queue[i];

    order_queue[n_orders] = NULL;
    return next_order;
}

#endif //PROJETO2_ORDER_H
