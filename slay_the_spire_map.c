#include "slay_the_spire_map.h"
#include "slay_the_spire_utils.h"
#include "slay_the_spire_battle.h"
#include "slay_the_spire_type.h"
#include <SDL2/SDL.h>

int currentLevel;

extern int gameState;

void initialize_map() {
    currentLevel = 0;
    printf("Map initialized.\n");
}

void render_map(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
    SDL_RenderClear(renderer);

    int node_radius = 20;
    int node_spacing = 100;

    for (int i = 0; i < 5; i++) {
        int x = WINDOW_WIDTH / 2;
        int y = (i + 1) * node_spacing;
        SDL_Rect node_rect = {x - node_radius, y - node_radius, node_radius * 2, node_radius * 2};

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &node_rect);

        char node_label[16];
        sprintf(node_label, "Node %d", i + 1);
        render_centered_text(renderer, node_label, node_rect);
    }

    SDL_RenderPresent(renderer);
}

void handle_map_click(int x, int y) {
    int node_radius = 20;
    int node_spacing = 100;

    for (int i = 0; i < 5; i++) {
        int node_x = WINDOW_WIDTH / 2;
        int node_y = (i + 1) * node_spacing;
        SDL_Rect node_rect = {node_x - node_radius, node_y - node_radius, node_radius * 2, node_radius * 2};

        if (x >= node_rect.x && x <= node_rect.x + node_rect.w &&
            y >= node_rect.y && y <= node_rect.y + node_rect.h) {
            gameState = BATTLE_STATE;
            initialize_battle();
            break;
        }
    }
}
