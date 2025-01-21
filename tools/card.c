//
// Created by 48811 on 25-1-14.
//

#include "card.h"
#include <string.h>
#include <stdlib.h>
#include "button.h"

void print_everycard(SDL_Renderer *renderer, Player *player, int y) {
    int i;
    TTF_Font *font = TTF_OpenFont("./res/ys_zt.ttf", 25), *title_font = TTF_OpenFont("./res/ys_zt.ttf", 35);
    SDL_Rect rect = {200, 200 + y, 300, 450};
    for (i = 0; i < player->sum_deck_size; i++) {
        print_card(renderer, player->sum_deck[i], rect, 0, 0, font,
                   title_font);
        rect.x += rect.w * 1.5;
        if ((i + 1) % 4 == 0) {
            rect.x = 200;
            rect.y += rect.h * 1.5;
        }
    }
}

Buff free_buff = {0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0}};
//Buff free_buff = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

void init_buff(Buff *buff) {
    *buff = free_buff;
}

void buff_decrease(Buff *buff) {
    if (buff->fragile > 0) {
        buff->fragile--;
    }
    if (buff->block_reduction > 0) {
        buff->block_reduction--;
    }
    if (buff->resistance > 0) {
        buff->resistance--;
    }
    if (buff->block_increase > 0) {
        buff->block_increase--;
    }
    if (buff->weak > 0) {
        buff->weak--;
    }
    if (buff->strength > 0) {
        buff->strength--;
    }
    if (buff->dizziness > 0) {
        buff->dizziness--;
    }
    if (buff->poisoning > 0) {
        buff->poisoning--;
    }
    if (buff->withering > 0) {
        buff->withering--;
    }
    if (buff->flame > 0) {
        buff->flame--;
    }
    if (buff->freezing > 0) {
        buff->freezing--;
    }
    if (buff->lightning > 0) {
        buff->lightning--;
    }
    if (buff->undead > 0) {
        buff->undead--;
    }
}

/*
Card *create_card(char *name, int cost, int type, int career, void (*effect)(struct Player *, struct Enemy *)) {
    Card *new_card = (Card *) malloc(sizeof(Card));
    new_card->name = strdup(name);
    new_card->cost = cost;
    new_card->effect = effect;
    new_card->type = type;
    new_card->career = career;
    return new_card;
}*/

Player *init_player(int hp, int career) {
    Player *player = (Player *) malloc(sizeof(Player));
    player->player_career = career + 1;
    player->hp = hp;
    player->maxhp = hp;
    player->block = 0;
    player->energy = 3;
    player->coin = 99;
    player->hand = NULL;
    player->hand_size = 0;
    player->deck = NULL;
    player->deck_size = 0;
    player->discard_pile = NULL;
    player->discard_pile_size = 0;
    player->sum_deck = NULL;
    player->sum_deck_size = 0;
    player->buff = free_buff;
    player->times = 0;
    return player;
}

void add_card_to_bag(Player *player, Card *card) {
    player->sum_deck_size++;
    player->sum_deck = (Card **) realloc(player->sum_deck, player->sum_deck_size * sizeof(Card *));
    player->sum_deck[player->sum_deck_size - 1] = card;
}

void add_card_to_deck(Player *player, Card *card) {
    player->deck_size++;
    player->deck = (Card **) realloc(player->deck, player->deck_size * sizeof(Card *));
    player->deck[player->deck_size - 1] = card;
}

void Enemy_be_attack(Enemy *enemy, int damage) {
    if (damage > enemy->block) {
        damage -= enemy->block;
        enemy->block = 0;
    } else {
        enemy->block -= damage;
    }
    if (damage == 0) {
        return;
    }
    damage = damage * (double) (1.0 + (enemy->buff.fragile <= 0 ? 0.0 : 1.0) * 0.25 +
                                (enemy->buff.resistance <= 0 ? 0.0 : 1.0) * (-0.25));

    enemy->hp -= damage;
    if (enemy->hp <= 0) {
        enemy->hp = 0;
    }
    if (enemy->buff.undead > 0 && enemy->hp == 0) {
        enemy->hp = 1;
    }
}

void Player_attack_enemy(Player *player, Enemy *enemy, int damage) {
    damage = damage * (double) (1.0 + (player->buff.strength <= 0 ? 0.0 : 1.0) * 0.25 +
                                (player->buff.weak <= 0 ? 0.0 : 1.0) * (-0.25));
    Enemy_be_attack(enemy, damage);
}

void attack(Player *player, Enemy *enemy) {
    Player_attack_enemy(player, enemy, 6);
}

void critical_hit(Player *player, Enemy *enemy) {
    Player_attack_enemy(player, enemy, 30);
}

