//
// Created by 48811 on 25-1-24.
//

#include "events.h"

extern Events Safe_house, decitions[2], events_rewards;
extern Rewards rewards;
extern int main_event_num;
extern Events main_event[10];
extern int main_collection_num[6];
extern Collection main_collection[6][10];

void safe_house_sleep(Player *player) {
    player_get_hp(player, player->maxhp * 0.2);
}

void safe_house_recover(Player *player) {
    player->hp = player->maxhp;
    player->coin /= 2;
}

void safe_house_coin(Player *player) {
    if (generate_random(1, 1000) == 245) {
        player->coin += 999;
        Safe_house.choice_end[2] = "你发现了隐藏的巨款，真是意外之喜";
    } else {
        player->coin += generate_random(50, 200);
    }
}

void init_rewards() {
    events_rewards.name = "得偿所愿";
    events_rewards.discribe = "散落的珠宝，未知的财务，你索取，???回应";
    events_rewards.choice_num = 3;
    for (int i = 0; i < 3; i++) {
        int arr[5] = {30, 25, 20, 15, 10};
        int collection_get_x = generate_random_with_weighted(arr), collection_get_y = generate_random(0,
                                                                                                      main_collection_num[collection_get_x] -
                                                                                                      1);
        if (all_collections_had()) {
            collection_get_x = 0;
            collection_get_y = 0;
        } else {
            do {
                collection_get_x = generate_random_with_weighted(arr);
                collection_get_y = generate_random(0, main_collection_num[collection_get_x] - 1);
            } while (main_collection[collection_get_x][collection_get_y].get);
        }
        switch (collection_get_x) {
            case 0:
                events_rewards.choice_name[i] = "谢谢！";
                break;
            case 1:
                events_rewards.choice_name[i] = "拿走一件藏品";
                break;
            case 2:
                events_rewards.choice_name[i] = "许愿....";
                break;
            case 3:
                events_rewards.choice_name[i] = "我需要的是这个！";
                break;
            default:
                events_rewards.choice_name[i] = "难道这就是...";
        }
        events_rewards.choice_discribe[i] = malloc(200 * sizeof(char));
        sprintf(events_rewards.choice_discribe[i], "获得 “%s” : %s",
                main_collection[collection_get_x][collection_get_y].name,
                main_collection[collection_get_x][collection_get_y].discribe);
        events_rewards.choice_end[i] = "不知何人回应了你的愿望\n希望这个藏品能为你的旅途提供帮助";
        rewards.x[i] = collection_get_x;
        rewards.y[i] = collection_get_y;
//        events_rewards.effect[i] = player_get_collection(Player * player, collection_get_x, collection_get_y);
    }
    rewards.events = &events_rewards;
}

void init_safehouse() {
    Safe_house.name = "安全屋";
    Safe_house.discribe = "抓紧时间整理物资、放松身心、规划路线，新的挑战很快就到。";
    Safe_house.choice_num = 3;
    Safe_house.choice_name[0] = "好好休息";
    Safe_house.choice_discribe[0] = "回复20%生命值";
    Safe_house.effect[0] = safe_house_sleep;
    Safe_house.choice_end[0] = "你好好的睡了一觉";
    Safe_house.choice_name[1] = "进行治疗";
    Safe_house.choice_discribe[1] = "花费50%金币，恢复全部生命值";
    Safe_house.effect[1] = safe_house_recover;
    Safe_house.choice_end[1] = "花费了大量金币寻求了专业的治疗，你现在感觉良好";
    Safe_house.choice_name[2] = "获取补给";
    Safe_house.choice_discribe[2] = "获得一些金币";
    Safe_house.choice_end[2] = "你获得了一些补给";
    Safe_house.effect[2] = safe_house_coin;
}

void decitions_forward(Player *player) {
    return;
}

extern int endness;

void decitions_back(Player *player) {
    endness = 0;
    return;
}

void init_decition() {
    decitions[0].name = "迷雾";
    decitions[0].discribe = "迷雾渐起，前途未知，你将何去何从？\n选择下一层的方向";
    decitions[0].choice_num = 2;
    decitions[0].choice_name[0] = "前进";
    decitions[0].choice_discribe[0] = "走";
    decitions[0].effect[0] = decitions_forward;
    decitions[0].choice_end[0] = "你突破了迷雾，进入森林";
    decitions[0].choice_name[1] = "回头";
    decitions[0].choice_discribe[1] = "这个地方很诡异，你决定立刻离开";
    decitions[0].effect[1] = decitions_back;
    decitions[0].choice_end[1] = "你转身离去";

}

void Wings_Statue_wish(Player *player) {
    delete_card_from_bag(player, generate_random(0, player->sum_deck_size - 1));
}

