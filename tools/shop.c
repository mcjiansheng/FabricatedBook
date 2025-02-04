//
// Created by 48811 on 25-2-3.
//

#include "shop.h"

extern int main_collection_num[7];
extern Collection main_collection[7][10];
extern int main_potion_num;
extern Potion main_potion[20];
extern Card main_card[4][50];
extern int main_cardnum[4];

Shop *init_shop(Player *player) {
    Shop *shop = malloc(sizeof(Shop));
    for (int i = 0; i < 7; i++) {
        int index = generate_random(3, main_cardnum[player->player_career] - 1);
        shop->card[i] = &main_card[player->player_career][index];
        shop->card_coin[i] = (shop->card[i]->value * 40) + generate_random(10, 30);
    }
    int x[3], y[3];
    for (int i = 0; i < 3; i++) {
        int arr[5] = {30, 25, 20, 15, 10};
        int collection_get_x, collection_get_y;
        if (all_collections_had()) {
            collection_get_x = 0;
            collection_get_y = 0;
        } else {
            bool flag = false;
            do {
                collection_get_x = generate_random_with_weighted(arr);
                collection_get_y = generate_random(0, main_collection_num[collection_get_x] - 1);
                flag = false;
                for (int j = 0; j <= i - 1; j++) {
                    if (collection_get_x == x[j] && collection_get_y == y[j]) {
                        flag = true;
                    }
                }
            } while (main_collection[collection_get_x][collection_get_y].get || flag);
        }

        shop->collection[i] = &main_collection[collection_get_x][collection_get_y];
        shop->collection_coin[i] = (collection_get_x + 2) * 25 + generate_random(5, 20);
        shop->collection_x[i] = collection_get_x;
        shop->collection_y[i] = collection_get_y;
        x[i] = collection_get_x;
        y[i] = collection_get_y;
    }
    int p[3];
    for (int i = 0; i < 3; i++) {
        int index = generate_random(0, main_potion_num - 1);
        bool flag = false;
        do {
            flag = false;
            index = generate_random(0, main_potion_num - 1);
            for (int j = 0; j < i - 1; j++) {
                if (p[j] == index) {
                    flag = true;
                }
            }
        } while (flag);
        shop->potion[i] = &main_potion[index];
        shop->potion_coin[i] = generate_random(30, 70);
        p[i] = index;
    }
    shop->discard_able = true;
    return shop;
}

void free_shop(Shop *shop) {
    free(shop);
}

