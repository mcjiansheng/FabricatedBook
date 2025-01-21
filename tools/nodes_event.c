//
// Created by 48811 on 25-1-17.
//

#include "nodes_event.h"

extern int Enemy_num_in_map[7][2];
extern Enemy Enemy_in_map[7][2][10];
extern int fight_in_map[7][2];
extern Fight fight_map[7][2][10];
extern int main_Enemynum;
extern Enemy main_enemy[3];

extern int round_times;

void event_init() {

    fight_in_map[1][0] = 1;
    fight_map[1][0][0] = (Fight) {3, &Enemy_in_map[1][0][0], &Enemy_in_map[1][0][0], &Enemy_in_map[1][0][0]};
}

extern int deadly_tempotimes;

void decide_enemy_step(Enemy *enemy) {
    enemy->next_step = generate_random(0, enemy->skill_num - 1);
}

void fight_start(Fight *fight, Player *player) {
    round_times = 0;
    init_buff(&player->buff);
    main_Enemynum = fight->enemy_num;
    for (int i = 0; i < fight->enemy_num; i++) {
        main_enemy[i] = *fight->enemy[i];
        init_buff(&main_enemy[i].buff);
        decide_enemy_step(&main_enemy[i]);
    }
    deadly_tempotimes = 0;
    for (int i = 0; i < player->sum_deck_size; i++) {
        add_card_to_deck(player, player->sum_deck[i]);
    }
}

void print_Buff(SDL_Renderer *renderer, char *str, int x, int y, int t, SDL_Color color) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, str);
    SDL_Rect rect = {x, y, 20, 20};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    if (t < 100 && t > 0) {
        char *text = malloc(20 * sizeof(char));
        TTF_Font *font = TTF_OpenFont("./res/ys_zt.ttf", 16);
        sprintf(text, "%d", t);
        draw_text(renderer, font, text, x + 20, y, color);
        TTF_CloseFont(font);
        free(text);
    }
}

#define Buff_diff 50
#define Buff_lent 200
#define Buff_rowd 30

int round_progress;//-1 敌人 1 我方