void Wings_Statue_destroy(Player *player) {
    player->coin += generate_random(50, 80);
}

void Wings_Statue_leave(Player *player) {
    return;
}

void init_events() {
    main_event_num = 1;
    main_event[0] = (Events) {"翅膀雕像",
                              "在形状不同的巨石之间，你看见一尊做工精细的翅膀形状的蓝色雕像。\n你可以看见雕像的裂缝中有金币掉出来。或许里面还有更多……",
                              3, "祈祷", "摧毁", "离开", "", "从你的牌组中 随机 移除一张牌。获得 7 生命",
                              "获得 50-80 金币", "", "",
                              "你曾听人提起过一个崇拜巨大鸟类的邪教。当你跪下祷告的时候，你开始觉得有一些头晕……过了一会儿，你醒了过来，感觉脚步有点变轻了。",
                              "你使出浑身的力气开始砸雕像。很快它就彻底裂开，里面是一大堆金币。你把钱尽可能收集起来，重新上路。",
                              "这个雕像让你觉得有点不安。你决定不要去惊扰它，直接离开了。"
                              "", "", Wings_Statue_wish, Wings_Statue_destroy, Wings_Statue_leave, NULL
    };
}

void draw_events(SDL_Renderer *renderer, Events *events, int alpha) {
    char *title = events->name, *text = events->discribe;
    TTF_Font *title_font = TTF_OpenFont("./res/ys_zt.ttf", 45), *text_font = TTF_OpenFont("./res/ys_zt.ttf", 20);
    draw_text_alpha(renderer, title_font, title, 200, 500, COLOR_BLACK, alpha);
    draw_text_alpha(renderer, text_font, text, 200, 550, COLOR_BLACK, alpha);
    TTF_CloseFont(title_font);
    TTF_CloseFont(text_font);
}