void sweep(Player *player, Enemy *enemy) {
    for (int i = 0; i < main_Enemynum; i++) {
        Player_attack_enemy(player, &main_enemy[i], 5);
    }
}

void Player_get_block(Player *player, int block) {
    block = block * (double) (1.0 + (player->buff.block_reduction <= 0 ? 0.0 : -0.5) +
                              (player->buff.block_increase <= 0 ? 0.0 : 0.5));
    player->block += block;
}

void defense(Player *player, Enemy *enemy) {
    Player_get_block(player, 6);
}

void get_buff(int *buff, int size) {
    *buff += size;
}

void painful_blow(Player *player, Enemy *enemy) {
    get_buff(&enemy->buff.fragile, 2);
    Player_attack_enemy(player, enemy, 8);
}

void ambush(Player *player, Enemy *enemy) {
    Player_attack_enemy(player, enemy, 5);
    get_buff(&enemy->buff.weak, 3);
}

void counterattack(Player *player, Enemy *enemy) {
    Player_attack_enemy(player, enemy, player->block);
}

void powerful_strike(Player *player, Enemy *enemy) {
    int cnt = 0;
    for (int i = 0; i < player->hand_size; i++) {
        cnt += player->hand[i]->type == 1;
    }
    Player_attack_enemy(player, enemy, 10 + 3 * cnt);
}

void armorer(Player *player, Enemy *enemy) {
    get_buff(&player->buff.armor, 99999);
}

int deadly_tempotimes;

void deadly_tempo(Player *player, Enemy *enemy) {
    Player_attack_enemy(player, enemy, 7 + 1 * deadly_tempotimes);
    deadly_tempotimes++;
}

void ACE(Player *player, Enemy *enemy) {
    for (int i = 0; i < 5; i++) {
        draw_card(player);
    }
}

void struggle_desperately(Player *player, Enemy *enemy) {
    get_buff(&player->buff.undead, 3);
    get_buff(&player->buff.extra_energy[1], 3);
}

void excited(Player *player, Enemy *enemy) {
    player->buff.weak = 0;
    player->buff.fragile = 0;
    player->buff.block_reduction = 0;
    player->buff.dizziness = 0;
    player->buff.poisoning = 0;
    player->buff.withering = 0;
    player->buff.flame = 0;
    player->buff.freezing = 0;
    player->buff.lightning = 0;
}

void heal(Player *player, Enemy *enemy) {
    player->hp += 10;
    if (player->hp > player->maxhp) {
        player->hp = player->maxhp;
    }
}

void init_card() {
    int i, j;
    main_cardnum[1] = 13;//1:攻击 2:防御 3:装备 4:技能
    main_card[1][0] = (Card) {"攻击", 1, false, 1, 1, true, attack, "造成6点伤害"};
    main_card[1][1] = (Card) {"防护", 1, false, 2, 1, false, defense, "获得6点格挡"};
    main_card[1][2] = (Card) {"痛击", 2, false, 2, 1, true, painful_blow, "造成8点伤害\n提供2点易伤"};
    main_card[1][3] = (Card) {"横扫", 1, false, 1, 1, false, sweep, "对所有单位造成5点伤害"};
    main_card[1][4] = (Card) {"奇袭", 0, true, 4, 1, true, ambush, "造成5点伤害和3点虚弱"};
    main_card[1][5] = (Card) {"反击", 1, false, 4, 1, true, counterattack, "根据格挡值造成伤害"};
    main_card[1][6] = (Card) {"强力击", 2, false, 1, 1, true, powerful_strike,
                              "造成10点伤害\n手中每有一张攻击牌\n使伤害增加3"};
    main_card[1][7] = (Card) {"装甲", 2, true, 3, 1, false, armorer, "使我方该场战斗中格挡值\n不再在回合结束时消失"};
    main_card[1][8] = (Card) {"致命节奏", 1, false, 1, 1, true, deadly_tempo, "造成7点伤害\n每使用一次该牌，伤害+1"};
    main_card[1][9] = (Card) {"底牌", 0, true, 4, 1, false, ACE, "抽5张牌"};
    main_card[1][10] = (Card) {"搏命挣扎", 0, true, 4, 1, false, struggle_desperately,
                               "接下来的3回合内不死\n且额外获得2能量\n但3回合结束后直接死亡"};
    main_card[1][11] = (Card) {"兴奋", 1, true, 4, 1, false, excited, "清除所有的负面效果"};
    main_card[1][12] = (Card) {"治疗", 1, true, 4, 1, false, heal, "回复10生命值"};
    main_card[1][13] = (Card) {"致命一击", 3, false, 1, 1, true, critical_hit, "造成30点伤害"};
}

