#include "slay_the_spire_battle.h"
#include "slay_the_spire_utils.h"
#include "slay_the_spire_handler.h"
#include "slay_the_spire_cards_func.h"
#include "slay_the_spire_enemy_func.h"
#include <stdio.h>

int selected_card = -1;
int player_turn = 1;
Uint32 enemy_turn_end_time = 0;

extern int gameState;
extern Player player;
extern Enemy currentEnemy;

void initialize_battle() {
    player.health = 100;
    player.max_health = 100;
    player.energy = 3;
    player.defense = 0;
    player.drawPile.card_count = 0;
    player.discardPile.card_count = 0;
    player.hand.card_count = 0;
    init_card_deck(&player.drawPile);
    draw_cards(&player, 5);

    init_enemy(&currentEnemy, ENEMY_TYPE_1); // Инициализация врага
    printf("Battle initialized.\n");
}

void update_battle() {
    if (player.health <= 0) {
        end_game();
    }

    if (currentEnemy.health <= 0) {
        end_battle();
    }

    if (!player_turn && SDL_GetTicks() > enemy_turn_end_time) {
        player.energy = 3;
        draw_cards(&player, 5);
        player_turn = 1;
    }
}

void render_battle(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
    SDL_RenderClear(renderer);

    SDL_Rect player_rect = {100, 100, 150, 250};
    SDL_Rect enemy_rect = {WINDOW_WIDTH - 250, 100, 150, 250};

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &player_rect);
    render_centered_text(renderer, "Hero", player_rect);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &enemy_rect);
    render_centered_text(renderer, currentEnemy.name, enemy_rect);

    char player_hp[16];
    sprintf(player_hp, "HP: %d/%d", player.health, player.max_health);
    render_centered_text(renderer, player_hp, (SDL_Rect){player_rect.x, player_rect.y + player_rect.h, player_rect.w, 30});

    char enemy_hp[16];
    sprintf(enemy_hp, "HP: %d/%d", currentEnemy.health, currentEnemy.max_health);
    render_centered_text(renderer, enemy_hp, (SDL_Rect){enemy_rect.x, enemy_rect.y + enemy_rect.h, enemy_rect.w, 30});

    char player_defense[16];
    sprintf(player_defense, "Def: %d", player.defense);
    render_centered_text(renderer, player_defense, (SDL_Rect){player_rect.x, player_rect.y + player_rect.h + 30, player_rect.w, 30});

    char enemy_defense[16];
    sprintf(enemy_defense, "Def: %d", currentEnemy.defense);
    render_centered_text(renderer, enemy_defense, (SDL_Rect){enemy_rect.x, enemy_rect.y + enemy_rect.h + 30, enemy_rect.w, 30});

    if (player_turn) {
        render_centered_text(renderer, "Player Turn", (SDL_Rect){WINDOW_WIDTH / 2 - 50, 50, 100, 30});
    } else {
        render_centered_text(renderer, "Enemy Turn", (SDL_Rect){WINDOW_WIDTH / 2 - 50, 50, 100, 30});
    }

    char enemy_intent[64];
    snprintf(enemy_intent, sizeof(enemy_intent), "a: %d d: %d", currentEnemy.attack_power, currentEnemy.defense);
    render_centered_text(renderer, enemy_intent, (SDL_Rect){enemy_rect.x, enemy_rect.y - 30, enemy_rect.w, 30});

    for (int i = 0; i < player.hand.card_count; i++) {
        int card_spacing = (WINDOW_WIDTH - 200) / player.hand.card_count;
        SDL_Rect card_rect = {100 + i * card_spacing, selected_card == i ? 420 : 450, 150, 250}; // Поднимаем выбранную карту
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &card_rect);
        char card_info[64];
        sprintf(card_info, "%d\n\n%s\n\n%d", player.hand.cards[i].cost, player.hand.cards[i].name, player.hand.cards[i].value);
        render_multiline_text(renderer, card_info, card_rect);
    }

    // Отрисовка шкалы энергии
    for (int i = 0; i < player.energy; i++) {
        SDL_Rect energy_rect = {50 + i * 40, 50, 30, 30};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &energy_rect);
    }

    render_end_turn_button(renderer);

    SDL_RenderPresent(renderer);
}

