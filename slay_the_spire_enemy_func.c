#include "slay_the_spire_enemy_func.h"
#include <stdio.h>
#include <string.h>

void init_enemy(Enemy *enemy, EnemyType type) {
    memset(enemy, 0, sizeof(Enemy)); // Инициализация всех полей структуры нулями

    switch (type) {
        case ENEMY_TYPE_1:
            enemy->health = 50;
            enemy->max_health = 50;
            enemy->attack_power = 10;
            enemy->defense = 5;
            snprintf(enemy->name, sizeof(enemy->name), "Enemy 1");
            enemy->actions[0] = enemy_attack;
            enemy->actions[1] = (void (*)(struct Enemy*, struct Player*))enemy_defend;
            enemy->actions[2] = (void (*)(struct Enemy*, struct Player*))enemy_do_nothing;
            enemy->current_action = 0;
            break;
        case ENEMY_TYPE_2:
            enemy->health = 70;
            enemy->max_health = 70;
            enemy->attack_power = 15;
            enemy->defense = 10;
            snprintf(enemy->name, sizeof(enemy->name), "Enemy 2");
            enemy->actions[0] = berserker_attack;
            enemy->actions[1] = (void (*)(struct Enemy*, struct Player*))enemy_defend;
            enemy->actions[2] = (void (*)(struct Enemy*, struct Player*))enemy_do_nothing;
            enemy->current_action = 0;
            break;
        case ENEMY_TYPE_3:
            enemy->health = 100;
            enemy->max_health = 100;
            enemy->attack_power = 20;
            enemy->defense = 15;
            snprintf(enemy->name, sizeof(enemy->name), "Enemy 3");
            enemy->actions[0] = berserker_attack;
            enemy->actions[1] = (void (*)(struct Enemy*, struct Player*))enemy_defend;
            enemy->actions[2] = (void (*)(struct Enemy*, struct Player*))enemy_do_nothing;
            enemy->current_action = 0;
            break;
        default:
            printf("Unknown enemy type\n");
            break;
    }
}

void enemy_attack(struct Enemy *enemy, struct Player *player) {
    player_take_damage(player, enemy->attack_power);
}

void enemy_defend(struct Enemy *enemy) {
    enemy->defense += 5;
}

void enemy_do_nothing(struct Enemy *enemy) {
    // Enemy does nothing this turn
}

void berserker_attack(struct Enemy *enemy, struct Player *player) {
    int damage = enemy->attack_power * 2; // Удвоенная сила атаки
    player_take_damage(player, damage);
}

void enemy_turn(struct Enemy *enemy, struct Player *player) {
    enemy->actions[enemy->current_action](enemy, player);
    enemy->current_action = (enemy->current_action + 1) % 3;
}
