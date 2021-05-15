#ifndef PROJETO2_CHEF_H
#define PROFETO2_CHEF_H

#include "order.h"

typedef enum {WAITING,STARTING,GET_INGREDIENT,CUTTING,COOKING,DELIVERING} chef_status;

// const char* possible_status[] = {"WAITING","STARTING","GET_INGREDIENT","CUTTING","COOKING","DELIVERING"};

typedef struct chef {
  int id;
  int status;
} chef;

int get_ingredients(order *order);
int cut_ingredients();
int cook_meal();
int deliver_meal();
void* t_chef(void* v);

#endif //PROJETO2_CHEF_H