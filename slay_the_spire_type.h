#pragma once


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define WINDOW_HEIGHT 900
#define WINDOW_WIDTH 1200
#define WINDOW_BACKGROUND_COLOR 35, 35, 35, 255
#define START_MENU 0
#define BATTLE_MOD 1
#define MAP 2
#define AWARDS 3


typedef struct Card_node {
    SDL_Rect value;
    int (*func)(void *, void *);
    char *desc;
    struct Card_node *next;
} Card_node;


typedef struct {
    int len;
    Card_node *head;
} Card_list;


typedef struct Enemy_node {
    int hp;
    int defense;
    int action;
    int count_action;
    int *actions;
    double attack_factor;
    double defense_factor;
    char *desc;
    SDL_Rect value;
    struct Enemy_node *next;
} Enemy_node;


typedef struct {
    
    int len;
    Enemy_node *head;
} Enemy_list;


typedef struct Player {
    
    int hp;
    int defense;
    int count_cards;
    Card_list *reset_pile;
    Card_list *pile_of_goodness;
    Card_list *hand;
    double attack_factor;
    double defense_factor;
    SDL_Rect hero_rect;
    SDL_Rect energy_rect;
    int cur_energy;
    int max_energy;
} Player;


typedef struct {

    SDL_Rect rect;
    char *text;
    int (*func)();
} Rect_Text;


typedef struct {

    Rect_Text *list;
    int len;
} Rect_Text_List;


typedef struct {

    int x;
    int y;
    int w;
    int h;
} Rect_size;