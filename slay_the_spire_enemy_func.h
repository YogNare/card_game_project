#pragma once

#include "slay_the_spire_type.h"

void init_enemy(Enemy *enemy, EnemyType type);
void enemy_turn(Enemy *enemy, Player *player);
void enemy_attack(Enemy *enemy, Player *player);
void enemy_defend(Enemy *enemy);
void enemy_do_nothing(Enemy *enemy);
void berserker_attack(Enemy *enemy, Player *player);
