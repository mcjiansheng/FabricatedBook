//
// Created by 48811 on 25-1-14.
//

#ifndef SLAYTHESPIRE_CARD_H
#define SLAYTHESPIRE_CARD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Player;
struct Enemy;
typedef struct Buff {
    int fragile, block_reduction, resistance, block_increase, weak, strength, dizziness, poisoning, withering, flame, freezing, lightning;
    int armor, undead, extra_energy[3];
} Buff;
typedef struct {
    char *name;
    int cost;
    bool exhaust;
    int type;//1:攻击 2:防御 3:装备 4:技能
    int career;
    bool need_aim;//是否需要瞄准
    void (*effect)(struct Player *, struct Enemy *);

    char *description;
} Card;
extern Card main_card[4][50];
extern int main_cardnum[4];
typedef struct Potion {
    char *name;
    bool need_aim;

    void (*effect)(struct Player *, struct Enemy *);
} Potion;
typedef struct Player {
    int maxhp, hp, coin, energy, block, times;
    int player_career;//1:战士 2:法师 3:女巫
    Card **hand; // 手牌
    int hand_size, hand_type[5];
    Card **deck; // 牌库
    int deck_size;
    Card **discard_pile; // 弃牌堆
    int discard_pile_size;
    Card **sum_deck;//总牌堆
    int sum_deck_size;
    Buff buff;
} Player;

typedef struct Enemy {
    int hp, block;
    Buff buff;
} Enemy;
extern int main_Enemynum;
extern Enemy *main_enemy[3];

void init_card();

void init_buff(Buff *buff);

Card *create_card(char *name, int cost, int type, int career, void (*effect)(struct Player *, struct Enemy *));

Player *init_player(int hp, int career);

void draw_card(Player *player);//抽牌

void use_card(Player *player, int card_index, Enemy *enemy);//出牌

void discard_card(Player *player, int card_index);//弃牌

void shuffle_discard_pile_to_deck(Player *player);//洗牌
void attack(Player *player, Enemy *enemy);

void Player_attack_enemy(Player *player, Enemy *enemy, int damage);

void Enemy_be_attack(Enemy *enemy, int damage);

void Player_get_block(Player *player, int block);

void defense(Player *player, Enemy *enemy);

void add_card_to_bag(Player *player, Card *card);

#endif //SLAYTHESPIRE_CARD_H
