#pragma once
#include "slay_the_spire_type.h"

int basic_attack_func(void *p, void *e);


Card_list *card_init_list();


void card_free_list(Card_list *list);


Card_node *card_create_node(SDL_Rect *rect, int type);


int card_add_node(Card_list *list, int type, int x, int y, int w, int h);


int card_delete_by_id(Card_list *list, int id);