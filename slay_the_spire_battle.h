#pragma once

#include <SDL2/SDL.h>
#include "slay_the_spire_type.h"

// Объявление глобальных переменных
extern int selected_card;
extern int player_turn;

// Function prototypes
void initialize_battle();
void start_battle();
void update_battle();
void render_battle(SDL_Renderer *renderer);
void handle_battle_click(int x, int y);
void handle_right_click();
void end_turn();
void player_attack(Player *player, Enemy *enemy, int damage);
void player_defend(Player *player, int defense);
void draw_cards(Player *player, int num_cards);
void end_battle();
void end_game();
int is_end_turn_button_clicked(int x, int y);
void render_end_turn_button(SDL_Renderer *renderer);
