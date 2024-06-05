#include "slay_the_spire_handler.h"


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


int battle_mouse_click_handler(SDL_Event *event, Enemy_list *enemy_list, int *choose_rect, Player *player) {
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
                if (enemy->value.x < event->button.x && event->button.x < enemy->value.x + enemy->value.w &&
                    enemy->value.y < event->button.y && event->button.y < enemy->value.y + enemy->value.h) {

                    card_help_node->func(player, enemy);
                    if (enemy->hp <= 0) {
                        //delete_by_id(rect_list, *choose_rect - 1);
                        enemy_delete_by_id(enemy_list, i);
                        printf("enemy %d - die\n", i);
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

        if (card_help_node->value.x < event->button.x && event->button.x < card_help_node->value.x + card_help_node->value.w &&
            card_help_node->value.y < event->button.y && event->button.y < card_help_node->value.y + card_help_node->value.h) {
            if (event->button.button == SDL_BUTTON_LEFT && *choose_rect == 0) {
                *choose_rect = i + 1;
                card_help_node->value.y -= 50;
                printf("Hahaha click - %d\n", i);
                break;
            }
        }
    }

    return 0;
}


int start_menu_mouse_click_handler(SDL_Event *event, int *mod, Rect_Text_List *start_menu_list, bool *running) { 

    for (int i = 0; i < start_menu_list->len; i ++) {
        if (start_menu_list->list[i].rect.x < event->button.x && event->button.x < start_menu_list->list[i].rect.x + start_menu_list->list[i].rect.w &&
        start_menu_list->list[i].rect.y < event->button.y && event->button.y < start_menu_list->list[i].rect.y + start_menu_list->list[i].rect.h) {
            
            start_menu_list->list[i].func(mod, running);

            break;
        }
    }

    return 0;
}


int map_mouse_click_handler(SDL_Event *event, int *mod, SDL_Rect *map_rect, bool *running, int *battle_start) {

    if (map_rect->x < event->button.x && event->button.x < map_rect->x + map_rect->w &&
        map_rect->y < event->button.y && event->button.y < map_rect->y + map_rect->h) {
        
        *mod = BATTLE_MOD;
        *battle_start = 1;
    }

    return 0;
}