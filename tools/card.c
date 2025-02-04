//
// Created by 48811 on 25-1-14.
//

#include "card.h"
#include <string.h>
#include <stdlib.h>
#include "button.h"

extern int main_collection_num[7];
extern Collection main_collection[7][10];

bool rect_in_mouse(SDL_Rect rect, int mouse_x, int mouse_y) {
    if (mouse_x >= rect.x && mouse_x <= rect.x + rect.w &&
        mouse_y >= rect.y && mouse_y <= rect.y + rect.h) {
        return true;
    }
    return false;
}

void print_everycard(SDL_Renderer *renderer, Player *player, int y, int mouse_x, int mouse_y, int index) {
    int i;
    TTF_Font *font = TTF_OpenFont("./res/ys_zt.ttf", 25), *title_font = TTF_OpenFont("./res/ys_zt.ttf", 35);
    SDL_Rect rect = {200, 200 + y, 300, 450};
    for (i = 0; i < player->sum_deck_size; i++) {
        print_card(renderer, player->sum_deck[i], rect, rect_in_mouse(rect, mouse_x, mouse_y), index == i, font,
                   title_font);
        rect.x += rect.w * 1.5;
        if ((i + 1) % 4 == 0) {
            rect.x = 200;
            rect.y += rect.h * 1.5;
        }
    }
}

void print_everycollection(SDL_Renderer *renderer, Player *player, int y) {
    int i;
    TTF_Font *font = TTF_OpenFont("./res/ys_zt.ttf", 20), *title_font = TTF_OpenFont("./res/ys_zt.ttf", 35);
    SDL_Rect rect = {200, 200 + y, 200, 300};
    for (i = 0; i < player->sum_collection; i++) {
        print_collection(renderer, player->collections[i], rect, font,
                         title_font);
        rect.x += rect.w * 1.5;
        if ((i + 1) % 5 == 0) {
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
extern int main_potion_num;
extern Potion main_potion[20];

void p0(Player *player) {
    player_get_hp(player, 10);
}

void p1(Player *player) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            Enemy_be_attack(&main_enemy[i], 10);
        }
    }
}

void p2(Player *player) {
    Player_get_block(player, 30);
}

void p3(Player *player) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            main_enemy[i].buff.poisoning += 5;
        }
    }
}

void p4(Player *player) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            main_enemy[i].buff.withering += 5;
            enemy_withering(&main_enemy[i]);
        }
    }
}

void p5(Player *player) {
    player->energy += 3;
    for (int i = 0; i < 3; i++) {
        if (player->deck_size == 0 && player->discard_pile_size == 0) {
            break;
        }
        draw_card(player);
    }
}

void p6(Player *player) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            main_enemy[i].block = 0;
        }
    }
}

void p7(Player *player) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            main_enemy[i].buff.dizziness++;
        }
    }
}

void p8(Player *player) {
    player->buff.strength += 5;
}

void p9(Player *player) {
    player->buff.resistance += 5;
}

void nubo(Player *player) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            Enemy_be_attack(&main_enemy[i], 999);
        }
    }
    player_be_attacked(player, NULL, 999);
}

extern Potion Nuclear_Bomb;

void init_potion() {
    main_potion_num = 10;
    Nuclear_Bomb = (Potion) {"核弹", "对敌我双方造成999伤害", COLOR_BLACK, nubo};
    main_potion[0] = (Potion) {"回血药水", "回复10点生命值", COLOR_LIGHT_GREEN, p0};
    main_potion[1] = (Potion) {"攻击药水", "对所有敌人造成10点伤害", COLOR_RED, p1};
    main_potion[2] = (Potion) {"护盾药水", "获得30护盾", COLOR_GREY, p2};
    main_potion[3] = (Potion) {"中毒药水", "对所有敌人造成5点中毒", COLOR_GREYGREEN, p3};
    main_potion[4] = (Potion) {"凋零药水", "对所有敌人造成5点凋零\n引爆一次", COLOR_BLACK, p4};
    main_potion[5] = (Potion) {"能量药水", "获得三点能量，抽三张卡", COLOR_ORANGE, p5};
    main_potion[6] = (Potion) {"碎盾药水", "击碎所有敌人的护盾", COLOR_BLACK, p6};
    main_potion[7] = (Potion) {"眩晕药水", "使所有敌人眩晕1回合", COLOR_ORANGE, p7};
    main_potion[8] = (Potion) {"力量药水", "获得5点力量", COLOR_RED, p8};
    main_potion[9] = (Potion) {"抗性药水", "获得5点抗性", COLOR_BLACK, p9};
}

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
    player->sum_Potion = 0;
    player->potions = NULL;
    get_potion(player, &main_potion[generate_random(0, 9)]);
    get_potion(player, &main_potion[generate_random(0, 9)]);
    get_potion(player, &main_potion[generate_random(0, 9)]);
    player->sum_collection = 0;
    player->collections = NULL;
    player_get_collection(player, 0, 0);
    player->extra_damage = 0;
    player->enter_allowance = false;
    player->damage_increase = 0;
    return player;
}

void free_player(Player *player) {
    free(player->deck);
    free(player->hand);
    free(player->sum_deck);
    free(player->potions);
    free(player->discard_pile);
    free(player->collections);
    free(player);
}

void add_card_to_bag(Player *player, Card *card) {
    player->sum_deck_size++;
    player->sum_deck = (Card **) realloc(player->sum_deck, player->sum_deck_size * sizeof(Card *));
    player->sum_deck[player->sum_deck_size - 1] = card;
}

void delete_card_from_bag(Player *player, int index) {
    player->sum_deck[index] = player->sum_deck[player->sum_deck_size - 1];
    player->sum_deck_size--;
    player->sum_deck = (Card **) realloc(player->sum_deck, player->sum_deck_size * sizeof(Card *));
}

void add_card_to_deck(Player *player, Card *card) {
    player->deck_size++;
    player->deck = (Card **) realloc(player->deck, player->deck_size * sizeof(Card *));
    player->deck[player->deck_size - 1] = card;
}

void add_card_to_hand(Player *player, Card *card) {
    player->hand_size++;
    player->hand = (Card **) realloc(player->hand, player->hand_size * sizeof(Card *));
    player->hand[player->hand_size - 1] = card;
}

void Enemy_be_attack(Enemy *enemy, int damage) {
    if (damage > enemy->block) {
        damage -= enemy->block;
        enemy->block = 0;
    } else {
        enemy->block -= damage;
        damage = 0;
    }
    if (damage == 0) {
        return;
    }
    double enemy_hurt_increase = 1.0;
    if (enemy->buff.fragile > 0) {
        enemy_hurt_increase += 0.25;
    }
    if (enemy->buff.resistance > 0) {
        enemy_hurt_increase -= 0.25;
    }
    if (main_collection[0][6].get && generate_random(1, 3) == 2) {
        enemy_hurt_increase += 0.1;
    }
    if (main_collection[3][5].get) {
        enemy_hurt_increase += 0.4;
    }
    if (enemy_hurt_increase < 0) {
        return;
    }
    damage = (double) (damage) * enemy_hurt_increase;
    enemy->hp -= damage;
    if (enemy->hp <= 0) {
        enemy->hp = 0;
    }
    if (enemy->buff.undead > 0 && enemy->hp == 0) {
        enemy->hp = 1;
    }
}

void Player_attack_enemy(Player *player, Enemy *enemy, int damage) {
    double damage_increase = 1.0;
    if (player->buff.strength > 0) {
        damage_increase += 0.25;
    }
    if (player->buff.weak > 0) {
        damage_increase -= 0.25;
    }
    if (main_collection[3][0].get && player->hp <= player->maxhp / 10) {
        damage_increase += 0.5;
    }
    if (main_collection[4][0].get) {
        damage_increase += (0.08) * (player->coin / 10);
    }
    if (main_collection[4][1].get) {
        damage_increase += (0.01) * player->sum_deck_size;
    }
    if (main_collection[2][2].get) {
        damage_increase += (0.03) * (player->coin / 10);
    }
    if (main_collection[5][3].get && generate_random(1, 3) == 2) {
        damage_increase += 0.3;
    }
    if (main_collection[4][2].get) {
        damage_increase += 0.3;
    }
    if (main_collection[3][3].get) {
        if (player->buff.fragile > 0) {
            damage_increase += 0.2;
        }
        if (player->buff.block_reduction > 0) {
            damage_increase += 0.2;
        }
        if (player->buff.weak > 0) {
            damage_increase += 0.2;
        }
        if (player->buff.poisoning > 0) {
            damage_increase += 0.2;
        }
        if (player->buff.dizziness > 0) {
            damage_increase += 0.2;
        }
        if (player->buff.withering > 0) {
            damage_increase += 0.2;
        }
    }
    if (main_collection[0][5].get) {
        damage_increase += 0.05;
    }
    if (main_collection[2][5].get) {
        damage_increase += 0.25;
    }
    if (main_collection[1][6].get && generate_random(1, 10) == 7) {
        damage_increase += 0.8;
    }
    damage_increase += player->damage_increase;
    if (damage_increase < 0) {
        return;
    }
    damage = (double) (damage) * damage_increase;
    damage += player->extra_damage;
    if (damage > 0) {
        Enemy_be_attack(enemy, damage);
    }
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
    double block_increase = 1.0;
    if (player->buff.block_reduction > 0) {
        block_increase -= 0.5;
    }
    if (player->buff.block_increase > 0) {
        block_increase += 0.5;
    }
    if (main_collection[3][1].get && player->maxhp / 10 >= player->hp) {
        block_increase += 0.5;
    }
    if (block_increase < 0) {
        return;
    }
    block = (double) (block) * block_increase;
    player->block += block;
}

