#pragma once
#include "slay_the_spire_type.h"
#include "slay_the_spire_enemy_func.h"


int keyboard_handler(SDL_Event *event, bool *running);


int mouse_move_handler(SDL_Event *event);


int battle_mouse_click_handler(SDL_Event *event, Enemy_list *enemy_list, int *choose_rect, Player *player);


int start_menu_mouse_click_handler(SDL_Event *event, int *mod, Rect_Text_List *start_menu_list, bool *running);


void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, SDL_Rect *rect);


int map_mouse_click_handler(SDL_Event *event, int *mod, SDL_Rect *map_rect, bool *running, int *battle_start);