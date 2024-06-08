#include "slay_the_spire_handler.h"
#include "slay_the_spire_start_menu.h"
#include "slay_the_spire_map.h"
#include "slay_the_spire_battle.h"
#include <SDL2/SDL.h>

extern int gameState;

void handle_events(int *isRunning) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            *isRunning = 0;
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (gameState == START_MENU_STATE) {
                handle_start_menu_click(x, y);
            } else if (gameState == MAP_STATE) {
                handle_map_click(x, y);
            } else if (gameState == BATTLE_STATE) {
                handle_battle_click(x, y);
            }
        } 
        // else if (e.type == SDL_MOUSEBUTTONUP) {
        //     if (gameState == BATTLE_STATE) {
        //         handle_right_click();
        //     }
        // }
    }
}