void defense(Player *player, Enemy *enemy) {
    Player_get_block(player, 6);
}

void get_buff(int *buff, int size) {
    *buff += size;
    if (*buff > 999) {
        *buff = 999;
    }
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

void player_get_hp(Player *player, int num) {
    double hp_increase = 1.0;
    if (main_collection[4][2].get) {
        hp_increase += 0.35;
    }
    if (main_collection[2][3].get) {
        hp_increase += 0.2;
    }
    player->hp += num * hp_increase;
    if (player->hp > player->maxhp) {
        player->hp = player->maxhp;
    }
}

void enemy_withering(Enemy *enemy) {
    if (enemy->buff.withering <= 0) {
        return;
    }
    enemy->buff.withering_times++;
    double damage_increase = 1.0;
    if (main_collection[4][4].get) {
        damage_increase += 0.5;
    }
    if (main_collection[2][4].get) {
        damage_increase += 0.1;
    }
    Enemy_be_attack(enemy, enemy->buff.withering_times * damage_increase);
}

void heal(Player *player, Enemy *enemy) {
    player_get_hp(player, 10);
}

void boiling_blood(Player *player, Enemy *enemy) {
    get_buff(&player->buff.strength, 2);
    add_card_to_deck(player,
                     &main_card[player->player_career][generate_random(2, main_cardnum[player->player_career])]);
}

void elbowing(Player *player, Enemy *enemy) {
    Player_attack_enemy(player, enemy, 6);
    if (generate_random(1, 4) == 2) {
        get_buff(&enemy->buff.dizziness, 1);
    }
}

void Bladestorm(Player *player, Enemy *enemy) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < main_Enemynum; j++) {
            if (main_enemy[j].hp > 0) {
                Player_attack_enemy(player, &main_enemy[j], 3);
            }
        }
    }
}

void hasaki(Player *player, Enemy *enemy) {
    get_buff(&enemy->buff.fragile, 3);
    Player_attack_enemy(player, enemy, 6);
}

void Dragon_Fang(Player *player, Enemy *enemy) {
    if (enemy->hp < 30) {
        Player_attack_enemy(player, enemy, 14);
    } else {
        Player_attack_enemy(player, enemy, 9);
    }
}

void hero_entrance(Player *player, Enemy *enemy) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            get_buff(&main_enemy[i].buff.fragile, 2);
            get_buff(&main_enemy[i].buff.block_reduction, 2);
            Player_attack_enemy(player, &main_enemy[i], 12);
        }
    }
    player->energy += 3;
}

void Fate_Sealed(Player *player, Enemy *enemy) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            Player_attack_enemy(player, &main_enemy[i], 16);
        }
    }
}

void Corrupt(Player *player, Enemy *enemy) {
    get_buff(&enemy->buff.withering, 4);
    enemy_withering(enemy);
}

void plague(Player *player, Enemy *enemy) {
    for (int i = 0; i < main_Enemynum; i++) {
        get_buff(&main_enemy[i].buff.poisoning, 6);
        get_buff(&main_enemy[i].buff.poisoning, main_enemy[i].buff.poisoning);
    }
}

void Poisoned(Player *player, Enemy *enemy) {
    for (int i = 0; i < 5; i++) {
        Player_attack_enemy(player, enemy, 2);
        if (rand() % 2 == 1) {
            get_buff(&player->buff.poisoning, 1);
        }
    }
}

void weakness(Player *player, Enemy *enemy) {
    get_buff(&enemy->buff.fragile, 1);
    get_buff(&enemy->buff.block_reduction, 1);
}

void Cheat(Player *player, Enemy *enemy) {
    Player_get_block(player, 30);
}

void Blast_Dawn(Player *player, Enemy *enemy) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < main_Enemynum; j++) {
            if (main_enemy[j].hp > 0) {
                Player_attack_enemy(player, &main_enemy[j], 10);
            }
        }
    }
}

void Reckoning(Player *player, Enemy *enemy) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            Player_attack_enemy(player, &main_enemy[i], 3);
            Player_get_block(player, 5);
        }
    }
}

void Sever_Bones(Player *player, Enemy *enemy) {
    int tmp = (player->maxhp - player->hp) / 10;
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            Player_attack_enemy(player, &main_enemy[i], 5 + 3 * tmp);
        }
    }
}

void Unyielding(Player *player, Enemy *enemy) {
    get_buff(&player->buff.block_increase, 3);
    Player_get_block(player, 10);
}

void init_card() {
    int i, j;
    main_cardnum[1] = 30;//1:攻击 2:防御 3:装备 4:技能
    main_card[1][0] = (Card) {"攻击", 1, false, 1, 1, true, attack, "造成6点伤害", 0};
    main_card[1][1] = (Card) {"防护", 1, false, 2, 1, false, defense, "获得6点格挡", 0};
    main_card[1][2] = (Card) {"痛击", 2, false, 1, 1, true, painful_blow, "造成8点伤害\n提供2点易伤", 1};
    main_card[1][3] = (Card) {"横扫", 1, false, 1, 1, false, sweep, "对所有单位造成5点伤害", 1};
    main_card[1][4] = (Card) {"奇袭", 0, true, 4, 1, true, ambush, "造成5点伤害\n和3点虚弱", 1};
    main_card[1][5] = (Card) {"反击", 1, false, 4, 1, true, counterattack, "根据格挡值造成伤害", 1};
    main_card[1][6] = (Card) {"强力击", 2, false, 1, 1, true, powerful_strike,
                              "造成10点伤害\n手中每有一张攻击牌\n使伤害增加3", 1};
    main_card[1][7] = (Card) {"装甲", 2, true, 3, 1, false, armorer, "使我方该场战斗中格挡值\n不再在回合结束时消失", 2};
    main_card[1][8] = (Card) {"致命节奏", 1, false, 1, 1, true, deadly_tempo, "造成7点伤害\n每使用一次该牌\n伤害+1", 1};
    main_card[1][9] = (Card) {"底牌", 0, true, 4, 1, false, ACE, "抽5张牌", 2};
    main_card[1][10] = (Card) {"搏命挣扎", 0, true, 4, 1, false, struggle_desperately,
                               "接下来的3回合内不死\n且额外获得2能量\n但3回合结束后直接死亡", 2};
    main_card[1][11] = (Card) {"兴奋", 1, true, 4, 1, false, excited, "清除所有的负面效果", 2};
    main_card[1][12] = (Card) {"治疗", 1, true, 4, 1, false, heal, "回复10生命值", 1};
    main_card[1][13] = (Card) {"致命一击", 3, false, 1, 1, true, critical_hit, "造成30点伤害", 2};
    main_card[1][14] = (Card) {"沸血", 0, false, 4, 1, false, boiling_blood, "获得2回合力量\n随机一张牌", 1};
    main_card[1][15] = (Card) {"肘击", 1, false, 1, 1, true, elbowing, "造成6点伤害\n25%造成1回合眩晕", 1};
    main_card[1][16] = (Card) {"剑刃风暴", 2, false, 1, 1, false, Bladestorm, "对所有敌人造成3*3点伤害", 2};
    main_card[1][17] = (Card) {"哈撒给", 0, false, 1, 1, true, hasaki, "造成4点伤害\n3回合易碎", 2};
    main_card[1][18] = (Card) {"龙牙", 1, false, 1, 1, true, Dragon_Fang, "造成9点伤害\n若敌方生命值小于30\n伤害+5", 1};
    main_card[1][19] = (Card) {"英雄登场", 0, true, 4, 1, false, hero_entrance,
                               "对所有敌人造成12点伤害\n2回合脆弱和易碎\n获得3点能量",
                               2};
    main_card[1][20] = (Card) {"双剑划斩", 2, false, 1, 1, false, Fate_Sealed,
                               "对所有敌人造成16点伤害",
                               2};
    main_card[1][21] = (Card) {"腐化", 1, false, 1, 1, true, Corrupt,
                               "造成4点凋零\n引爆1次凋零",
                               1};
    main_card[1][22] = (Card) {"瘟疫", 2, true, 4, 1, false, plague,
                               "所有敌人受到6点中毒\n使所有敌人中毒翻倍",
                               2};
    main_card[1][23] = (Card) {"淬毒", 1, false, 1, 1, true, Poisoned,
                               "对敌人造成5*2点伤害\n每次攻击50%中毒",
                               2};
    main_card[1][24] = (Card) {"弱点", 0, false, 4, 1, true, weakness,
                               "造成1回合\n脆弱和易碎",
                               2};
    main_card[1][25] = (Card) {"歪瓜", 0, true, 2, 1, false, Cheat,
                               "获得30点格挡",
                               2};
    main_card[1][26] = (Card) {"爆裂黎明", 5, true, 4, 1, false, Blast_Dawn,
                               "大彻大悟\n对所有敌人\n造成6*10点伤害",
                               3};
    main_card[1][27] = (Card) {"凛神斩", 1, false, 1, 1, false, Reckoning,
                               "对所有敌人造成3点伤害\n命中每个敌人提供5格挡",
                               2};
    main_card[1][28] = (Card) {"肉斩骨断", 1, false, 1, 1, false, Sever_Bones,
                               "对敌人造成5点伤害\n每损失10生命值\n伤害+3 ",
                               2};
    main_card[1][29] = (Card) {"不屈", 2, false, 2, 1, false, Unyielding,
                               "获得3点坚强\n10点格挡",
                               1};

}

