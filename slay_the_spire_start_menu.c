#include "slay_the_spire_start_menu.h"
#include "slay_the_spire_utils.h"
#include "slay_the_spire_map.h"
#include "slay_the_spire_type.h"
#include <SDL2/SDL.h>
#include <stdio.h>

extern int gameState;

void initialize_map(); // Объявление функции

void initialize_start_menu() {
    printf("Start menu initialized.\n");
}

void render_start_menu(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
    SDL_RenderClear(renderer);

    SDL_Rect start_button = {WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 50, 200, 100};
    SDL_Rect quit_button = {WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 70, 200, 100};

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &start_button);
    render_centered_text(renderer, "Start Game", start_button);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &quit_button);
    render_centered_text(renderer, "Quit Game", quit_button);

    SDL_RenderPresent(renderer);
}

void handle_start_menu_click(int x, int y) {
    SDL_Rect start_button = {WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 50, 200, 100};
    SDL_Rect quit_button = {WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 70, 200, 100};

    if (x >= start_button.x && x <= start_button.x + start_button.w &&
        y >= start_button.y && y <= start_button.y + start_button.h) {
        gameState = MAP_STATE;
        initialize_map();
    } else if (x >= quit_button.x && x <= quit_button.x + quit_button.w &&
               y >= quit_button.y && y <= quit_button.y + quit_button.h) {
        exit(0);
    }
}
