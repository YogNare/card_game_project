#include "slay_the_spire_handler.h"
#include "slay_the_spire_cards_func.h"


bool check_in_box(SDL_Event *event, SDL_Rect *rect) {

    if (rect->x < event->button.x && event->button.x < rect->x + rect->w &&
        rect->y < event->button.y && event->button.y < rect->y + rect->h)
        return true;
    else return false;
}


int keyboard_handler(SDL_Event *event, bool *running) {
    switch (event->key.keysym.sym) {
        case SDLK_DOWN:
            printf("down\n");
            break;
        case SDLK_UP:
            printf("up\n");
            break;
        case SDLK_ESCAPE:
            printf("esc\n");
            *running = false;
            break;
        case SDLK_0:
            printf("zero\n");
            break;
        default:
            printf("wtf\n");
            break;
    }

    return 0;
}


int mouse_move_handler(SDL_Event *event) {
    printf("(%d; %d)\n", event->motion.x, event->motion.y);
    return 0;
}


int battle_mouse_click_handler(SDL_Event *event, Enemy_list *enemy_list, int *choose_rect, Player *player, int *turn) {
    Card_node *card_help_node;

    if (*choose_rect != 0) {
        card_help_node = player->hand->head;
        for (int i = 1; i < *choose_rect; i++) {
            card_help_node = card_help_node->next;
        }

        if (event->button.button == SDL_BUTTON_RIGHT) {
            card_help_node->value.y += 50;
            *choose_rect = 0;
        } else if (event->button.button == SDL_BUTTON_LEFT) {
            Enemy_node *enemy = enemy_list->head;

            for (int i = 0; i < enemy_list->len; i++) {
                if (check_in_box(event, &enemy->value)) {

                    card_help_node->func(player, enemy);
                    card_delete_by_id(player->hand, (*choose_rect) - 1);

                    if (enemy->hp <= 0) {
                        enemy_delete_by_id(enemy_list, i);
                        printf("enemy %d - die\n", i);
                        // printf("%d\n", player->hand->len);
                    }

                    card_help_node->value.y += 50;
                    *choose_rect = 0;

                    printf("enemy - %d\n", i);
                    break;
                }
                enemy = enemy->next;
            }
        }
    }

    for (int i = 0; i < player->hand->len; i++) {
        if (i == 0) card_help_node = player->hand->head;
        else card_help_node = card_help_node->next;

        if (check_in_box(event, &card_help_node->value)) {
            if (event->button.button == SDL_BUTTON_LEFT && *choose_rect == 0) {
                *choose_rect = i + 1;
                card_help_node->value.y -= 50;
                printf("Hahaha click - %d\n", i);
                break;
            }
        }
    }

    if (check_in_box(event, &player->energy_rect)) {

        printf("end player turn\n");
        *turn = ENEMY_TURN;
    }

    return 0;
}


int start_menu_mouse_click_handler(SDL_Event *event, int *mod, Rect_Text_List *start_menu_list, bool *running) { 

    for (int i = 0; i < start_menu_list->len; i ++) {
        if (check_in_box(event, &start_menu_list->list[i]->rect)) {
            
            start_menu_list->list[i]->func(mod, running);

            break;
        }
    }

    return 0;
}


int map_mouse_click_handler(SDL_Event *event, int *mod, SDL_Rect *map_rect, bool *running, int *battle_start) {

    if (event, map_rect) {
        
        *mod = BATTLE_MOD;
        *battle_start = 1;
    }

    return 0;
}


int awards_mouse_click_handler(SDL_Event *event, int *mod, Rect_Text_List *awards_list, bool *running) {

    if (check_in_box(event, &awards_list->list[0]->rect)) {

        printf("I'm here\n");
        *mod = CHOOSE_CARD_MOD;
    }
}