void player_be_attacked(Player *player, Enemy *enemy, int damage) {
    if (damage > player->block) {
        damage -= player->block;
        player->block = 0;
    } else {
        player->block -= damage;
        damage = 0;
    }
    if (damage <= 0) {
        return;
    }
    double damage_increase = 1.0;
    if (player->buff.fragile > 0) {
        damage_increase += 0.25;
    }
    if (player->buff.resistance > 0) {
        damage_increase -= 0.25;
    }
    if (main_collection[3][7].get) {
        for (int i = 0; i < main_collection_num[6]; i++) {
            if (main_collection[6][i].get) {
                damage_increase -= 0.1;
            }
        }
    }
    if (damage_increase < 0) {
        return;
    }
    if (main_collection[4][5].get) {
        damage_increase *= 0.7;
    }
    damage = (double) (damage) * damage_increase;
    player->hp -= damage;
    if (player->hp <= 0) {
        player->hp = 0;
    }
    if (player->buff.undead > 0 && player->hp <= 0) {
        player->hp = 1;
    }

}

void enemy_attack_player(Player *player, Enemy *enemy, int damage) {
    double damage_increase = 1.0;
    if (enemy->buff.strength > 0) {
        damage_increase += 0.25;
    }
    if (enemy->buff.weak > 0) {
        damage_increase -= 0.25;
    }

    if (main_collection[6][1].get) {
        damage_increase += 0.2;
    }
    if (main_collection[4][2].get) {
        damage_increase -= 0.3;
    }
    if (damage_increase < 0) {
        return;
    }
    damage = (double) (damage) * damage_increase;
    player_be_attacked(player, enemy, damage);
}

void enemy_get_block(Enemy *enemy, int block) {
    double block_increase = 1.0;
    if (enemy->buff.block_increase > 0) {
        block_increase += 0.5;
    }
    if (enemy->buff.block_reduction > 0) {
        block_increase -= 0.5;
    }
    block = (double) (block) * block_increase;
    enemy->block += block;
}

void enemy_get_hp(Enemy *enemy, int num) {
    enemy->hp += num;
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

void vulture_block(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 3);
}

void vulture_attack(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 3);
}

void vulture_attack2(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 7);
}

void wandering_ghost_recover(Player *player, Enemy *enemy) {
    enemy_get_hp(enemy, 10);
    get_buff(&enemy->buff.resistance, 5);
    get_buff(&enemy->buff.strength, 5);
}

void wandering_ghost_attack(Player *player, Enemy *enemy) {
    for (int i = 0; i < 8; i++) {
        enemy_attack_player(player, enemy, 2);
        if (generate_random(1, 2) == 1) {
            get_buff(&player->buff.withering, 1);
        }
    }
}

void wandering_ghost_weaken(Player *player, Enemy *enemy) {
    get_buff(&player->buff.fragile, 5);
    get_buff(&player->buff.weak, 5);
}

void wandering_ghost_attack2(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 8);
    if (player->buff.withering > 0) {
        player_withering(player);
    }
}

void wandering_ghost_block(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 10);
}

void Thief_attack(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 2);
    get_buff(&player->buff.poisoning, 3);
}

void Thief_attack2(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 5);
    get_buff(&player->buff.fragile, 2);
}

void Thief_block(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 5);
}

void hunter_strengthen(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 10);
    get_buff(&enemy->buff.strength, 3);
}

void hunter_attack1(Player *player, Enemy *enemy) {
    for (int i = 0; i < 2; i++) {
        enemy_attack_player(player, enemy, 5);
        if (generate_random(1, 4) == 2) {
            get_buff(&player->buff.weak, 1);
        }
    }
}

void hunter_attack2(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 9);
    get_buff(&enemy->buff.block_increase, 3);
}

void hunter_attack3(Player *player, Enemy *enemy) {
    if (player->block > 0) {
        enemy_attack_player(player, enemy, 5);
    }
    enemy_attack_player(player, enemy, 10);
}

void treeman_attack1(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 3);
    enemy_attack_player(player, enemy, 8);
    if (generate_random(1, 4) == 3) {
        get_buff(&player->buff.poisoning, 1);
    }
}

void treeman_attack2(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 3);
    for (int i = 0; i < 4; i++) {
        enemy_attack_player(player, enemy, 4);
        if (generate_random(1, 2) == 2) {
            get_buff(&player->buff.fragile, 1);
        }
    }
}

void treeman_defense(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 3);
    enemy_get_block(enemy, 10);
    if (enemy->hp < 30) {
        get_buff(&enemy->buff.armor, 999);
    }
}

void oldhunter_attack1(Player *player, Enemy *enemy) {
    get_buff(&player->buff.fragile, 3);
    get_buff(&player->buff.block_reduction, 3);
    for (int i = 0; i < 3; i++) {
        enemy_attack_player(player, enemy, 5);
    }
}

void oldhunter_block(Player *player, Enemy *enemy) {
    get_buff(&enemy->buff.strength, 4);
    enemy_get_block(enemy, 20);
}

void oldhunter_attack2(Player *player, Enemy *enemy) {
    for (int i = 0; i < 2; i++) {
        enemy_attack_player(player, enemy, 7);
        if (generate_random(1, 2) == 1) {
            get_buff(&player->buff.weak, 1);
        }
    }
}

void oldhunter_attack3(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 12);
    get_buff(&enemy->buff.block_increase, 2);
}

extern int round_times;

void goblin_ability(Enemy *enemy) {
    if (round_times <= 3) {
        enemy->buff.strength = 999;
    } else {
        enemy->buff.strength = 0;
        enemy->buff.weak = 999;
    }
}

void goblin_health(Player *player, Enemy *enemy) {
    goblin_ability(enemy);
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            enemy_get_hp(&main_enemy[i], 5);
        }
    }
}

void goblin_attack(Player *player, Enemy *enemy) {
    goblin_ability(enemy);
    enemy_attack_player(player, enemy, 6);
    get_buff(&player->buff.poisoning, 3);
}

void goblin_attack2(Player *player, Enemy *enemy) {
    goblin_ability(enemy);
    enemy_attack_player(player, enemy, 8);
    enemy_get_block(enemy, 4);
}

void slime_block(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 8);
}

void slime_block2(Player *player, Enemy *enemy) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            enemy_get_block(&main_enemy[i], 3);
        }
    }
}

void slime_attack(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 2 + (enemy->block / 2));
}

void slime_block_to_player(Player *player, Enemy *enemy) {
    Player_get_block(player, enemy->block);
}

void Goblin_Chief_ability(Enemy *enemy) {
    if (round_times <= 5) {
        enemy->buff.strength = 999;
    } else {
        enemy->buff.strength = 0;
        enemy->buff.weak = 999;
    }
}

void Goblin_Chief_attack(Player *player, Enemy *enemy) {
    Goblin_Chief_ability(enemy);
    enemy_attack_player(player, enemy, 9);
    get_buff(&player->buff.poisoning, 3);
}

void Goblin_Chief_attack2(Player *player, Enemy *enemy) {
    Goblin_Chief_ability(enemy);
    enemy_attack_player(player, enemy, 8);
    enemy_get_block(enemy, 10);
}

void Goblin_Chief_attack3(Player *player, Enemy *enemy) {
    Goblin_Chief_ability(enemy);
    for (int i = 0; i < 5; i++) {
        enemy_attack_player(player, enemy, 3);
    }
    get_buff(&player->buff.weak, 2);
}

void Goblin_Chief_health(Player *player, Enemy *enemy) {
    goblin_ability(enemy);
    enemy_get_block(enemy, 10);
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            enemy_get_hp(&main_enemy[i], 7);
        }
    }
}

void zombie_ability(Enemy *enemy) {
    enemy->hp += 5;
}

void zombie_attack(Player *player, Enemy *enemy) {
    zombie_ability(enemy);
    enemy_attack_player(player, enemy, 6);
    get_buff(&player->buff.poisoning, 2);
}