void handle_battle_click(int x, int y) {
    if (is_end_turn_button_clicked(x, y)) {
        end_turn();
        return;
    }

    for (int i = 0; i < player.hand.card_count; i++) {
        int card_spacing = (WINDOW_WIDTH - 200) / player.hand.card_count;
        SDL_Rect card_rect = {100 + i * card_spacing, 450, 150, 250};
        if (x >= card_rect.x && x <= card_rect.x + card_rect.w &&
            y >= card_rect.y && y <= card_rect.y + card_rect.h) {
            selected_card = i;
            return;
        }
    }

    SDL_Rect player_rect = {100, 100, 150, 250};
    SDL_Rect enemy_rect = {WINDOW_WIDTH - 250, 100, 150, 250};

    if (x >= player_rect.x && x <= player_rect.x + player_rect.w &&
        y >= player_rect.y && y <= player_rect.y + player_rect.h) {
        if (selected_card != -1 && player.hand.cards[selected_card].action_type == DEFENSE && player.hand.cards[selected_card].cost <= player.energy) {
            player.energy -= player.hand.cards[selected_card].cost;
            play_card(&player.hand.cards[selected_card], &player, &currentEnemy);
            for (int j = selected_card; j < player.hand.card_count - 1; j++) {
                player.hand.cards[j] = player.hand.cards[j + 1];
            }
            player.hand.card_count--;
            selected_card = -1;
            return;
        }
    }

    if (x >= enemy_rect.x && x <= enemy_rect.x + enemy_rect.w &&
        y >= enemy_rect.y && y <= enemy_rect.y + enemy_rect.h) {
        if (selected_card != -1 && player.hand.cards[selected_card].action_type == ATTACK && player.hand.cards[selected_card].cost <= player.energy) {
            player.energy -= player.hand.cards[selected_card].cost;
            play_card(&player.hand.cards[selected_card], &player, &currentEnemy);
            for (int j = selected_card; j < player.hand.card_count - 1; j++) {
                player.hand.cards[j] = player.hand.cards[j + 1];
            }
            player.hand.card_count--;
            selected_card = -1;
            return;
        }
    }
}

void handle_right_click() {
    selected_card = -1;
}

void player_attack(Player *player, Enemy *enemy, int damage) {
    int effective_damage = damage - enemy->defense;
    if (effective_damage > 0) {
        enemy->health -= effective_damage;
    }
    enemy->defense = 0;
}

void player_defend(Player *player, int defense) {
    player->defense += defense;
}

void player_take_damage(Player *player, int damage) {
    int effective_damage = damage - player->defense;
    if (effective_damage > 0) {
        player->health -= effective_damage;
    }
    player->defense = 0;
}

void enemy_take_damage(Enemy *enemy, int damage) {
    int effective_damage = damage - enemy->defense;
    if (effective_damage > 0) {
        enemy->health -= effective_damage;
    }
    enemy->defense = 0;
}

void end_turn() {
    if (player_turn) {
        for (int i = 0; i < player.hand.card_count; i++) {
            player.discardPile.cards[player.discardPile.card_count++] = player.hand.cards[i];
        }
        player.hand.card_count = 0;

        player_turn = 0;
        currentEnemy.defense = 0;
        enemy_turn(&currentEnemy, &player);
        enemy_turn_end_time = SDL_GetTicks() + 1000; // 1 секунда задержки для хода врага
    }
}

void end_battle() {
    gameState = MAP_STATE;
    printf("Battle ended.\n");
}

void end_game() {
    gameState = START_MENU_STATE;
    printf("Game over.\n");
}

int is_end_turn_button_clicked(int x, int y) {
    SDL_Rect end_turn_button = {WINDOW_WIDTH - 150, WINDOW_HEIGHT - 50, 100, 30};
    if (x >= end_turn_button.x && x <= end_turn_button.x + end_turn_button.w &&
        y >= end_turn_button.y && y <= end_turn_button.y + end_turn_button.h) {
        return 1;
    }
    return 0;
}

void render_end_turn_button(SDL_Renderer *renderer) {
    SDL_Rect end_turn_button = {WINDOW_WIDTH - 150, WINDOW_HEIGHT - 50, 100, 30};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &end_turn_button);
    render_centered_text(renderer, "End Turn", end_turn_button);
}
