//
// Created by 48811 on 25-1-14.
//

#ifndef SLAYTHESPIRE_CARD_H
#define SLAYTHESPIRE_CARD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "collection.h"

struct Player;
struct Enemy;
typedef struct Buff {
    int fragile, block_reduction, resistance, block_increase, weak, strength, dizziness, poisoning, withering, withering_times, flame, freezing, lightning;
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
    char *discribe;
    SDL_Color color;

    void (*effect)(struct Player *);
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
    int sum_Potion;
    Potion **potions;
    int sum_collection;
    Collection **collections;
    Buff buff;
    int extra_damage;
    bool enter_allowance;
} Player;
typedef struct Enemy_skill {
    int type;//1 atk 2def 3wek 4inc 5ukn
    char *qua;

    void (*effect)(struct Player *, struct Enemy *);
} Enemy_skill;
typedef struct Enemy {
    char *name;
    SDL_Texture *texture;
    int hp, block;
    int skill_num;
    Enemy_skill skill[7];
    Buff buff;
    int next_step;
} Enemy;
extern int main_Enemynum;
extern Enemy main_enemy[3];

void print_everycard(SDL_Renderer *renderer, Player *player, int y);

void print_everycollection(SDL_Renderer *renderer, Player *player, int y);

void init_card();

void init_potion();

void init_enemy(SDL_Renderer *renderer);

void init_buff(Buff *buff);

void buff_decrease(Buff *buff);

Card *create_card(char *name, int cost, int type, int career, void (*effect)(struct Player *, struct Enemy *));

Player *init_player(int hp, int career);

void draw_card(Player *player);//抽牌

void use_card(Player *player, int *card_index, Enemy *enemy);//出牌


void discard_card(Player *player, int card_index);//弃牌

void shuffle_discard_pile_to_deck(Player *player);//洗牌
void attack(Player *player, Enemy *enemy);

void Enemy_be_attack(Enemy *enemy, int damage);

void Player_get_block(Player *player, int block);

void Player_attack_enemy(Player *player, Enemy *enemy, int damage);

void player_be_attacked(Player *player, Enemy *enemy, int damage);

void defense(Player *player, Enemy *enemy);

void add_card_to_bag(Player *player, Card *card);

void add_card_to_deck(Player *player, Card *card);

void delete_card_from_bag(Player *player, int index);

void get_potion(Player *player, Potion *potion);

void discard_potion(Player *player, int index);

void use_potion(Player *player, int index);

void player_get_hp(Player *player, int num);

void player_get_collection(Player *player, int x, int y);

#endif //SLAYTHESPIRE_CARD_H