void zombie_attack2(Player *player, Enemy *enemy) {
    zombie_ability(enemy);
    enemy_attack_player(player, enemy, 7);
    enemy_attack_player(player, enemy, 7);
}

void zombie_fraglie(Player *player, Enemy *enemy) {
    zombie_ability(enemy);
    get_buff(&enemy->buff.fragile, 5);
}

void Corrupted_Forest_Ranger_attack(Player *player, Enemy *enemy) {
    get_buff(&enemy->buff.fragile, 999);
    enemy_attack_player(player, enemy, generate_random(12, 20));
}

void player_withering(Player *player) {
    if (player->buff.withering <= 0) {
        return;
    }
    player->buff.withering_times++;
    player_be_attacked(player, NULL, player->buff.withering_times);
}

void withering_tree_health(Player *player, Enemy *enemy) {
    enemy_get_hp(enemy, generate_random(10, 25));
}

void withering_tree_attack(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 15);
    if (generate_random(4, 1) == 2) {
        player_withering(player);
    }
    if (generate_random(4, 1) == 3) {
        get_buff(&player->buff.withering, 1);
    }
    get_buff(&player->buff.withering, 3);
}

void withering_tree_attack2(Player *player, Enemy *enemy) {
    for (int i = 0; i < 4; i++) {
        enemy_attack_player(player, enemy, 7);
        if (generate_random(4, 1) == 2) {
            player_withering(player);
        }
        if (generate_random(4, 1) == 3) {
            get_buff(&player->buff.withering, 1);
        }
    }
    enemy_get_block(enemy, 5);
}

void withering_tree_attack3(Player *player, Enemy *enemy) {
    player_withering(player);
    get_buff(&enemy->buff.resistance, 3);
}

void withering_tree_attack4(Player *player, Enemy *enemy) {
    player_withering(player);
    enemy_attack_player(player, enemy, 15);
    if (generate_random(4, 1) == 2) {
        player_withering(player);
    }
    if (generate_random(4, 1) == 3) {
        get_buff(&player->buff.withering, 1);
    }
}

void withering_tree_attack5(Player *player, Enemy *enemy) {
    int tmp = player->hp;
    player_withering(player);
    enemy_get_hp(enemy, tmp - player->hp);
}

void Human_Mushroom_ability(Player *player) {
    get_buff(&player->buff.poisoning, 1);
}

void Human_Mushroom_attack(Player *player, Enemy *enemy) {
    Human_Mushroom_ability(player);
    enemy_attack_player(player, enemy, 7);
    get_buff(&player->buff.poisoning, 2);
}

void Human_Mushroom_attack2(Player *player, Enemy *enemy) {
    Human_Mushroom_ability(player);
    for (int i = 0; i < 5; i++) {
        enemy_attack_player(player, enemy, 4);
        if (generate_random(1, 4) == 3) {
            get_buff(&player->buff.poisoning, 1);
        }
    }
}

void Human_Mushroom_attack3(Player *player, Enemy *enemy) {
    Human_Mushroom_ability(player);
    enemy_attack_player(player, enemy, 10);
    enemy_get_hp(enemy, player->buff.poisoning);
}

void Human_Mushroom_weaken(Player *player, Enemy *enemy) {
    Human_Mushroom_ability(player);
    get_buff(&player->buff.poisoning, 3);
    get_buff(&player->buff.fragile, 3);
}

void The_Lost_Forest_Warden_ability(Player *player, Enemy *enemy, int damage) {
    if (generate_random(1, 5) == 3) {
        damage += damage / 5;
    }
    enemy_attack_player(player, enemy, damage);
}

void The_Lost_Forest_Warden_attack(Player *player, Enemy *enemy) {
    The_Lost_Forest_Warden_ability(player, enemy, 18);
}

void The_Lost_Forest_Warden_attack2(Player *player, Enemy *enemy) {
    for (int i = 0; i < 6; i++) {
        The_Lost_Forest_Warden_ability(player, enemy, 3);
    }
}

void The_Lost_Forest_Warden_weaken(Player *player, Enemy *enemy) {
    get_buff(&player->buff.fragile, 3);
    get_buff(&enemy->buff.fragile, 3);
}

void The_Lost_Forest_Warden_defend(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 8);
}

void The_Lost_Forest_Warden_nothing(Player *player, Enemy *enemy) {
    return;
}

void Corrupted_Forest_Warden_attack(Player *player, Enemy *enemy) {
    get_buff(&player->buff.fragile, 999);
    enemy_attack_player(player, enemy, generate_random(13, 20));
}

void Corrupted_Forest_Warden_defend(Player *player, Enemy *enemy) {
    get_buff(&player->buff.fragile, 999);
    enemy_get_block(enemy, generate_random(8, 20));
}

void fog_ghost_increase(Player *player, Enemy *enemy) {
    get_buff(&enemy->buff.strength, 3);
}

void fog_ghost_attack(Player *player, Enemy *enemy) {
    for (int i = 0; i < 2; i++) {
        enemy_attack_player(player, enemy, 10);
        get_buff(&player->buff.poisoning, 1);
    }
}

void fog_ghost_attack2(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 12);
    get_buff(&player->buff.poisoning, 1);
    get_buff(&player->buff.fragile, 2);
}

void Phantom_ability(Enemy *enemy) {
    enemy->hp -= generate_random(20, 40);
    if (enemy->hp < 0) {
        enemy->hp = 0;
    }
}

void Phantom_ability2(Player *player, Enemy *enemy, int damage) {
    enemy_attack_player(player, enemy, damage);
    get_buff(&player->buff.withering, 1);
}

void Phantom_attack(Player *player, Enemy *enemy) {
    Phantom_ability(enemy);
    if (enemy->hp <= 0) {
        return;
    }
    for (int i = 0; i < 3; i++) {
        Phantom_ability2(player, enemy, 4);
    }
}

void Phantom_weaken(Player *player, Enemy *enemy) {
    get_buff(&player->buff.weak, 2);
}

void Phantom_attack2(Player *player, Enemy *enemy) {
    for (int i = 0; i < 5; i++) {
        Phantom_ability2(player, enemy, 2);
        if (generate_random(1, 5) == 3) {
            player_withering(player);
        }
    }
}

void Mountain_Zombie_ability(Enemy *enemy) {
    enemy_get_hp(enemy, 5);
}

void Mountain_Zombie_attack(Player *player, Enemy *enemy) {
    Mountain_Zombie_ability(enemy);
    enemy_attack_player(player, enemy, 8);
    enemy_get_hp(enemy, 3);
    enemy_get_block(enemy, 3);
}

void Mountain_Zombie_attack2(Player *player, Enemy *enemy) {
    Mountain_Zombie_ability(enemy);
    for (int i = 0; i < 2; i++) {
        enemy_attack_player(player, enemy, 9);
        enemy_get_hp(enemy, 3);
    }
}

void Mountain_Zombie_increase(Player *player, Enemy *enemy) {
    Mountain_Zombie_ability(enemy);
    get_buff(&enemy->buff.resistance, 3);
}

void Mountain_Zombie_defend(Player *player, Enemy *enemy) {
    Mountain_Zombie_ability(enemy);
    enemy_get_block(enemy, 10);
}

void Fog_walking_Bird_attack(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 12);
}

void Fog_walking_Bird_attack2(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 4);
    enemy_attack_player(player, enemy, 4);
}

void Fog_walking_Bird_defend(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 12);
    get_buff(&enemy->buff.strength, 2);
}

void Lost_Traveler_attack(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 8);
    enemy_attack_player(player, enemy, 8);
    enemy_attack_player(player, enemy, 8);
}

void Lost_Traveler_attack2(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 10);
    enemy_attack_player(player, enemy, 10);
}

void Lost_Traveler_defend(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 12);
}

void Lost_Traveler_increase(Player *player, Enemy *enemy) {
    get_buff(&enemy->buff.strength, 2);
    get_buff(&enemy->buff.resistance, 2);
}

void The_Last_Sentinel_ability(Enemy *enemy) {
    if (enemy->hp < 250) {
        for (int i = 0; i < main_Enemynum; i++) {
            if (main_enemy[i].hp > 0) {
                get_buff(&main_enemy[i].buff.strength, 99);
            }
        }
    }
}

void The_Last_Sentinel_attack(Player *player, Enemy *enemy) {
    The_Last_Sentinel_ability(enemy);
    enemy_attack_player(player, enemy, 18);
}

void The_Last_Sentinel_defend(Player *player, Enemy *enemy) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            enemy_get_block(&main_enemy[i], 10);
        }
    }
}

void The_Last_Sentinel_defend2(Player *player, Enemy *enemy) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            enemy_get_block(enemy, 15);
        }
    }
}

void The_Last_Sentinel_health(Player *player, Enemy *enemy) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            enemy_get_hp(&main_enemy[i], 7);
        }
    }
}

void The_Last_Sentinel_health2(Player *player, Enemy *enemy) {
    for (int i = 1; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            enemy_get_hp(&main_enemy[i], 20);
        }
    }
}

