#include "order.h"

order * getOrder() {
    order * out = (order*) calloc(1, sizeof(order));
    int recipe = random() % 4;
    (*out)[0] = recipes[recipe].required[0];
    (*out)[1] = recipes[recipe].required[1];
    int optionals = random() % 3;
    bool choose[4] = { false, false, false, false};
    for (int i = 0; i < optionals; i++) {
        do {
            int t = random() % 3;
            if (!choose[t]) {
                (*out)[i + 2] = recipes[recipe].optional[t];
                choose[t] = true;
            }
        } while ((*out)[i + 2] == null);
    }
    return out;
}
void fill_queue() {
    recipes[0] = (recipeTemplate) { { bread, meat }, { tomato, lettuce, cheese } };
    recipes[1] = (recipeTemplate) { { noodles, tomato }, { cheese, onions, meat } };
    recipes[2] = (recipeTemplate) { { dough, lettuce }, { cheese, tomato, onions } };

    n_orders = ORDERS;
    order_queue = calloc(ORDERS, sizeof(order*));
    for (int i = 0; i < ORDERS; i++) {
        order_queue[i] = getOrder();
    }
}

order * get_next_order() {
    if(n_orders == 0) return NULL;
    
    order * next_order = order_queue[0];

    n_orders = n_orders - 1;
    for(int i = 1; i < n_orders; i++)
        order_queue[i - 1] = order_queue[i];
    
    order_queue[n_orders] = NULL;
    return next_order;
}