void draw_choose(SDL_Renderer *renderer, Events *events, int mouse_x, int mouse_y, int press, int alpha) {
    int i = 0;
    char *title, *text;
    SDL_Rect rect = {1200, 300, 500, 150};
    TTF_Font *title_font = TTF_OpenFont("./res/ys_zt.ttf", 30), *text_font = TTF_OpenFont("./res/ys_zt.ttf", 16);
    for (i = 0; i < events->choice_num; i++) {
        title = events->choice_name[i];
        text = events->choice_discribe[i];
        if (mouse_in_rect(rect, mouse_x, mouse_y)) {
            if (press) {
                SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_Rect rect2 = {rect.x - 10, rect.y - 10, rect.w + 20, rect.h + 20};
            SDL_RenderFillRect(renderer, &rect2);
        }
        int a_cl = 255 - alpha;
        if (a_cl > 220) {
            a_cl = 220;
        }
        SDL_SetRenderDrawColor(renderer, a_cl, a_cl, a_cl, a_cl);
        SDL_RenderFillRect(renderer, &rect);
        draw_text_alpha(renderer, title_font, title, rect.x + 10, rect.y + 25,
                        COLOR_WHITE, alpha);
        draw_text_alpha(renderer, text_font, text, rect.x + 10, rect.y + 70,
                        COLOR_WHITE, alpha);
        rect.y += 200;
    }
}

void player_choose_choice(Events *events, Player *player, int mouse_x, int mouse_y, int *choice) {
    int i = 0;
    SDL_Rect rect = {1200, 300, 500, 150};
    for (i = 0; i < events->choice_num; i++) {
        if (mouse_in_rect(rect, mouse_x, mouse_y)) {
            player->enter_allowance = true;
            *choice = i;
            events->effect[i](player);
            break;
        }
        rect.y += 200;
    }
}

void player_choose_rewards(Rewards *rewardss, Player *player, int mouse_x, int mouse_y, int *choice) {
    int i = 0;
    Events *events = rewardss->events;
    SDL_Rect rect = {1200, 300, 500, 150};
    for (i = 0; i < events->choice_num; i++) {
        if (mouse_in_rect(rect, mouse_x, mouse_y)) {
            player->enter_allowance = true;
            *choice = i;
            player_get_collection(player, rewardss->x[i], rewardss->y[i]);
            break;
        }
        rect.y += 200;
    }
}

void draw_end(SDL_Renderer *renderer, Events *events, int choice, int alpha) {
    TTF_Font *title_font = TTF_OpenFont("./res/ys_zt.ttf", 45), *text_font = TTF_OpenFont("./res/ys_zt.ttf", 20);
    draw_text_alpha(renderer, title_font, events->choice_name[choice], 300, 500, COLOR_BLACK, alpha);
    draw_text_alpha(renderer, text_font, events->choice_end[choice], 300, 550, COLOR_BLACK, alpha);
    TTF_CloseFont(title_font);
    TTF_CloseFont(text_font);

}

void enter_events(SDL_Window *window, SDL_Renderer *renderer, Player *player, Events *events) {
    player->enter_allowance = false;
    SDL_Event event;
    TTF_Font *State_font = TTF_OpenFont("./res/ys_zt.ttf", 45);
    char *hp_text = malloc(20 * sizeof(char)), *coin_text = malloc(20 * sizeof(char));
    Button potion_using, potion_discard;
    initButton(&potion_discard, (Rect) {0.5, 0.2, 0.05, 0.025}, window, COLOR_GREY, COLOR_GREYGREEN, COLOR_BLACK,
               "丢弃", "./res/ys_zt.ttf", 5);
    initButton(&potion_using, (Rect) {0.5, 0.2, 0.05, 0.025}, window, COLOR_GREY, COLOR_GREYGREEN, COLOR_LIGHT_RED,
               "使用", "./res/ys_zt.ttf", 5);
    printf("init button finish!\n");
    int mouse_x = 0, mouse_y = 0;
    int choose_potion = -1, press = 0, choice = -1;
    int alpha = 0, step = 7;
    while (!player->enter_allowance) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    Button_destroy(&potion_using);
                    Button_destroy(&potion_discard);
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
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    press = 1;
                    player_choose_potion(player, mouse_x, mouse_y, &choose_potion);
                    potion_using.isPressed = isMouseInButton(event.motion.x, event.motion.y, &potion_using);
                    potion_discard.isPressed = isMouseInButton(event.motion.x, event.motion.y, &potion_discard);
                    break;
                case SDL_MOUSEBUTTONUP:
                    press = 0;
                    if (choose_potion != -1 && potion_discard.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &potion_discard)) {
                        discard_potion(player, choose_potion);
                        choose_potion = -1;
                    }
                    potion_discard.isPressed = false;
                    if (alpha >= 255) {
                        player_choose_choice(events, player, mouse_x, mouse_y, &choice);
                    }

                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);
        SDL_RenderClear(renderer);
        //渲染事件
        draw_events(renderer, events, alpha);
        draw_choose(renderer, events, mouse_x, mouse_y, press, alpha);
        //渲染药水
        draw_Potion(renderer, player);
        if (choose_potion != -1) {
            printf("%d\n", choose_potion);
            print_potion_discribe(renderer, player, choose_potion, &potion_using, &potion_discard);
            drawButton(renderer, &potion_discard);
        }
        //渲染生命值和金币
        sprintf(hp_text, "生命值: %d / %d", player->hp, player->maxhp);
        draw_text(renderer, State_font, hp_text, 50, 50, COLOR_LIGHT_RED);
        sprintf(coin_text, "金币: %d", player->coin);
        draw_text(renderer, State_font, coin_text, 800, 50, COLOR_DARK_YELLOW);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
        if (alpha < 255) {
            alpha += step;
            if (alpha > 255) {
                alpha = 255;
            }
        }
    }
    int quit = 1;
    alpha = 0;
    while (quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    Button_destroy(&potion_using);
                    Button_destroy(&potion_discard);
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
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    player_choose_potion(player, mouse_x, mouse_y, &choose_potion);
                    potion_using.isPressed = isMouseInButton(event.motion.x, event.motion.y, &potion_using);
                    potion_discard.isPressed = isMouseInButton(event.motion.x, event.motion.y, &potion_discard);
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (choose_potion != -1 && potion_discard.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &potion_discard)) {
                        discard_potion(player, choose_potion);
                        choose_potion = -1;
                    } else {
                        if (alpha == 255) {
                            quit = 0;
                        }
                    }
                    potion_discard.isPressed = false;
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);
        SDL_RenderClear(renderer);
        //渲染事件
        draw_end(renderer, events, choice, alpha);
        //渲染药水
        draw_Potion(renderer, player);
        if (choose_potion != -1) {
            printf("%d\n", choose_potion);
            print_potion_discribe(renderer, player, choose_potion, &potion_using, &potion_discard);
            drawButton(renderer, &potion_discard);
        }
        //渲染生命值和金币
        sprintf(hp_text, "生命值: %d / %d", player->hp, player->maxhp);
        draw_text(renderer, State_font, hp_text, 50, 50, COLOR_LIGHT_RED);
        sprintf(coin_text, "金币: %d", player->coin);
        draw_text(renderer, State_font, coin_text, 800, 50, COLOR_DARK_YELLOW);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
        if (alpha < 255) {
            alpha += step;
            if (alpha > 255) {
                alpha = 255;
            }
        }
    }
}