void turret_attack(Player *player, Enemy *enemy) {
    if (main_enemy[0].hp <= 0) {
        enemy->hp = 0;
        return;
    }
    enemy_attack_player(player, enemy, 8);
}

void turret_attack2(Player *player, Enemy *enemy) {
    if (main_enemy[0].hp <= 0) {
        enemy->hp = 0;
        return;
    }
    enemy_attack_player(player, enemy, 12);
    enemy->hp -= 5;
    if (enemy->hp < 0) {
        enemy->hp = 0;
    }
}

void train_ability(Player *player, Enemy *enemy) {
    get_buff(&enemy->buff.armor, 999);
    if (enemy->hp <= 0) {
        enemy->hp -= 30;
        if (enemy->hp <= 0) {
            enemy->hp = 0;
            return;
        }
    }
    int t = 30 - round_times;
    if (t >= 0) {
        sprintf(enemy->name, "历史的幻影\n%d回合后斩杀玩家", t);
    }
    if (t <= 0) {
        player->hp = 0;
    }

}

void train_defend(Player *player, Enemy *enemy) {
    train_ability(player, enemy);
    if (enemy->hp <= 0) {
        return;
    }
    enemy_get_block(enemy, 10);
}

void train_attack(Player *player, Enemy *enemy) {
    train_ability(player, enemy);
    if (enemy->hp <= 0) {
        return;
    }
    for (int i = 0; i < 7; i++) {
        enemy_attack_player(player, enemy, 3);
    }
    get_buff(&player->buff.weak, 2);
}

void train_increase(Player *player, Enemy *enemy) {
    train_ability(player, enemy);
    if (enemy->hp <= 0) {
        return;
    }
    get_buff(&enemy->buff.block_increase, 3);
}

void train_attack2(Player *player, Enemy *enemy) {
    train_ability(player, enemy);
    if (enemy->hp <= 0) {
        return;
    }
    int tmp = player->hp;
    for (int i = 0; i < 3; i++) {
        enemy_attack_player(player, enemy, 5);
    }
    enemy_get_block(enemy, tmp - player->hp);
}

void train_increase2(Player *player, Enemy *enemy) {
    get_buff(&enemy->buff.strength, 2);
    enemy_get_block(enemy, 3);
}

void Sword_Guardian_ability(Enemy *enemy) {
    if (round_times >= 5) {
        get_buff(&enemy->buff.strength, 999);
    }
}

void Sword_Guardian_attack(Player *player, Enemy *enemy) {
    Sword_Guardian_ability(enemy);
    enemy_attack_player(player, enemy, 16);
    enemy_attack_player(player, enemy, 16);
}

void Sword_Guardian_defend(Player *player, Enemy *enemy) {
    Sword_Guardian_ability(enemy);
    enemy_get_block(enemy, 12);
}

void Sword_Guardian_attack2(Player *player, Enemy *enemy) {
    Sword_Guardian_ability(enemy);
    enemy_attack_player(player, enemy, 28);
}

void Shield_Guard_defend(Player *player, Enemy *enemy) {
    get_buff(&enemy->buff.armor, 999);
    enemy_get_block(enemy, 30);
}

void Shield_Guard_attack(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, enemy->block / 2);
    if (generate_random(1, 2) == 1) {
        get_buff(&enemy->buff.dizziness, 1);
    }
}

void Shield_Guard_attack2(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, enemy->block / 10 + 10);
}

void Shield_Guard_increase(Player *player, Enemy *enemy) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            get_buff(&main_enemy[i].buff.resistance, 5);
        }
    }
}

void Gun_Guardian_ability(Player *player, Enemy *enemy, int damage) {
    enemy_attack_player(player, enemy, damage);
    if (generate_random(1, 4) == 3) {
        enemy_attack_player(player, enemy, 3);
    }
}

void Gun_Guardian_attack1(Player *player, Enemy *enemy) {
    for (int i = 0; i < 4; i++) {
        Gun_Guardian_ability(player, enemy, 5);
    }
    get_buff(&enemy->buff.dizziness, 1);
}

void Gun_Guardian_attack2(Player *player, Enemy *enemy) {
    for (int i = 0; i < 3; i++) {
        Gun_Guardian_ability(player, enemy, 7);
    }
    get_buff(&enemy->buff.dizziness, 1);
}

void mage_ability(Player *player, Enemy *enemy, int damage) {
    enemy_attack_player(player, enemy, damage);
    player_withering(player);
}

void mage_attack(Player *player, Enemy *enemy) {
    for (int i = 0; i < 2; i++) {
        mage_ability(player, enemy, 5);
    }
}

void mage_attack2(Player *player, Enemy *enemy) {
    for (int i = 0; i < 3; i++) {
        mage_ability(player, enemy, 8);
    }
}

void mage_defend(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 12);
    enemy_get_hp(enemy, 20);
}

void mage_wither(Player *player, Enemy *enemy) {
    get_buff(&player->buff.withering, 3);
}

void Gargoyle_defend(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 20);
}

void Gargoyle_attack(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 8);
    enemy_attack_player(player, enemy, 8);
    enemy_attack_player(player, enemy, 8);
    get_buff(&player->buff.block_reduction, 2);
}

void Gargoyle_attack2(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 28);
}

void Gargoyle_increase(Player *player, Enemy *enemy) {
    get_buff(&enemy->buff.strength, 2);
}

void Guardian_Commander_attack(Player *player, Enemy *enemy) {
    for (int i = 0; i < 5; i++) {
        enemy_attack_player(player, enemy, 3);
    }
}

void Guardian_Commander_defend(Player *player, Enemy *enemy) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            enemy_get_block(&main_enemy[i], 5);
        }
    }
}

void Guardian_Commander_defend2(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 15);
}

void Guardian_Commander_health(Player *player, Enemy *enemy) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp > 0) {
            enemy_get_hp(&main_enemy[i], 5);
        }
    }
}

void Guardian_Commander_unknow(Player *player, Enemy *enemy) {
    int index = generate_random(1, 2);
    if (main_enemy[index].hp > 0) {
        get_buff(&main_enemy[index].buff.dizziness, 1);
        enemy_get_hp(&main_enemy[index], 20);
    }
}

void shadow_guard_attack(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 20);
    get_buff(&enemy->buff.fragile, 5);
}

void shadow_guard_attack2(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 36);
}

void shadow_guard_weaken(Player *player, Enemy *enemy) {
    get_buff(&player->buff.fragile, 4);
    get_buff(&player->buff.block_reduction, 4);
}

void shadow_guard_attack3(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 16);
    enemy_attack_player(player, enemy, 16);
}

extern int Enemy_num_in_map[7][2];
extern Enemy Enemy_in_map[7][2][10];

void King_ability(Player *player, Enemy *enemy) {
    player_withering(player);
    get_buff(&player->buff.poisoning, 2);
}

void King_attack(Player *player, Enemy *enemy) {
    for (int i = 0; i < 3; i++) {
        enemy_attack_player(player, enemy, 9);
        King_ability(player, enemy);
    }
    enemy_get_block(enemy, 20);
}

void King_increase(Player *player, Enemy *enemy) {
    enemy->buff.fragile = 0;
    enemy->buff.block_reduction = 0;
    enemy->buff.weak = 0;
    enemy->buff.dizziness = 0;
    enemy->buff.poisoning = 0;
    enemy->buff.withering = 0;
    enemy_get_block(enemy, 40);
}

void King_attack2(Player *player, Enemy *enemy) {
    if (enemy->buff.strength <= 0) {
        get_buff(&enemy->buff.dizziness, 2);
        get_buff(&enemy->buff.strength, 5);
    } else {
        enemy_attack_player(player, enemy, 30);
        get_buff(&player->buff.withering, 2);
        King_ability(player, enemy);
    }
}

void King_attack3(Player *player, Enemy *enemy) {
    for (int i = 0; i < 8; i++) {
        if (generate_random(1, 5) != 3) {
            enemy_attack_player(player, enemy, 4);
            get_buff(&player->buff.withering, 2);
            King_ability(player, enemy);
        }
    }
}

void King_weaken(Player *player, Enemy *enemy) {
    get_buff(&enemy->buff.block_increase, 5);
    get_buff(&player->buff.block_reduction, 5);
}

void Puppetmaster_health(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, 20);
    if (main_enemy[1].hp > 0) {
        main_enemy[1].hp = 150;
    }
}

void Puppetmaster_attack(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 14);
    enemy_attack_player(player, enemy, 14);
    enemy_attack_player(player, enemy, 14);
}

void Puppetmaster_steal(Player *player, Enemy *enemy) {
    enemy_get_block(enemy, player->block);
    get_buff(&enemy->buff.armor, 3);
    if (main_enemy[1].hp > 0) {
        enemy_get_block(&main_enemy[1], player->block);
        get_buff(&main_enemy[1].buff.armor, 3);
    }
    player->block = 0;
}

void Puppetmaster_wither(Player *player, Enemy *enemy) {
    get_buff(&player->buff.withering, 5);
    int tmp = player->hp;
    player_withering(player);
    enemy_get_hp(enemy, tmp - player->hp);
}

