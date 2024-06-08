#pragma once

#include "slay_the_spire_type.h"

void card_action_attack_1(struct Player *player, struct Enemy *enemy);
void card_action_attack_2(struct Player *player, struct Enemy *enemy);
void card_action_defend(struct Player *player, struct Enemy *enemy);

void init_card_deck(CardDeck *deck);
Card draw_card(CardDeck *deck);
void shuffle_deck(CardDeck *deck);
void draw_cards(Player *player, int num_cards);
void play_card(Card *card, Player *player, Enemy *enemy);
