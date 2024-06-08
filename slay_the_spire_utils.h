#pragma once
#include <SDL2/SDL.h>

void render_text(SDL_Renderer *renderer, const char *text, int x, int y);
void render_centered_text(SDL_Renderer *renderer, const char *text, SDL_Rect rect);
void render_multiline_text(SDL_Renderer *renderer, const char *text, SDL_Rect rect);