void Puppetmaster_increase(Player *player, Enemy *enemy) {
    if (main_enemy[1].hp > 0) {
        get_buff(&main_enemy[1].buff.fragile, enemy->buff.fragile);
        enemy->buff.fragile = 0;
        get_buff(&main_enemy[1].buff.block_reduction, enemy->buff.block_reduction);
        enemy->buff.block_reduction = 0;
        get_buff(&main_enemy[1].buff.weak, enemy->buff.weak);
        enemy->buff.weak = 0;
        get_buff(&main_enemy[1].buff.poisoning, enemy->buff.poisoning);
        enemy->buff.poisoning = 0;
        get_buff(&main_enemy[1].buff.withering, enemy->buff.withering);
        enemy->buff.withering = 0;
    }
    enemy_attack_player(player, enemy, 20);
}

void Puppetmaster_weaken(Player *player, Enemy *enemy) {
    get_buff(&player->buff.fragile, 3);
    get_buff(&player->buff.withering, 3);
    get_buff(&player->buff.weak, 3);
    enemy_get_block(enemy, 10);
}

void Puppetmaster_attack2(Player *player, Enemy *enemy) {
    enemy_attack_player(player, enemy, 5);
    if (generate_random(1, 2) == 2) {
        get_buff(&player->buff.dizziness, 1);
    }
}

void puppet_ability(Player *player, Enemy *enemy) {
    if (main_enemy[0].hp <= 0) {
        enemy->hp = 0;
        return;
    }
    int tmp = generate_random(1, 3);
    if (tmp == 1) {
        get_buff(&main_enemy[0].buff.resistance, 3);
    } else if (tmp == 2) {
        get_buff(&main_enemy[0].buff.strength, 3);
    } else {
        get_buff(&main_enemy[0].buff.block_increase, 3);
    }
}

void puppet_health(Player *player, Enemy *enemy) {
    puppet_ability(player, enemy);
    if (enemy->hp <= 0) {
        return;
    }
    Enemy_be_attack(enemy, 10);
    enemy_get_hp(enemy, 10);
}

void puppet_wither(Player *player, Enemy *enemy) {
    puppet_ability(player, enemy);
    if (enemy->hp <= 0) {
        return;
    }
    player_withering(player);
}

void puppet_defend(Player *player, Enemy *enemy) {
    puppet_ability(player, enemy);
    if (enemy->hp <= 0) {
        return;
    }
    enemy_get_block(&main_enemy[0], 10);
}