void draw_shop(SDL_Renderer *renderer, Player *player, Shop *shop, int mouse_x, int mouse_y, int press) {
    int i;
    TTF_Font *font = TTF_OpenFont("./res/ys_zt.ttf", 18), *title_font = TTF_OpenFont("./res/ys_zt.ttf", 25);
    SDL_Rect rect = {400, 200, 200, 300};
    char *text = malloc(20 * sizeof(char));
    for (i = 0; i < 7; i++) {
        if (shop->card[i] == NULL) {
            rect.x += rect.w * 1.25;
            if ((i + 1) % 5 == 0) {
                rect.x = 400;
                rect.y += rect.h * 1.25;
            }
            continue;
        }
        print_card(renderer, shop->card[i], rect, mouse_in_rect(rect, mouse_x, mouse_y),
                   mouse_in_rect(rect, mouse_x, mouse_y) && press, font,
                   title_font);
        sprintf(text, "价格: %d", shop->card_coin[i]);
        draw_text_with_alpha(renderer, font, text, rect.x + rect.w / 2, rect.y + (rect.h / 4 * 3),
                             (player->coin >= shop->card_coin[i] ? COLOR_DARK_YELLOW : COLOR_RED), 255);
        rect.x += rect.w * 1.25;
        if ((i + 1) % 5 == 0) {
            rect.x = 400;
            rect.y += rect.h * 1.25;
        }
    }
    TTF_Font *coll_font = TTF_OpenFont("./res/ys_zt.ttf", 14), *coll_title_font = TTF_OpenFont("./res/ys_zt.ttf", 20);
    SDL_Rect coll_rect = {900, 550, 170, 150};
    for (i = 0; i < 3; i++) {
        if (shop->collection[i] == NULL) {
            coll_rect.x += coll_rect.w * 1.25;
            continue;
        }
        print_collection(renderer, shop->collection[i], coll_rect, coll_font,
                         coll_title_font);
        sprintf(text, "价格: %d", shop->collection_coin[i]);
        draw_text_with_alpha(renderer, font, text, coll_rect.x + coll_rect.w / 2, coll_rect.y + (coll_rect.h / 5 * 4),
                             (player->coin >= shop->collection_coin[i] ? COLOR_DARK_YELLOW : COLOR_RED), 255);
        coll_rect.x += coll_rect.w * 1.25;
    }
    SDL_Rect pot_rect = {900, 750, 170, 150};
    for (i = 0; i < 3; i++) {
        if (shop->potion[i] == NULL) {
            pot_rect.x += pot_rect.w * 1.25;
            continue;
        }
        Potion *potion = shop->potion[i];
        Collection collection = (Collection) {potion->name, potion->discribe, 2, false};
        print_collection(renderer, &collection, pot_rect, coll_font,
                         coll_title_font);
        sprintf(text, "价格: %d", shop->potion_coin[i]);
        draw_text_with_alpha(renderer, font, text, pot_rect.x + pot_rect.w / 2, pot_rect.y + (pot_rect.h / 5 * 4),
                             (player->coin >= shop->potion_coin[i] ? COLOR_DARK_YELLOW : COLOR_RED), 255);
        pot_rect.x += pot_rect.w * 1.25;
    }
    if (shop->discard_able) {
        SDL_Rect dis_rect = {1550, 550, 200, 300};
        Collection collection = (Collection) {"弃牌", "选择一张牌弃置\n整场每次使用价格+25\n每个商店只能使用一次",
                                              5, false};
        print_collection(renderer, &collection, dis_rect, font,
                         title_font);
        sprintf(text, "价格: %d", discard_coin);
        draw_text_with_alpha(renderer, font, text, dis_rect.x + dis_rect.w / 2, dis_rect.y + (dis_rect.h / 5 * 4),
                             (player->coin >= discard_coin ? COLOR_DARK_YELLOW : COLOR_RED), 255);
    }
    free(text);
}

void player_buy_card(Player *player, Shop *shop, int index) {
    if (shop->card_coin[index] > player->coin) {
        return;
    }
    player->coin -= shop->card_coin[index];
    add_card_to_bag(player, shop->card[index]);
    shop->card[index] = NULL;
}

void player_buy_collection(Player *player, Shop *shop, int index) {
    if (shop->collection_coin[index] > player->coin) {
        return;
    }
    player->coin -= shop->collection_coin[index];
    player_get_collection(player, shop->collection_x[index], shop->collection_y[index]);
    shop->collection[index] = NULL;
}

void player_buy_potion(Player *player, Shop *shop, int index) {
    if (shop->potion_coin[index] > player->coin) {
        return;
    }
    if (player->sum_Potion >= 3 && player->player_career != 2) {
        return;
    }
    if (player->sum_Potion >= 5) {
        return;
    }
    player->coin -= shop->potion_coin[index];
    get_potion(player, shop->potion[index]);
    shop->potion[index] = NULL;
}

void player_choose_discard_in_all_card(Player *player, int y, int mouse_x, int mouse_y, int *choosed) {
    int i;
    SDL_Rect rect = {200, 200 + y, 300, 450};
    for (i = 0; i < player->sum_deck_size; i++) {
        if (mouse_in_rect(rect, mouse_x, mouse_y)) {
            (*choosed) = i;
            return;
        }
        rect.x += rect.w * 1.5;
        if ((i + 1) % 4 == 0) {
            rect.x = 200;
            rect.y += rect.h * 1.5;
        }
    }
}

