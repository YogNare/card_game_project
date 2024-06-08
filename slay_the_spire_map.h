#pragma once

#include <SDL2/SDL.h>

extern int gameState; // Объявление переменной

void render_map(SDL_Renderer *renderer);
void handle_map_click(int x, int y);
void increment_player_level();