void init_enemy(SDL_Renderer *renderer) {//1攻击atk 2防御def 3削弱wek 4增益inc 5未知ukn
    Enemy_num_in_map[1][0] = 3;
    Enemy_in_map[5][1][5] = (Enemy) {"傀儡", IMG_LoadTexture(renderer, "./img/puppet.png"), 150,
                                     0, 3};
    Enemy_in_map[5][1][5].skill[0] = (Enemy_skill) {5, "???", puppet_health};
    Enemy_in_map[5][1][5].skill[1] = (Enemy_skill) {1, "凋零", puppet_wither};
    Enemy_in_map[5][1][5].skill[2] = (Enemy_skill) {2, "10", puppet_defend};
    Enemy_in_map[5][1][4] = (Enemy) {"幕后黑手", IMG_LoadTexture(renderer, "./img/Puppetmaster.png"), 1000,
                                     0, 7};
    Enemy_in_map[5][1][4].skill[0] = (Enemy_skill) {2, "???", Puppetmaster_health};
    Enemy_in_map[5][1][4].skill[1] = (Enemy_skill) {5, "3*14", Puppetmaster_attack};
    Enemy_in_map[5][1][4].skill[2] = (Enemy_skill) {5, "3*14", Puppetmaster_steal};
    Enemy_in_map[5][1][4].skill[3] = (Enemy_skill) {1, "凋零", Puppetmaster_wither};
    Enemy_in_map[5][1][4].skill[4] = (Enemy_skill) {5, "20", Puppetmaster_increase};
    Enemy_in_map[5][1][4].skill[5] = (Enemy_skill) {3, "", Puppetmaster_weaken};
    Enemy_in_map[5][1][4].skill[6] = (Enemy_skill) {1, "5", Puppetmaster_attack2};
    Enemy_in_map[5][1][3] = (Enemy) {"魔王", IMG_LoadTexture(renderer, "./img/King.png"), 700,
                                     0, 5};
    Enemy_in_map[5][1][3].skill[0] = (Enemy_skill) {1, "3*9", King_attack};
    Enemy_in_map[5][1][3].skill[1] = (Enemy_skill) {4, "", King_increase};
    Enemy_in_map[5][1][3].skill[2] = (Enemy_skill) {5, "30", King_attack2};
    Enemy_in_map[5][1][3].skill[3] = (Enemy_skill) {1, "8*4", King_attack3};
    Enemy_in_map[5][1][3].skill[4] = (Enemy_skill) {4, "", King_weaken};
    Enemy_in_map[5][1][2] = (Enemy) {"影卫", IMG_LoadTexture(renderer, "./img/shadow_guard.png"), 200,
                                     0, 4};
    Enemy_in_map[5][1][2].skill[0] = (Enemy_skill) {1, "20", shadow_guard_attack};
    Enemy_in_map[5][1][2].skill[1] = (Enemy_skill) {1, "36", shadow_guard_attack2};
    Enemy_in_map[5][1][2].skill[2] = (Enemy_skill) {3, "", shadow_guard_weaken};
    Enemy_in_map[5][1][2].skill[3] = (Enemy_skill) {1, "2*16", shadow_guard_attack3};
    Enemy_in_map[5][1][1] = (Enemy) {"卫士统领", IMG_LoadTexture(renderer, "./img/Guardian_Commander.png"), 240,
                                     35, 5};
    Enemy_in_map[5][1][1].skill[0] = (Enemy_skill) {1, "5*3", Guardian_Commander_attack};
    Enemy_in_map[5][1][1].skill[1] = (Enemy_skill) {2, "5 to all", Guardian_Commander_defend};
    Enemy_in_map[5][1][1].skill[2] = (Enemy_skill) {2, "15", Guardian_Commander_defend2};
    Enemy_in_map[5][1][1].skill[3] = (Enemy_skill) {4, "", Guardian_Commander_health};
    Enemy_in_map[5][1][1].skill[4] = (Enemy_skill) {5, "", Guardian_Commander_unknow};
    Enemy_in_map[5][1][0] = (Enemy) {"石像鬼", IMG_LoadTexture(renderer, "./img/Gargoyle.png"), 300,
                                     0, 4};
    Enemy_in_map[5][1][0].skill[0] = (Enemy_skill) {2, "20", Gargoyle_defend};
    Enemy_in_map[5][1][0].skill[1] = (Enemy_skill) {1, "3 * 8", Gargoyle_attack};
    Enemy_in_map[5][1][0].skill[2] = (Enemy_skill) {1, "28", Gargoyle_attack2};
    Enemy_in_map[5][1][0].skill[3] = (Enemy_skill) {4, "", Gargoyle_increase};
    Enemy_in_map[5][0][3] = (Enemy) {"法师", IMG_LoadTexture(renderer, "./img/mage.png"), 150,
                                     0, 4};
    Enemy_in_map[5][0][3].skill[0] = (Enemy_skill) {1, "2 * 5", mage_attack};
    Enemy_in_map[5][0][3].skill[1] = (Enemy_skill) {1, "3 * 8", mage_attack2};
    Enemy_in_map[5][0][3].skill[2] = (Enemy_skill) {4, "12 + 20", mage_defend};
    Enemy_in_map[5][0][3].skill[3] = (Enemy_skill) {3, "", mage_wither};
    Enemy_in_map[5][0][2] = (Enemy) {"铳卫", IMG_LoadTexture(renderer, "./img/Gun_Guardian.png"), 180,
                                     0, 2};
    Enemy_in_map[5][0][2].skill[0] = (Enemy_skill) {1, "4 * 5", Gun_Guardian_attack1};
    Enemy_in_map[5][0][2].skill[1] = (Enemy_skill) {1, "3 * 7", Gun_Guardian_attack2};
    Enemy_in_map[5][0][1] = (Enemy) {"盾卫", IMG_LoadTexture(renderer, "./img/Shield_Guard.png"), 500,
                                     0, 4};
    Enemy_in_map[5][0][1].skill[0] = (Enemy_skill) {2, "30", Shield_Guard_defend};
    Enemy_in_map[5][0][1].skill[1] = (Enemy_skill) {1, "50%格挡", Shield_Guard_attack};
    Enemy_in_map[5][0][1].skill[2] = (Enemy_skill) {1, "10+10%格挡", Shield_Guard_attack2};
    Enemy_in_map[5][0][1].skill[3] = (Enemy_skill) {4, "", Shield_Guard_increase};
    Enemy_in_map[5][0][0] = (Enemy) {"剑卫", IMG_LoadTexture(renderer, "./img/Sword_Guardian.png"), 250,
                                     0, 3};
    Enemy_in_map[5][0][0].skill[0] = (Enemy_skill) {1, "2*16", Sword_Guardian_attack};
    Enemy_in_map[5][0][0].skill[1] = (Enemy_skill) {2, "12", Sword_Guardian_defend};
    Enemy_in_map[5][0][0].skill[2] = (Enemy_skill) {1, "28", Sword_Guardian_attack2};
    Enemy_in_map[4][1][4] = (Enemy) {"历史的幻影\n30回合后斩杀玩家", IMG_LoadTexture(renderer, "./img/train.png"), 500,
                                     0, 5};
    Enemy_in_map[4][1][4].skill[0] = (Enemy_skill) {2, "10", train_defend};
    Enemy_in_map[4][1][4].skill[1] = (Enemy_skill) {1, "7*3", train_attack};
    Enemy_in_map[4][1][4].skill[2] = (Enemy_skill) {4, "", train_increase};
    Enemy_in_map[4][1][4].skill[3] = (Enemy_skill) {1, "3*5", train_attack2};
    Enemy_in_map[4][1][4].skill[4] = (Enemy_skill) {4, "", train_increase2};
    Enemy_in_map[4][1][3] = (Enemy) {"炮塔", IMG_LoadTexture(renderer, "./img/turret.png"), 100,
                                     0, 2};
    Enemy_in_map[4][1][3].skill[0] = (Enemy_skill) {1, "8", turret_attack};
    Enemy_in_map[4][1][3].skill[1] = (Enemy_skill) {1, "12", turret_attack2};
    Enemy_in_map[4][1][2] = (Enemy) {"最后的哨兵", IMG_LoadTexture(renderer, "./img/The_Last_Sentinel.png"), 500,
                                     0, 5};
    Enemy_in_map[4][1][2].skill[0] = (Enemy_skill) {1, "18", The_Last_Sentinel_attack};
    Enemy_in_map[4][1][2].skill[1] = (Enemy_skill) {2, "10 to all", The_Last_Sentinel_defend};
    Enemy_in_map[4][1][2].skill[2] = (Enemy_skill) {2, "? * 15", The_Last_Sentinel_defend2};
    Enemy_in_map[4][1][2].skill[3] = (Enemy_skill) {4, "7 to all", The_Last_Sentinel_health};
    Enemy_in_map[4][1][2].skill[4] = (Enemy_skill) {4, "20 to 炮塔", The_Last_Sentinel_health2};
    Enemy_in_map[4][1][1] = (Enemy) {"迷途旅人", IMG_LoadTexture(renderer, "./img/Lost_Traveler.png"), 300,
                                     0, 4};
    Enemy_in_map[4][1][1].skill[0] = (Enemy_skill) {1, "3*8", Lost_Traveler_attack};
    Enemy_in_map[4][1][1].skill[1] = (Enemy_skill) {1, "2*10", Lost_Traveler_attack2};
    Enemy_in_map[4][1][1].skill[2] = (Enemy_skill) {2, "12", Lost_Traveler_defend};
    Enemy_in_map[4][1][1].skill[3] = (Enemy_skill) {4, "", Lost_Traveler_increase};
    Enemy_in_map[4][0][3] = (Enemy) {"雾行鸟", IMG_LoadTexture(renderer, "./img/Fog_walking_Bird.png"), 120,
                                     0, 3};
    Enemy_in_map[4][0][3].skill[0] = (Enemy_skill) {1, "12", Fog_walking_Bird_attack};
    Enemy_in_map[4][0][3].skill[1] = (Enemy_skill) {2, "12", Fog_walking_Bird_defend};
    Enemy_in_map[4][0][3].skill[2] = (Enemy_skill) {1, "2*4", Fog_walking_Bird_attack2};
    Enemy_in_map[4][1][0] = (Enemy) {"腐烂山鬼", IMG_LoadTexture(renderer, "./img/Mountain_Zombie.png"), 200,
                                     0, 4};
    Enemy_in_map[4][1][0].skill[0] = (Enemy_skill) {1, "8", Mountain_Zombie_attack};
    Enemy_in_map[4][1][0].skill[1] = (Enemy_skill) {1, "2*9", Mountain_Zombie_attack2};
    Enemy_in_map[4][1][0].skill[2] = (Enemy_skill) {4, "", Mountain_Zombie_increase};
    Enemy_in_map[4][1][0].skill[3] = (Enemy_skill) {2, "10", Mountain_Zombie_defend};
    Enemy_in_map[4][0][2] = (Enemy) {"幻影", IMG_LoadTexture(renderer, "./img/Phantom.png"), 100,
                                     0, 3};
    Enemy_in_map[4][0][2].skill[0] = (Enemy_skill) {1, "3*4", Phantom_attack};
    Enemy_in_map[4][0][2].skill[1] = (Enemy_skill) {3, "2", Phantom_weaken};
    Enemy_in_map[4][0][2].skill[2] = (Enemy_skill) {1, "5*2 凋零", Phantom_attack2};
    Enemy_in_map[4][0][1] = (Enemy) {"雾鬼", IMG_LoadTexture(renderer, "./img/fog_ghost.png"), 100,
                                     0, 3};
    Enemy_in_map[4][0][1].skill[0] = (Enemy_skill) {4, "", fog_ghost_increase};
    Enemy_in_map[4][0][1].skill[1] = (Enemy_skill) {1, "2*10", fog_ghost_attack};
    Enemy_in_map[4][0][1].skill[2] = (Enemy_skill) {1, "12", fog_ghost_attack2};
    Enemy_in_map[4][0][0] = (Enemy) {"腐化守林人", IMG_LoadTexture(renderer, "./img/Corrupted_Forest_Warden.png"), 120,
                                     0, 2};
    Enemy_in_map[4][0][0].skill[0] = (Enemy_skill) {1, "13-20", Corrupted_Forest_Warden_attack};
    Enemy_in_map[4][0][0].skill[1] = (Enemy_skill) {2, "8-20", Corrupted_Forest_Warden_defend};
    Enemy_in_map[3][1][3] = (Enemy) {"迷失守林人", IMG_LoadTexture(renderer, "./img/The_Lost_Forest_Warden.png"), 250,
                                     0, 5};
    Enemy_in_map[3][1][3].skill[0] = (Enemy_skill) {5, "18", The_Lost_Forest_Warden_attack};
    Enemy_in_map[3][1][3].skill[1] = (Enemy_skill) {5, "6*3", The_Lost_Forest_Warden_attack2};
    Enemy_in_map[3][1][3].skill[2] = (Enemy_skill) {5, "", The_Lost_Forest_Warden_weaken};
    Enemy_in_map[3][1][3].skill[3] = (Enemy_skill) {5, "8", The_Lost_Forest_Warden_defend};
    Enemy_in_map[3][1][3].skill[4] = (Enemy_skill) {5, "", The_Lost_Forest_Warden_nothing};
    Enemy_in_map[3][1][2] = (Enemy) {"人中菌", IMG_LoadTexture(renderer, "./img/Human_Mushroom.png"), 250,
                                     0, 4};
    Enemy_in_map[3][1][2].skill[0] = (Enemy_skill) {1, "7", Human_Mushroom_attack};
    Enemy_in_map[3][1][2].skill[1] = (Enemy_skill) {1, "5*4", Human_Mushroom_attack2};
    Enemy_in_map[3][1][2].skill[2] = (Enemy_skill) {1, "10", Human_Mushroom_attack3};
    Enemy_in_map[3][1][2].skill[3] = (Enemy_skill) {3, "", Human_Mushroom_weaken};
    Enemy_in_map[3][1][1] = (Enemy) {"凋零之树", IMG_LoadTexture(renderer, "./img/withering_tree.png"), 200,
                                     0, 6};
    Enemy_in_map[3][1][1].skill[0] = (Enemy_skill) {4, "10-25", withering_tree_health};
    Enemy_in_map[3][1][1].skill[1] = (Enemy_skill) {1, "15", withering_tree_attack};
    Enemy_in_map[3][1][1].skill[2] = (Enemy_skill) {1, "4*7", withering_tree_attack2};
    Enemy_in_map[3][1][1].skill[3] = (Enemy_skill) {5, "凋零", withering_tree_attack3};
    Enemy_in_map[3][1][1].skill[4] = (Enemy_skill) {1, "15+凋零", withering_tree_attack4};
    Enemy_in_map[3][1][1].skill[5] = (Enemy_skill) {4, "凋零", withering_tree_attack5};
    Enemy_in_map[3][1][0] = (Enemy) {"堕落守林人", IMG_LoadTexture(renderer, "./img/Corrupted_Forest_Ranger.png"), 100,
                                     0, 1};
    Enemy_in_map[3][1][0].skill[0] = (Enemy_skill) {1, "12-20", Corrupted_Forest_Ranger_attack};
    Enemy_in_map[3][0][0] = (Enemy) {"腐尸", IMG_LoadTexture(renderer, "./img/zombie.png"), 150, 0, 3};
    Enemy_in_map[3][0][0].skill[0] = (Enemy_skill) {1, "6", zombie_attack};
    Enemy_in_map[3][0][0].skill[1] = (Enemy_skill) {1, "2*7", zombie_attack2};
    Enemy_in_map[3][0][0].skill[2] = (Enemy_skill) {5, "", zombie_fraglie};
    Enemy_in_map[1][0][0] = (Enemy) {"拾荒者", IMG_LoadTexture(renderer, "./img/ragpicker.png"), 45, 0, 3};
    Enemy_in_map[1][0][0].skill[0] = (Enemy_skill) {1, "2*3", ragpicker_attack};
    Enemy_in_map[1][0][0].skill[1] = (Enemy_skill) {4, "", ragpicker_Strengthen};
    Enemy_in_map[1][0][0].skill[2] = (Enemy_skill) {3, "5", ragpicker_Weaken};
    Enemy_in_map[1][0][1] = (Enemy) {"秃鹫", IMG_LoadTexture(renderer, "./img/vulture.png"), 25, 0, 3};
    Enemy_in_map[1][0][1].skill[0] = (Enemy_skill) {2, "3", vulture_block};
    Enemy_in_map[1][0][1].skill[1] = (Enemy_skill) {1, "3", vulture_attack};
    Enemy_in_map[1][0][1].skill[2] = (Enemy_skill) {1, "7", vulture_attack2};
    Enemy_in_map[1][0][2] = (Enemy) {"盗贼", IMG_LoadTexture(renderer, "./img/Thief.png"), 35, 0, 3};
    Enemy_in_map[1][0][2].skill[0] = (Enemy_skill) {3, "2", Thief_attack};
    Enemy_in_map[1][0][2].skill[1] = (Enemy_skill) {3, "5", Thief_attack2};
    Enemy_in_map[1][0][2].skill[2] = (Enemy_skill) {2, "5", Thief_block};
    Enemy_in_map[1][1][0] = (Enemy) {"孤魂野鬼", IMG_LoadTexture(renderer, "./img/wandering_ghost.png"), 40, 0, 5};
    Enemy_in_map[1][1][0].skill[0] = (Enemy_skill) {5, "10", wandering_ghost_recover};
    Enemy_in_map[1][1][0].skill[1] = (Enemy_skill) {3, "8*2", wandering_ghost_attack};
    Enemy_in_map[1][1][0].skill[2] = (Enemy_skill) {3, "", wandering_ghost_weaken};
    Enemy_in_map[1][1][0].skill[3] = (Enemy_skill) {1, "8", wandering_ghost_attack2};
    Enemy_in_map[1][1][0].skill[4] = (Enemy_skill) {2, "10", wandering_ghost_block};
    Enemy_in_map[2][0][0] = (Enemy) {"猎人", IMG_LoadTexture(renderer, "./img/hunter.png"), 65, 0, 4};
    Enemy_in_map[2][0][0].skill[0] = (Enemy_skill) {4, "10", hunter_strengthen};
    Enemy_in_map[2][0][0].skill[1] = (Enemy_skill) {1, "2*5", hunter_attack1};
    Enemy_in_map[2][0][0].skill[2] = (Enemy_skill) {1, "9", hunter_attack2};
    Enemy_in_map[2][0][0].skill[3] = (Enemy_skill) {1, "10(+5)", hunter_attack3};
    Enemy_in_map[2][0][1] = (Enemy) {"树人", IMG_LoadTexture(renderer, "./img/treeman.png"), 90, 0, 3};
    Enemy_in_map[2][0][1].skill[0] = (Enemy_skill) {1, "8", treeman_attack1};
    Enemy_in_map[2][0][1].skill[1] = (Enemy_skill) {1, "4*4", treeman_attack2};
    Enemy_in_map[2][0][1].skill[2] = (Enemy_skill) {2, "10", treeman_defense};
    Enemy_in_map[2][0][2] = (Enemy) {"哥布林", IMG_LoadTexture(renderer, "./img/Goblin.png"), 60, 0, 3};
    Enemy_in_map[2][0][2].skill[0] = (Enemy_skill) {4, "5", goblin_health};
    Enemy_in_map[2][0][2].skill[1] = (Enemy_skill) {1, "6", goblin_attack};
    Enemy_in_map[2][0][2].skill[2] = (Enemy_skill) {1, "8", goblin_attack2};
    Enemy_in_map[2][0][3] = (Enemy) {"史莱姆", IMG_LoadTexture(renderer, "./img/slime.png"), 40, 0, 4};
    Enemy_in_map[2][0][3].skill[0] = (Enemy_skill) {2, "8", slime_block};
    Enemy_in_map[2][0][3].skill[1] = (Enemy_skill) {2, "3*all", slime_block2};
    Enemy_in_map[2][0][3].skill[2] = (Enemy_skill) {1, "2+50%block", slime_attack};
    Enemy_in_map[2][0][3].skill[3] = (Enemy_skill) {5, "", slime_block_to_player};
    Enemy_in_map[2][1][0] = (Enemy) {"老猎人", IMG_LoadTexture(renderer, "./img/oldhunter.png"), 95, 0, 4};
    Enemy_in_map[2][1][0].skill[0] = (Enemy_skill) {3, "3*5", oldhunter_attack1};
    Enemy_in_map[2][1][0].skill[1] = (Enemy_skill) {2, "20", oldhunter_block};
    Enemy_in_map[2][1][0].skill[2] = (Enemy_skill) {1, "2*7", oldhunter_attack2};
    Enemy_in_map[2][1][0].skill[3] = (Enemy_skill) {1, "12", oldhunter_attack3};
    Enemy_in_map[2][1][1] = (Enemy) {"哥布林首领", IMG_LoadTexture(renderer, "./img/Goblin_Chief.png"), 100, 0, 4};
    Enemy_in_map[2][1][1].skill[0] = (Enemy_skill) {1, "9", Goblin_Chief_attack};
    Enemy_in_map[2][1][1].skill[1] = (Enemy_skill) {1, "8", Goblin_Chief_attack2};
    Enemy_in_map[2][1][1].skill[2] = (Enemy_skill) {1, "5*3", Goblin_Chief_attack3};
    Enemy_in_map[2][1][1].skill[3] = (Enemy_skill) {2, "10+7", Goblin_Chief_health};
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
        //printf("Not enough energy to use the card!\n");
        return;
    }
    if (main_collection[1][5].get) {
        player_get_hp(player, 1);
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

void get_potion(Player *player, Potion *potion) {
    if (player->player_career != 2 && player->sum_Potion > 2) {
        return;
    }
    if (player->player_career == 2 && player->sum_Potion > 4) {
        return;
    }
    player->sum_Potion++;
    player->potions = (Potion **) realloc(player->potions, player->sum_Potion * sizeof(Potion *));
    player->potions[player->sum_Potion - 1] = potion;
}

void discard_potion(Player *player, int index) {
    if (index > player->sum_Potion) {
        return;
    }
    for (int i = index; i < player->sum_Potion - 1; i++) {
        player->potions[i] = player->potions[i + 1];
    }
    player->sum_Potion--;
    player->potions = (Potion **) realloc(player->potions, player->sum_Potion * sizeof(Potion *));
}

void use_potion(Player *player, int index) {
    if (index > player->sum_Potion) {
        return;
    }
    player->potions[index]->effect(player);
    discard_potion(player, index);
}

extern int main_collection_num[7];
extern Collection main_collection[7][10];

void player_get_collection(Player *player, int x, int y) {
    main_collection[x][y].get = true;
    player->sum_collection++;
    player->collections = (Collection **) realloc(player->collections, player->sum_collection * sizeof(Collection *));
    player->collections[player->sum_collection - 1] = &main_collection[x][y];
    if (x == 0 && y == 0) {
        player->maxhp += 5;
        player->hp += 5;
    }
    if (x == 0 && y == 1) {
        player->coin += 30;
    }
    if (x == 1 && y == 0) {
        player->coin += 100;
    }
    if (x == 1 && y == 2) {
        player->maxhp += 10;
        player->hp += 10;
    }
    if (x == 0 && y == 3) {
        add_card_to_bag(player,
                        &main_card[player->player_career][generate_random(2, main_cardnum[player->player_career] - 1)]);
    }
    if (x == 2 && y == 1) {
        add_card_to_bag(player,
                        &main_card[player->player_career][generate_random(2, main_cardnum[player->player_career] - 1)]);
        add_card_to_bag(player,
                        &main_card[player->player_career][generate_random(2, main_cardnum[player->player_career] - 1)]);
        add_card_to_bag(player,
                        &main_card[player->player_career][generate_random(2, main_cardnum[player->player_career] - 1)]);

    }
    if (x == 6 && y == 2) {
        player->hp = player->hp * 0.7;
        if (player->hp <= 0) {
            player->hp = 1;
        }
    }
    if (x == 1 && y == 3) {
        player_get_hp(player, player->maxhp / 4);
    }
    if (x == 0 && y == 4) {
        player->coin++;
    }
}