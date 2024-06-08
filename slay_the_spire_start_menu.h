#pragma once

#include <SDL2/SDL.h>

void initialize_start_menu();
void render_start_menu(SDL_Renderer *renderer); // Добавим объявление
void handle_start_menu_click(int x, int y);