void enter_rewards(SDL_Window *window, SDL_Renderer *renderer, Player *player, Rewards *rewardss) {
    Events *events = rewardss->events;
    player->enter_allowance = false;
    SDL_Event event;
    TTF_Font *State_font = TTF_OpenFont("./res/ys_zt.ttf", 45);
    char *hp_text = malloc(20 * sizeof(char)), *coin_text = malloc(20 * sizeof(char));
    Button potion_using, potion_discard;
    initButton(&potion_discard, (Rect) {0.5, 0.2, 0.05, 0.025}, window, COLOR_GREY, COLOR_GREYGREEN, COLOR_BLACK,
               "丢弃", "./res/ys_zt.ttf", 5);
    initButton(&potion_using, (Rect) {0.5, 0.2, 0.05, 0.025}, window, COLOR_GREY, COLOR_GREYGREEN, COLOR_LIGHT_RED,
               "使用", "./res/ys_zt.ttf", 5);
    printf("init button finish!\n");
    int mouse_x = 0, mouse_y = 0;
    int choose_potion = -1, press = 0, choice = -1;
    int alpha = 0, step = 7;
    while (!player->enter_allowance) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    Button_destroy(&potion_using);
                    Button_destroy(&potion_discard);
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
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    press = 1;
                    player_choose_potion(player, mouse_x, mouse_y, &choose_potion);
                    potion_using.isPressed = isMouseInButton(event.motion.x, event.motion.y, &potion_using);
                    potion_discard.isPressed = isMouseInButton(event.motion.x, event.motion.y, &potion_discard);
                    break;
                case SDL_MOUSEBUTTONUP:
                    press = 0;
                    if (choose_potion != -1 && potion_discard.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &potion_discard)) {
                        discard_potion(player, choose_potion);
                        choose_potion = -1;
                    }
                    potion_discard.isPressed = false;
                    if (alpha >= 255) {
                        player_choose_rewards(rewardss, player, mouse_x, mouse_y, &choice);
                    }

                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);
        SDL_RenderClear(renderer);
        //渲染事件
        draw_events(renderer, events, alpha);
        draw_choose(renderer, events, mouse_x, mouse_y, press, alpha);
        //渲染药水
        draw_Potion(renderer, player);
        if (choose_potion != -1) {
            printf("%d\n", choose_potion);
            print_potion_discribe(renderer, player, choose_potion, &potion_using, &potion_discard);
            drawButton(renderer, &potion_discard);
        }
        //渲染生命值和金币
        sprintf(hp_text, "生命值: %d / %d", player->hp, player->maxhp);
        draw_text(renderer, State_font, hp_text, 50, 50, COLOR_LIGHT_RED);
        sprintf(coin_text, "金币: %d", player->coin);
        draw_text(renderer, State_font, coin_text, 800, 50, COLOR_DARK_YELLOW);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
        if (alpha < 255) {
            alpha += step;
            if (alpha > 255) {
                alpha = 255;
            }
        }
    }
    int quit = 1;
    alpha = 0;
    while (quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    Button_destroy(&potion_using);
                    Button_destroy(&potion_discard);
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
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    player_choose_potion(player, mouse_x, mouse_y, &choose_potion);
                    potion_using.isPressed = isMouseInButton(event.motion.x, event.motion.y, &potion_using);
                    potion_discard.isPressed = isMouseInButton(event.motion.x, event.motion.y, &potion_discard);
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (choose_potion != -1 && potion_discard.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &potion_discard)) {
                        discard_potion(player, choose_potion);
                        choose_potion = -1;
                    } else {
                        if (alpha == 255) {
                            quit = 0;
                        }
                    }
                    potion_discard.isPressed = false;
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);
        SDL_RenderClear(renderer);
        //渲染事件
        draw_end(renderer, events, choice, alpha);
        //渲染药水
        draw_Potion(renderer, player);
        if (choose_potion != -1) {
            printf("%d\n", choose_potion);
            print_potion_discribe(renderer, player, choose_potion, &potion_using, &potion_discard);
            drawButton(renderer, &potion_discard);
        }
        //渲染生命值和金币
        sprintf(hp_text, "生命值: %d / %d", player->hp, player->maxhp);
        draw_text(renderer, State_font, hp_text, 50, 50, COLOR_LIGHT_RED);
        sprintf(coin_text, "金币: %d", player->coin);
        draw_text(renderer, State_font, coin_text, 800, 50, COLOR_DARK_YELLOW);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
        if (alpha < 255) {
            alpha += step;
            if (alpha > 255) {
                alpha = 255;
            }
        }
    }
}