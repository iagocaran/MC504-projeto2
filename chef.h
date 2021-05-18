#ifndef PROJETO2_CHEF_H
#define PROJETO2_CHEF_H

#include "order.h"
#include "graphicInterface.h"

typedef enum { WAITING, STARTING, GET_INGREDIENT, CUTTING, COOKING, DELIVERING } chef_status;

typedef struct chef {
  int id;
  chef_status status;
  ingredient ingredient;
  SpriteSheet * img;
  order * order;
} chef;

int get_ingredients(chef * chef_info, order *order);
int cut_ingredients();
int cook_meal();
int deliver_meal();
void drawChef(chef * target);
void drawOrder(chef * target, SpriteSheet * ss);
void* t_chef(void* v);

bool * running;

#endif //PROJETO2_CHEF_H