void player_choose_card_to_discard(SDL_Window *window, SDL_Renderer *renderer, Player *player) {
    int y = 0;
    int mouse_x, mouse_y, mousex, mousey;
    bool dragging = false;
    int quit = 1;
    SDL_Event event;
    Button choose_discard;
    initButton(&choose_discard, (Rect) {0.85, 0.85, 0.15, 0.08}, window, COLOR_GREY,
               COLOR_DARKGREY,
               COLOR_BLACK, "确定", "./res/ys_zt.ttf", 12);
    int choose_the_card = -1;
    while (quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    Button_destroy(&choose_discard);
                    game_Quit(window, renderer);
                    break;
                case SDL_WINDOWEVENT:
                    break;
                case SDL_MOUSEWHEEL:
                    if (event.wheel.y > 0) {
                        // 向上滚动，画面上移
                        y += 50;
                    } else if (event.wheel.y < 0) {
                        // 向下滚动，画面下移
                        y -= 50;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mousex, &mousey);
                    choose_discard.isHovered = isMouseInButton(event.motion.x, event.motion.y, &choose_discard);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    choose_discard.isPressed = isMouseInButton(event.motion.x, event.motion.y, &choose_discard);
                    dragging = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    dragging = false;
                    if (choose_the_card != -1 && choose_discard.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &choose_discard)) {
                        Button_destroy(&choose_discard);
                        delete_card_from_bag(player, choose_the_card);
                        return;
                    }
                    choose_discard.isPressed = false;
                    player_choose_discard_in_all_card(player, y, mousex, mousey, &choose_the_card);
                    break;
            }
            if (event.type == SDL_MOUSEMOTION && dragging) {
                // 更新矩形的位置，计算鼠标移动的距离
                int delta_y = event.motion.y - mouse_y;
                y += delta_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);  // 更新鼠标位置
            }
        }
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);
        SDL_RenderClear(renderer);
        print_everycard(renderer, player, y, mousex, mousey, choose_the_card);
        if (choose_the_card != -1) {
            drawButton(renderer, &choose_discard);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
}

void player_buy_discard(Player *player, Shop *shop, SDL_Window *window, SDL_Renderer *renderer) {
    if (discard_coin > player->coin) {
        return;
    }
    if (player->sum_deck_size <= 1) {
        return;
    }
    player->coin -= discard_coin;
    shop->discard_able = false;
    player_choose_card_to_discard(window, renderer, player);
    discard_coin += 25;
}

void player_buy_shop(Player *player, Shop *shop, int mouse_x, int mouse_y, SDL_Window *window, SDL_Renderer *renderer) {
    SDL_Rect rect = {400, 200, 200, 300};
    int i;
    for (i = 0; i < 7; i++) {
        if (shop->card[i] == NULL) {
            rect.x += rect.w * 1.25;
            if ((i + 1) % 5 == 0) {
                rect.x = 400;
                rect.y += rect.h * 1.25;
            }
            continue;
        }
        if (mouse_in_rect(rect, mouse_x, mouse_y)) {
            player_buy_card(player, shop, i);
            return;
        }
        rect.x += rect.w * 1.25;
        if ((i + 1) % 5 == 0) {
            rect.x = 400;
            rect.y += rect.h * 1.25;
        }
    }
    SDL_Rect coll_rect = {900, 550, 170, 150};
    for (i = 0; i < 3; i++) {
        if (shop->collection[i] == NULL) {
            coll_rect.x += coll_rect.w * 1.25;
            continue;
        }
        if (mouse_in_rect(coll_rect, mouse_x, mouse_y)) {
            player_buy_collection(player, shop, i);
            return;
        }
        coll_rect.x += coll_rect.w * 1.25;
    }
    SDL_Rect pot_rect = {900, 750, 170, 150};
    for (i = 0; i < 3; i++) {
        if (shop->potion[i] == NULL) {
            pot_rect.x += pot_rect.w * 1.25;
            continue;
        }
        if (mouse_in_rect(pot_rect, mouse_x, mouse_y)) {
            player_buy_potion(player, shop, i);
            return;
        }
        pot_rect.x += pot_rect.w * 1.25;
    }
    if (shop->discard_able) {
        SDL_Rect dis_rect = {1550, 550, 200, 300};
        if (mouse_in_rect(dis_rect, mouse_x, mouse_y)) {
            player_buy_discard(player, shop, window, renderer);
            return;
        }
    }

}