void play_be_attacked(Player *player, Enemy *enemy, int damage) {
    if (damage > player->block) {
        damage -= player->block;
        player->block = 0;
    } else {
        player->block -= damage;
    }
    if (damage == 0) {
        return;
    }
    damage = damage * (double) (1.0 + (player->buff.fragile <= 0 ? 0.0 : 1.0) * 0.25 +
                                (player->buff.resistance <= 0 ? 0.0 : 1.0) * (-0.25));
    player->hp -= damage;
    if (player->hp <= 0) {
        player->hp = 0;
    }
    if (player->buff.undead > 0 && player->hp == 0) {
        player->hp = 1;
    }

}

void enemy_attack_player(Player *player, Enemy *enemy, int damage) {
    damage = damage * (double) (1.0 + (enemy->buff.strength <= 0 ? 0.0 : 1.0) * 0.25 +
                                (enemy->buff.weak <= 0 ? 0.0 : 1.0) * (-0.25));
    play_be_attacked(player, enemy, damage);
}

void ragpicker_attack(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 3);
    enemy_attack_player(player, enemy, 3);
}

void ragpicker_Strengthen(Player *player, Enemy *enemy) {
    get_buff(&enemy->buff.strength, 3);
}

void ragpicker_Weaken(Player *player, Enemy *enemy) {
    get_buff(&player->buff.fragile, 1);
    enemy_attack_player(player, enemy, 5);
}

extern int Enemy_num_in_map[7][2];
extern Enemy Enemy_in_map[7][2][10];

void init_enemy(SDL_Renderer *renderer) {
    Enemy_in_map[1][0][0] = (Enemy) {"拾荒者", IMG_LoadTexture(renderer, "./img/ragpicker.png"), 45, 0, 3};
    Enemy_in_map[1][0][0].skill[0] = (Enemy_skill) {1, "2*3", ragpicker_attack};
    Enemy_in_map[1][0][0].skill[1] = (Enemy_skill) {4, "", ragpicker_Strengthen};
    Enemy_in_map[1][0][0].skill[2] = (Enemy_skill) {3, "5", ragpicker_Weaken};
}

void draw_card(Player *player) {
    if (player->deck_size == 0) {
        // 如果牌库为空，将弃牌堆洗牌后放入牌库
        shuffle_discard_pile_to_deck(player);
    }
    if (player->deck_size > 0) {
        // 从牌库顶部抽取一张牌到手牌
        player->hand_size++;
        player->hand = (Card **) realloc(player->hand, player->hand_size * sizeof(Card *));
        player->hand[player->hand_size - 1] = player->deck[player->deck_size - 1];
        player->deck_size--;
        player->deck = (Card **) realloc(player->deck, player->deck_size * sizeof(Card *));
    }
}

void use_card(Player *player, int *card_index, Enemy *enemy) {
    if (*card_index < 0 || *card_index >= player->hand_size) {
        printf("Invalid card index!\n");
        return;
    }
    Card *card = player->hand[*card_index];
    if (card->cost > player->energy) {
        printf("Not enough energy to use the card!\n");
        return;
    }
    player->energy -= card->cost;
    card->effect(player, enemy); // 调用卡牌的效果函数
    // 将使用过的卡牌放入弃牌堆
    discard_card(player, *card_index);
    *card_index = -1;
}

void discard_card(Player *player, int card_index) {
    if (card_index < 0 || card_index >= player->hand_size) {
        printf("Invalid card index!\n");
        return;
    }
    Card *card = player->hand[card_index];
    if (!card->exhaust) {
        player->discard_pile_size++;
        player->discard_pile = (Card **) realloc(player->discard_pile, player->discard_pile_size * sizeof(Card *));
        player->discard_pile[player->discard_pile_size - 1] = card;
    }
    // 移除手牌中的该卡牌
    for (int i = card_index; i < player->hand_size - 1; i++) {
        player->hand[i] = player->hand[i + 1];
    }
    player->hand_size--;
    player->hand = (Card **) realloc(player->hand, player->hand_size * sizeof(Card *));
}

void shuffle_discard_pile_to_deck(Player *player) {
    if (player->discard_pile_size == 0) {
        return;
    }
    // 先将弃牌堆的牌添加到牌库
    player->deck_size += player->discard_pile_size;
    player->deck = (Card **) realloc(player->deck, player->deck_size * sizeof(Card *));
    for (int i = 0; i < player->discard_pile_size; i++) {
        player->deck[player->deck_size - 1 - i] = player->discard_pile[i];
    }
    player->discard_pile_size = 0;
    player->discard_pile = (Card **) realloc(player->discard_pile, 0);
    // 简单的洗牌算法，交换多次
    for (int i = 0; i < player->deck_size; i++) {
        int j = generate_random(0, player->deck_size - 1);
        Card *temp = player->deck[i];
        player->deck[i] = player->deck[j];
        player->deck[j] = temp;
    }
}