void draw_Buff(SDL_Renderer *renderer, Buff *buff, int x, int y) {
    int plus_x = 0, plus_y = 0;
    if (buff->fragile > 0) {
        print_Buff(renderer, "./img/fragile.png", x + plus_x, y + plus_y, buff->fragile, COLOR_LIGHT_RED);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
    if (buff->block_reduction > 0) {
        print_Buff(renderer, "./img/block_reduction.png", x + plus_x, y + plus_y, buff->block_reduction,
                   COLOR_LIGHT_RED);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
    if (buff->resistance > 0) {
        print_Buff(renderer, "./img/resistance.png", x + plus_x, y + plus_y, buff->resistance, COLOR_BLACK);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
    if (buff->block_increase > 0) {
        print_Buff(renderer, "./img/block_increase.png", x + plus_x, y + plus_y, buff->block_increase, COLOR_GREY);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
    if (buff->weak > 0) {
        print_Buff(renderer, "./img/weak.png", x + plus_x, y + plus_y, buff->weak, COLOR_LIGHT_BLUE);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
    if (buff->strength > 0) {
        print_Buff(renderer, "./img/strength.png", x + plus_x, y + plus_y, buff->strength, COLOR_LIGHT_RED);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
    if (buff->dizziness > 0) {
        print_Buff(renderer, "./img/dizziness.png", x + plus_x, y + plus_y, buff->dizziness, COLOR_DARK_YELLOW);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
    if (buff->poisoning > 0) {
        print_Buff(renderer, "./img/poisoning.png", x + plus_x, y + plus_y, buff->poisoning, COLOR_GREYGREEN);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
    if (buff->withering > 0) {
        print_Buff(renderer, "./img/withering.png", x + plus_x, y + plus_y, buff->withering, COLOR_BLACK);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
    if (buff->flame > 0) {
        print_Buff(renderer, "./img/flame.png", x + plus_x, y + plus_y, buff->flame, COLOR_RED);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
    if (buff->freezing > 0) {
        print_Buff(renderer, "./img/freezing.png", x + plus_x, y + plus_y, buff->freezing, COLOR_LIGHT_BLUE);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
    if (buff->lightning > 0) {
        print_Buff(renderer, "./img/lightning.png", x + plus_x, y + plus_y, buff->lightning, COLOR_DARK_YELLOW);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
    if (buff->armor > 0) {
        print_Buff(renderer, "./img/armor.png", x + plus_x, y + plus_y, buff->armor, COLOR_BLACK);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
    if (buff->undead > 0) {
        print_Buff(renderer, "./img/undead.png", x + plus_x, y + plus_y, buff->undead, COLOR_RED);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
    if (buff->extra_energy[0] > 0 || buff->extra_energy[1] > 0 || buff->extra_energy[2] > 0) {
        print_Buff(renderer, "./img/extra_energy.png", x + plus_x, y + plus_y,
                   max(buff->extra_energy[0], max(buff->extra_energy[1], buff->extra_energy[2])), COLOR_ORANGE);
        plus_x += Buff_diff;
        if (plus_x >= Buff_lent) {
            plus_x = 0;
            plus_y += Buff_rowd;
        }
    }
}

void print_players(SDL_Renderer *renderer, Player *player) {
    SDL_Texture *texture;
    if (player->player_career == 1) {
        texture = IMG_LoadTexture(renderer, "./img/Warrior.png");
    } else {
        printf("player's career is wrong!\n");
        return;
    }
    SDL_Rect rect = {400, 400, 200, 350};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    draw_Buff(renderer, &player->buff, rect.x, rect.y + rect.h);
}


void draw_enemy_next_step(SDL_Renderer *renderer, int x, int y, Enemy *enemy) {
    SDL_Color color;
    char *text = malloc(20 * sizeof(char));
    TTF_Font *State_font = TTF_OpenFont("./res/ys_zt.ttf", 20);
    if (State_font == NULL) {
        printf("texture is null!\n");
        exit(0);
    }
    SDL_Texture *texture;
    switch (enemy->skill[enemy->next_step].type) {
        case 1:
            color = COLOR_RED;
            texture = IMG_LoadTexture(renderer, "./img/atk.png");
            break;
        case 2:
            color = COLOR_BLACK;
            texture = IMG_LoadTexture(renderer, "./img/def.png");
            break;
        case 3:
            color = COLOR_RED;
            texture = IMG_LoadTexture(renderer, "./img/wek.png");
            break;
        case 4:
            color = COLOR_RED;
            texture = IMG_LoadTexture(renderer, "./img/inc.png");
            break;
        default:
            color = COLOR_BACKGROUND_GREY;
            texture = IMG_LoadTexture(renderer, "./img/ukn.png");
    }
    if (texture == NULL) {
        printf("texture is null!\n");
        exit(0);
    }
    SDL_Rect rect = {x - 15, y - 15, 30, 30};
//    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
//    printf("print enemy next skill successful! %d\n", enemy->skill[enemy->next_step].type);
    if (strcmp(enemy->skill[enemy->next_step].qua, "")) {
        draw_text(renderer, State_font, enemy->skill[enemy->next_step].qua, x + 20, y, color);
    }
    free(text);
    TTF_CloseFont(State_font);
}

void print_enemys(SDL_Renderer *renderer) {
    TTF_Font *State_font = TTF_OpenFont("./res/ys_zt.ttf", 20);
    char *text = malloc(20 * sizeof(char));
    if (main_Enemynum > 0 && main_enemy[0].hp > 0) {
        SDL_Rect rect = {1350, 400};
        SDL_QueryTexture(main_enemy[0].texture, NULL, NULL, &rect.w, &rect.h);
        rect.h = rect.h * 200 / rect.w;
        rect.w = 200;
        SDL_RenderCopy(renderer, main_enemy[0].texture, NULL, &rect);
        sprintf(text, "hp: %d", main_enemy[0].hp);
        draw_text(renderer, State_font, text, 1380, 400, COLOR_LIGHT_RED);
        if (main_enemy[0].block > 0) {
            sprintf(text, "block: %d", main_enemy[0].block);
            draw_text(renderer, State_font, text, 1400, 400, COLOR_BLACK);
        }
        draw_enemy_next_step(renderer, 1380, 370, &main_enemy[0]);
        draw_Buff(renderer, &main_enemy[0].buff, 1350, 400 + rect.h);
    }
    if (main_Enemynum > 1 && main_enemy[1].hp > 0) {
        SDL_Rect rect = {1150, 450};
        SDL_QueryTexture(main_enemy[1].texture, NULL, NULL, &rect.w, &rect.h);
        rect.h = rect.h * 200 / rect.w;
        rect.w = 200;
        SDL_RenderCopy(renderer, main_enemy[1].texture, NULL, &rect);
        sprintf(text, "hp: %d", main_enemy[1].hp);
        draw_text(renderer, State_font, text, 1180, 450, COLOR_LIGHT_RED);
        if (main_enemy[1].block > 0) {
            sprintf(text, "block: %d", main_enemy[1].block);
            draw_text(renderer, State_font, text, 1200, 400, COLOR_BLACK);
        }
        draw_enemy_next_step(renderer, 1180, 420, &main_enemy[1]);
        draw_Buff(renderer, &main_enemy[1].buff, rect.x, rect.y + rect.h);
    }
    if (main_Enemynum > 2 && main_enemy[2].hp > 0) {
        SDL_Rect rect = {1550, 350};
        SDL_QueryTexture(main_enemy[2].texture, NULL, NULL, &rect.w, &rect.h);
        rect.h = rect.h * 200 / rect.w;
        rect.w = 200;
        SDL_RenderCopy(renderer, main_enemy[2].texture, NULL, &rect);
        sprintf(text, "hp: %d", main_enemy[2].hp);
        draw_text(renderer, State_font, text, 1580, 350, COLOR_LIGHT_RED);
        if (main_enemy[2].block > 0) {
            sprintf(text, "block: %d", main_enemy[2].block);
            draw_text(renderer, State_font, text, 1600, 400, COLOR_BLACK);
        }
        draw_enemy_next_step(renderer, 1580, 320, &main_enemy[2]);
        draw_Buff(renderer, &main_enemy[2].buff, rect.x, rect.y + rect.h);
    }
    free(text);
    TTF_CloseFont(State_font);
}

void round_start(Player *player) {
    round_times++;
    for (int i = 0; i < 5; i++) {
        if (player->deck_size == 0 && player->discard_pile_size == 0) {
            break;
        }
        draw_card(player);
    }
    player->energy = 3;
    if (round_times % 2 == 1 && player->player_career == 2) {
        player->energy++;
    }
    for (int i = 0; i < 3; i++) {
        if (player->buff.extra_energy[i] > 0) {
            player->energy += i + 1;
            player->buff.extra_energy[i]--;
        }
    }
    if (player->buff.armor <= 0) {
        player->block = 0;
    } else {
        player->buff.armor--;
    }
    round_progress = 1;
}

extern int windowWidth, windowHeight;
#define CARD_WIDTH 150
#define CARD_HEIGHT 225
#define CARD_DIF 175

void print_a_hand_card(SDL_Renderer *renderer, Card *card, bool hover, bool press, SDL_Rect rect, TTF_Font *font,
                       TTF_Font *title_font) {
    print_card(renderer, card, rect, hover, press, font, title_font);
}

void print_hand_cards(SDL_Renderer *renderer, Player *player, int choose_card, int mouse_x, int mouse_y) {
    int x, y;
    int n = player->hand_size;
    y = 800;
    x = windowWidth / 2;
    x -= CARD_DIF * n / 2;
    bool hover = false, press = false;
    SDL_Rect rect;
    TTF_Font *font = TTF_OpenFont("./res/ys_zt.ttf", 20), *title_font = TTF_OpenFont("./res/ys_zt.ttf", 30);
//    printf("hand card num :%d\n", n);
    for (int i = 0; i < n; i++) {
//        printf("i:%d mouse:%d %d rect %d %d %d %d\n", i, mouse_x, mouse_y, rect.x, rect.y, rect.w, rect.h);
        if (choose_card == i) {
            press = true;
        } else {
            press = false;
        }
        rect = (SDL_Rect) {x + CARD_WIDTH / 2, y, CARD_WIDTH, CARD_HEIGHT};
        if (mouse_x >= rect.x && mouse_x < rect.x + rect.w && mouse_y >= rect.y && mouse_y < rect.y + rect.h) {
            hover = true;
        } else {
            hover = false;
        }
        print_a_hand_card(renderer, player->hand[i], hover, press, rect, font, title_font);
        x += CARD_DIF;
    }
    TTF_CloseFont(font);
    TTF_CloseFont(title_font);
}

void player_choose_card(Player *player, int mouse_x, int mouse_y, int *choose_card) {
    int x, y;
    int n = player->hand_size;
    y = 800;
    x = windowWidth / 2;
    SDL_Rect rect;
    x -= CARD_DIF * n / 2;
    for (int i = 0; i < n; i++) {

        rect = (SDL_Rect) {x + CARD_WIDTH / 2, y, CARD_WIDTH, CARD_HEIGHT};
        if (mouse_x >= rect.x && mouse_x < rect.x + rect.w && mouse_y >= rect.y && mouse_y < rect.y + rect.h) {
            *choose_card = i;
        }
        x += CARD_DIF;
    }
}

/*
bool mouse_in_rect(int mouse_x, int mouse_y, SDL_Rect rect) {
    return mouse_x >= rect.x && mouse_x < rect.x + rect.w && mouse_y >= rect.y && mouse_y < rect.y + rect.h;
}*/

void player_aim(Player *player, int mouse_x, int mouse_y, int *choose_card) {
    Card *card = player->hand[*choose_card];
    bool aim = card->need_aim;
    SDL_Rect rect = {400, 400, 200, 350};
    if (!aim && mouse_in_rect(rect, mouse_x, mouse_y)) {
        use_card(player, choose_card, NULL);
    }
    rect = (SDL_Rect) {1350, 400};
    SDL_QueryTexture(main_enemy[0].texture, NULL, NULL, &rect.w, &rect.h);
    rect.h = rect.h * 200 / rect.w;
    rect.w = 200;
    if (main_Enemynum > 0 && main_enemy[0].hp > 0 && mouse_in_rect(rect, mouse_x, mouse_y)) {
        use_card(player, choose_card, &main_enemy[0]);
    }
    rect = (SDL_Rect) {1150, 450};
    SDL_QueryTexture(main_enemy[1].texture, NULL, NULL, &rect.w, &rect.h);
    rect.h = rect.h * 200 / rect.w;
    rect.w = 200;
    if (main_Enemynum > 1 && main_enemy[1].hp > 0 && mouse_in_rect(rect, mouse_x, mouse_y)) {
        use_card(player, choose_card, &main_enemy[1]);
    }
    rect = (SDL_Rect) {1550, 350};
    SDL_QueryTexture(main_enemy[2].texture, NULL, NULL, &rect.w, &rect.h);
    rect.h = rect.h * 200 / rect.w;
    rect.w = 200;
    if (main_Enemynum > 2 && main_enemy[2].hp > 0 && mouse_in_rect(rect, mouse_x, mouse_y)) {
        use_card(player, choose_card, &main_enemy[2]);
    }
}

//extern const char *sug[];
void Buff_update(Player *player) {
    for (int i = 0; i < main_Enemynum; i++) {
        if (main_enemy[i].hp <= 0) {
            continue;
        }
        if (main_enemy[i].buff.poisoning > 0) {
            main_enemy[i].hp -= main_enemy[i].buff.poisoning;
        }
        if (main_enemy[i].buff.withering > 0) {
            main_enemy[i].buff.withering_times++;
            main_enemy[i].hp -= main_enemy[i].buff.withering_times;
        }
        if (main_enemy[i].buff.undead > 0 && main_enemy[i].hp <= 0) {
            main_enemy[i].hp = 1;
        }
    }
    if (player->buff.poisoning > 0) {
        player->hp -= player->buff.poisoning;
    }
    if (player->buff.withering > 0) {
        player->buff.withering_times++;
        player->hp -= player->buff.withering_times;
    }
    if (player->buff.undead > 0 && player->hp <= 0) {
        player->hp = 1;
    }
}

void Enemy_Action(Player *player, Enemy *enemy) {
    if (enemy->buff.armor <= 0) {
        enemy->block = 0;
    } else {
        enemy->buff.armor--;
    }
    enemy->skill[enemy->next_step].effect(player, enemy);
    enemy->next_step = generate_random(0, enemy->skill_num - 1);
}

void round_settlement(Player *player, int *times) {
    if (*times == 0) {
        for (int i = 0; i < player->hand_size; i++) {
            player->discard_pile_size++;
            player->discard_pile = (Card **) realloc(player->discard_pile, player->discard_pile_size * sizeof(Card *));
            player->discard_pile[player->discard_pile_size - 1] = player->hand[i];
        }
        player->hand_size = 0;
        player->hand = (Card **) realloc(player->hand, player->hand_size * sizeof(Card *));
        Buff_update(player);
    }
    if (*times == 50) {
        if (main_Enemynum > 0 && main_enemy[0].hp > 0) {
            Enemy_Action(player, &main_enemy[0]);
        } else {
            *times += 199;
        }
    }
    if (*times == 250) {
        if (main_Enemynum > 1 && main_enemy[1].hp > 0) {
            Enemy_Action(player, &main_enemy[1]);
        } else {
            *times += 199;
        }
    }
    if (*times == 450) {
        if (main_Enemynum > 2 && main_enemy[2].hp > 0) {
            Enemy_Action(player, &main_enemy[2]);
        } else {
            *times += 199;
        }
    }
    if (*times == 550) {
        buff_decrease(&player->buff);
        for (int i = 0; i < 3; i++) {
            if (main_Enemynum > i && main_enemy[i].hp > 0) {
                buff_decrease(&main_enemy[0].buff);
            }
        }
    }
}

void game_fight(SDL_Window *window, SDL_Renderer *renderer, Fight *fight, Player *player) {
    fight_start(fight, player);
    SDL_Event event;
    int quit = 0;
    char *hp_text = malloc(20 * sizeof(char)), *coin_text = malloc(20 * sizeof(char)), *text = malloc(
            20 * sizeof(char));
    TTF_Font *State_font = TTF_OpenFont("./res/ys_zt.ttf", 45);
    TTF_Font *advise_font = TTF_OpenFont("./res/ys_zt.ttf", 30);
    int choose_card = -1, mouse_x = 0, mouse_y = 0;
    round_start(player);
    Button next_round;
    Title advise;
    Title_init(&advise, "请选择要使用的卡牌", advise_font, 0.5, 0.3, COLOR_BLACK);
//    char *advise=sug[0];
    initButton(&next_round, (Rect) {0.5, 0.62, 0.10, 0.05}, window, COLOR_GREY,
               COLOR_GREYGREEN,
               COLOR_LIGHT_RED, "下一回合", "./res/ys_zt.ttf", 10);
    int times = 0;
    while (!quit) {
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);
        SDL_RenderClear(renderer);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    free(hp_text);
                    free(coin_text);
                    free(text);
                    TTF_CloseFont(State_font);
                    Button_destroy(&next_round);
                    Title_destroy(&advise);
                    game_Quit(window, renderer);
                    break;
                case SDL_WINDOWEVENT:
                    break;
                case SDL_MOUSEMOTION:
                    mouse_x = event.motion.x;
                    mouse_y = event.motion.y;
                    next_round.isHovered = isMouseInButton(event.motion.x, event.motion.y, &next_round);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (round_progress == 1) {
                        player_choose_card(player, mouse_x, mouse_y, &choose_card);
                    }
                    if (choose_card != -1) {
                        player_aim(player, mouse_x, mouse_y, &choose_card);
                    }
                    next_round.isPressed = isMouseInButton(event.motion.x, event.motion.y, &next_round);
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (round_progress == 1 && next_round.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &next_round)) {
                        times = 0;
                        round_progress = -1;
                        printf("next_round clicked!\n");
                    }
                    next_round.isPressed = false;
                    break;
            }
        }
        if (choose_card == -1) {
            advise.text = "请选择要使用的卡牌";
        } else if (player->energy < player->hand[choose_card]->cost) {
            advise.text = "能量不足";
        } else {
            advise.text = "请选择释放对象";
        }
        if (round_progress == 1) {
            drawButton(renderer, &next_round);
            print_hand_cards(renderer, player, choose_card, mouse_x, mouse_y);
        } else {
            round_settlement(player, &times);
            times++;
            if (times < 50) {
                advise.text = "伤害结算中";
            } else if (times < 250) {
                advise.text = "1号敌人行动中";
            } else if (times < 450) {
                advise.text = "2号敌人行动中";
            } else if (times < 550) {
                advise.text = "3号敌人行动中";
            } else {
                advise.text = "状态结算中";
            }
            if (times > 700) {
                times = 0;
                round_start(player);
            }
        }
        Title_print(&advise, window, renderer);
        print_players(renderer, player);
        print_enemys(renderer);
        sprintf(hp_text, "生命值: %d / %d", player->hp, player->maxhp);
        draw_text(renderer, State_font, hp_text, 50, 50, COLOR_LIGHT_RED);
        sprintf(text, "格挡: %d", player->block);
        draw_text(renderer, State_font, text, 120, 200, COLOR_BLACK);
        sprintf(coin_text, "金币: %d", player->coin);
        draw_text(renderer, State_font, coin_text, 800, 50, COLOR_DARK_YELLOW);
        sprintf(text, "牌堆: %d", player->deck_size);
        draw_text(renderer, State_font, text, 150, 700, COLOR_BLACK);
        sprintf(text, "弃牌堆: %d", player->discard_pile_size);
        draw_text(renderer, State_font, text, 1700, 700, COLOR_BLACK);
        sprintf(text, "能量: %d", player->energy);
        draw_text(renderer, State_font, text, 700, 700, COLOR_ORANGE);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
}