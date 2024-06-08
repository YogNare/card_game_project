#include "slay_the_spire_cards_func.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void card_action_attack_1(Player *player, Enemy *enemy) {
    player_attack(player, enemy, CARD_ATTACK_1_DAMAGE);
}

void card_action_attack_2(Player *player, Enemy *enemy) {
    player_attack(player, enemy, CARD_ATTACK_2_DAMAGE);
}

void card_action_defend(Player *player, Enemy *enemy) {
    player_defend(player, CARD_DEFENSE_AMOUNT);
}

void init_card_deck(CardDeck *deck) {
    deck->card_count = 11;
    for (int i = 0; i < 5; i++) {
        deck->cards[i] = (Card){.id = i + 1, .name = "Strike", .cost = CARD_ATTACK_1_COST, .action_type = ATTACK, .value = CARD_ATTACK_1_DAMAGE, .action = card_action_attack_1};
        deck->cards[i + 5] = (Card){.id = i + 6, .name = "Defend", .cost = CARD_DEFENSE_COST, .action_type = DEFENSE, .value = CARD_DEFENSE_AMOUNT, .action = card_action_defend};
    }
    deck->cards[10] = (Card){.id = 11, .name = "Heavy Strike", .cost = CARD_ATTACK_2_COST, .action_type = ATTACK, .value = CARD_ATTACK_2_DAMAGE, .action = card_action_attack_2};
    shuffle_deck(deck);
}

Card draw_card(CardDeck *deck) {
    if (deck->card_count > 0) {
        return deck->cards[--deck->card_count];
    } else {
        printf("Deck is empty!\n");
        return (Card){0};
    }
}

void shuffle_deck(CardDeck *deck) {
    srand(time(NULL));
    for (int i = deck->card_count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

void draw_cards(Player *player, int num_cards) {
    for (int i = 0; i < num_cards; i++) {
        if (player->drawPile.card_count == 0 && player->discardPile.card_count > 0) {
            for (int j = 0; j < player->discardPile.card_count; j++) {
                player->drawPile.cards[player->drawPile.card_count++] = player->discardPile.cards[j];
            }
            player->discardPile.card_count = 0;
            shuffle_deck(&player->drawPile);
        }

        if (player->drawPile.card_count > 0) {
            Card card = draw_card(&player->drawPile);
            player->hand.cards[player->hand.card_count++] = card;
        }
    }
}

void play_card(Card *card, Player *player, Enemy *enemy) {
    card->action(player, enemy);
    player->discardPile.cards[player->discardPile.card_count++] = *card;  // Сбрасываем карту после использования
}