void enter_shop(SDL_Window *window, SDL_Renderer *renderer, Player *player, Shop *shop) {
    player->enter_allowance = false;
    SDL_Event event;
    TTF_Font *State_font = TTF_OpenFont("./res/ys_zt.ttf", 45);
    char *hp_text = malloc(20 * sizeof(char)), *coin_text = malloc(20 * sizeof(char));
    Button potion_using, potion_discard, leave;
    initButton(&potion_discard, (Rect) {0.5, 0.2, 0.05, 0.025}, window, COLOR_GREY, COLOR_GREYGREEN, COLOR_BLACK,
               "丢弃", "./res/ys_zt.ttf", 5);
    initButton(&potion_using, (Rect) {0.5, 0.2, 0.05, 0.025}, window, COLOR_GREY, COLOR_GREYGREEN, COLOR_LIGHT_RED,
               "使用", "./res/ys_zt.ttf", 5);
    initButton(&leave, (Rect) {0.05, 0.8, 0.1, 0.05}, window, COLOR_GREY, COLOR_GREYGREEN, COLOR_LIGHT_RED,
               "离开", "./res/ys_zt.ttf", 10);
//    printf("init button finish!\n");
    int mouse_x = 0, mouse_y = 0;
    int choose_potion = -1, press = 0, choice = -1;
    int step = 7;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    Button_destroy(&potion_using);
                    Button_destroy(&potion_discard);
                    Button_destroy(&leave);
//                    printf("button destroyed!\n");
                    free(hp_text);
                    free(coin_text);
//                    printf("text free!\n");
                    TTF_CloseFont(State_font);
//                    printf("font close!\n");
                    game_Quit(window, renderer);
                    break;
                case SDL_WINDOWEVENT:
                    break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    potion_using.isHovered = isMouseInButton(event.motion.x, event.motion.y, &potion_using);
                    potion_discard.isHovered = isMouseInButton(event.motion.x, event.motion.y, &potion_discard);
                    leave.isHovered = isMouseInButton(event.motion.x, event.motion.y, &leave);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    press = 1;
                    player_choose_potion(player, mouse_x, mouse_y, &choose_potion);
                    potion_using.isPressed = isMouseInButton(event.motion.x, event.motion.y, &potion_using);
                    potion_discard.isPressed = isMouseInButton(event.motion.x, event.motion.y, &potion_discard);
                    leave.isPressed = isMouseInButton(event.motion.x, event.motion.y, &leave);
                    break;
                case SDL_MOUSEBUTTONUP:
                    press = 0;
                    if (choose_potion != -1 && potion_discard.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &potion_discard)) {
                        discard_potion(player, choose_potion);
                        choose_potion = -1;
                    } else {
                        player_buy_shop(player, shop, mouse_x, mouse_y, window, renderer);
                    }
                    potion_discard.isPressed = false;
                    if (leave.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &leave)) {
                        quit = 1;
                    }
                    leave.isPressed = false;
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);
        SDL_RenderClear(renderer);
        //渲染事件
        draw_shop(renderer, player, shop, mouse_x, mouse_y, press);
        //渲染药水
        draw_Potion(renderer, player);
        if (choose_potion != -1) {
            printf("%d\n", choose_potion);
            print_potion_discribe(renderer, player, choose_potion, &potion_using, &potion_discard);
            drawButton(renderer, &potion_discard);
        }
        drawButton(renderer, &leave);
        //渲染生命值和金币
        sprintf(hp_text, "生命值: %d / %d", player->hp, player->maxhp);
        draw_text(renderer, State_font, hp_text, 50, 50, COLOR_LIGHT_RED);
        sprintf(coin_text, "金币: %d", player->coin);
        draw_text(renderer, State_font, coin_text, 800, 50, COLOR_DARK_YELLOW);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
}