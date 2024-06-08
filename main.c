#include "slay_the_spire_battle.h"
#include "slay_the_spire_map.h"
#include "slay_the_spire_start_menu.h"
#include "slay_the_spire_handler.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;
Player player;
Enemy currentEnemy;
int gameState = START_MENU_STATE;

void initialize_game();
void run_game_loop();
void update_game_state();
void render_game(SDL_Renderer *renderer);

void initialize_game() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        return;
    }

    window = SDL_CreateWindow("Slay the Spire", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return;
    }

    font = TTF_OpenFont("/usr/share/fonts/JetBrainsMono/JetBrainsMonoNerdFont-Light.ttf", 24);
    if (!font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return;
    }

    initialize_start_menu();
}

void run_game_loop() {
    int isRunning = 1;
    SDL_Event e;

    while (isRunning) {
        handle_events(&isRunning);
        update_game_state();
        render_game(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

void update_game_state() {
    switch (gameState) {
        case START_MENU_STATE:
            // Update start menu
            break;
        case MAP_STATE:
            // Update map
            break;
        case BATTLE_STATE:
            update_battle();
            break;
        default:
            break;
    }
}

void render_game(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    switch (gameState) {
        case START_MENU_STATE:
            render_start_menu(renderer);
            break;
        case MAP_STATE:
            render_map(renderer);
            break;
        case BATTLE_STATE:
            render_battle(renderer);
            break;
        default:
            break;
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char *args[]) {
    initialize_game();
    run_game_loop();
    return 0;
}
