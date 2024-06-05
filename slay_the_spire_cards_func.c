#include "slay_the_spire_cards_func.h"


int basic_attack_func(void *p, void *e) {

    Enemy_node *enemy = (Enemy_node *) e;
    Player *player = (Player *) p;

    enemy->hp -= 200;

    return 0;
}


char *ultimate_card_list[2] = {"Attack\n10", "Defense\n10"};


Card_list *card_init_list() {
    Card_list *list = (Card_list *)malloc(sizeof(Card_list));
    list->len = 0;
    list->head = NULL;
    return list;
}


void card_free_list(Card_list *list) {
    Card_node *free_node;
    while (list->head != NULL) {
        free_node = list->head;
        list->head = list->head->next;
        free(free_node);
    }
    free(list);
}


Card_node *card_create_node(SDL_Rect *rect, int type) {
    Card_node *new_node = (Card_node *)malloc(sizeof(Card_node));
    new_node->value = *rect;
    new_node->next = NULL;
    new_node->desc = ultimate_card_list[type];
    new_node->func = basic_attack_func;
    return new_node;
}


int card_add_node(Card_list *list, int type, int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    Card_node *new_node = card_create_node(&rect, type);

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Card_node *help_node = list->head;
        while (help_node->next != NULL) {
            help_node = help_node->next;
        }
        help_node->next = new_node;
    }
    list->len++;
    return 0;
}


int card_delete_by_id(Card_list *list, int id) {
    if (id >= list->len) {
        return 1;
    }

    Card_node *delete_node = list->head;
    Card_node *current_node = list->head;

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