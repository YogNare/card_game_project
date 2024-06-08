#pragma once

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#define START_MENU_STATE 0
#define MAP_STATE 1
#define BATTLE_STATE 2

#define CARD_ATTACK_1_COST 1
#define CARD_ATTACK_1_DAMAGE 6
#define CARD_ATTACK_2_COST 2
#define CARD_ATTACK_2_DAMAGE 15
#define CARD_DEFENSE_COST 1
#define CARD_DEFENSE_AMOUNT 5

#define ATTACK 0
#define DEFENSE 1

struct Player; // Forward declaration
struct Enemy;  // Forward declaration

typedef struct Card {
    int id;
    char name[20];
    int cost;
    int action_type;
    int value;
    void (*action)(struct Player *player, struct Enemy *enemy);
} Card;

typedef struct CardDeck {
    Card cards[30];
    int card_count;
} CardDeck;

typedef struct Player {
    int health;
    int max_health;
    int energy;
    int defense;
    CardDeck drawPile;
    CardDeck discardPile;
    CardDeck hand;
} Player;

typedef struct Enemy {
    int health;
    int max_health;
    int defense;
    char name[20];
    void (*actions[5])(struct Enemy*, struct Player*);
    int current_action;
    int attack_power;
} Enemy;

typedef enum {
    ENEMY_TYPE_1,
    ENEMY_TYPE_2,
    ENEMY_TYPE_3
} EnemyType;

extern int currentLevel;

void player_attack(Player *player, Enemy *enemy, int damage);
void player_defend(Player *player, int defense);
void player_take_damage(Player *player, int damage);
void enemy_take_damage(Enemy *enemy, int damage);
void init_card_deck(CardDeck *deck);
void draw_cards(Player *player, int num_cards);
void play_card(Card *card, Player *player, Enemy *enemy);
void shuffle_deck(CardDeck *deck);
Card draw_card(CardDeck *deck);
