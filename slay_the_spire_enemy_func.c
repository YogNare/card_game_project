#include "slay_the_spire_enemy_func.h"


Enemy_list *enemy_init_list() {
    Enemy_list *list = (Enemy_list *)malloc(sizeof(Enemy_list));
    list->len = 0;
    list->head = NULL;
    return list;
}


void enemy_free_list(Enemy_list *list) {
    Enemy_node *free_node;
    while (list->head != NULL) {
        free_node = list->head;
        list->head = list->head->next;
        free(free_node);
    }
    free(list);
}


Enemy_node *enemy_create_node(SDL_Rect *rect, int hp) {
    Enemy_node *new_node = (Enemy_node *)malloc(sizeof(Enemy_node));
    new_node->value = *rect;
    new_node->next = NULL;
    new_node->hp = hp;
    return new_node;
}


int enemy_add_node(Enemy_list *list, int hp, int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    Enemy_node *new_node = enemy_create_node(&rect, hp);

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Enemy_node *help_node = list->head;
        while (help_node->next != NULL) {
            help_node = help_node->next;
        }
        help_node->next = new_node;
    }
    list->len++;
    return 0;
}


int enemy_delete_by_id(Enemy_list *list, int id) {
    if (id >= list->len) {
        return 1;
    }

    Enemy_node *delete_node = list->head;
    Enemy_node *current_node = list->head;

    if (id == 0) {
        list->head = list->head->next;
        list->len--;
        free(delete_node);
        return 0;
    }

    for (int i = 1; i < id; i++) {
        current_node = current_node->next;
    }

    delete_node = current_node->next;
    current_node->next = delete_node->next;
    free(delete_node);
    list->len--;

    return 0;
}