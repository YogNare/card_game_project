#pragma once
#include "slay_the_spire_type.h"


Enemy_list *enemy_init_list();


void enemy_free_list(Enemy_list *list);


Enemy_node *enemy_create_node(SDL_Rect *rect, int hp);


int enemy_add_node(Enemy_list *list, int hp, int x, int y, int w, int h);


int enemy_delete_by_id(Enemy_list *list, int id);