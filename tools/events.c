//
// Created by 48811 on 25-1-24.
//

#include "events.h"

extern Events Safe_house, decitions[2], events_rewards, meeting;
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

void decitions_power(Player *player) {
    player_get_collection(player, 5, 5);
}

void decitions_wealth(Player *player) {
    player_get_collection(player, 5, 6);
}

void decitions_fight(Player *player) {
    player_get_collection(player, 5, 4);
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

    decitions[1].name = "门扉";
    decitions[1].discribe = "斗争的火焰在高塔之上燃烧\n"
                            "“勇敢的旅者，前进吧”，一个声音在门扉后回响\n"
                            "强大的敌人就在前方，也许我可以给你一些小小的帮助";
    decitions[1].choice_num = 2;
    decitions[1].choice_name[0] = "权力";
    decitions[1].choice_discribe[0] = "获得\"集权\"\n每进入一个战斗节点，造成伤害+5%";
    decitions[1].effect[0] = decitions_power;
    decitions[1].choice_end[0] = "绝对的集权，皇权至高无上，任何生命都要跪拜于王座之下";
    decitions[1].choice_name[1] = "财富";
    decitions[1].choice_discribe[1] = "获得\"寡头\"\n每进入一个非战斗节点，获得20金币";
    decitions[1].effect[1] = decitions_wealth;
    decitions[1].choice_end[1] = "为了利益无所不用其极，只要有合适的价格即使神明也可以被摆在货架上";

    if (main_collection[5][0].get || main_collection[5][1].get) {
        decitions[1].choice_num = 3;
        decitions[1].choice_name[2] = "反抗";
        decitions[1].choice_discribe[2] = "没有你，对我很重要，探索走向不同方向";
        decitions[1].effect[2] = decitions_fight;
        decitions[1].choice_end[2] = "获得“巴别塔”:团结起来，不惜一切。险路恶敌中出现其他敌人";
    }
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

void meeting1(Player *player) {
    player_get_collection(player, 5, 0);
}

void meeting2(Player *player) {
    player_get_collection(player, 5, 1);
}

void meeting3(Player *player) {
    return;
}

void Goop1(Player *player) {
    if (player->hp < 11) {
        player->enter_allowance = false;
        return;
    }
    player->coin += 75;
    player->hp -= 11;
}

void Goop2(Player *player) {
    player->coin -= generate_random(35, 75);
    if (player->coin < 0) {
        player->coin = 0;
    }
}

void money1(Player *player) {
    if (generate_random(1, 4) == 1) {
        main_event[2].choice_end[0] = "你一无所获";
    } else {
        player->coin += 10;
        main_event[2].choice_end[0] = "你获得了10块钱";
    }
}

void money2(Player *player) {
    if (player->coin < 50) {
        player->enter_allowance = false;
        return;
    }
    player->coin -= 50;
    int index = generate_random(1, 100);
    if (index <= 25) {
        main_event[2].choice_end[1] = "你一无所获";
    } else if (index <= 75) {
        player->coin += 50;
        main_event[2].choice_end[1] = "你获得了50块钱";
    } else {
        player->coin += 100;
        main_event[2].choice_end[1] = "你获得了100块钱";
    }
}

void money3(Player *player) {
    if (player->coin < 100) {
        player->enter_allowance = false;
        return;
    }
    player->coin -= 100;
    int index = generate_random(1, 100);
    if (index <= 50) {
        main_event[2].choice_end[2] = "你一无所获";
    } else if (index <= 75) {
        player->coin += 100;
        main_event[2].choice_end[2] = "你获得了100块钱";
    } else if (index <= 95) {
        player->coin += 150;
        main_event[2].choice_end[2] = "你获得了150块钱";
    } else if (index <= 99) {
        player->coin += 500;
        main_event[2].choice_end[2] = "你获得了500块钱";
    } else {
        player->coin += 1000;
        main_event[2].choice_end[2] = "你获得了1000块钱";
    }
}

void zl1(Player *player) {
    if (player->hp <= 15) {
        player->enter_allowance = false;
        return;
    }
    player->hp -= 15;
    player_get_collection(player, 5, 3);
}

void zl2(Player *player) {
    player_get_hp(player, 20);
    player_get_collection(player, 6, generate_random(0, main_collection_num[5] - 1));
}

extern Potion Nuclear_Bomb;

void village1(Player *player) {
    get_potion(player, &Nuclear_Bomb);
}

void village2(Player *player) {
    player->coin += 200;
}

void village3(Player *player) {
    player_get_hp(player, player->maxhp * 3 / 4);
}

void rsyy1(Player *player) {
    player->hp = player->maxhp;
}

void rsyy2(Player *player) {
    player->coin += 500;
}

void hsws1(Player *player) {
    for (int i = 0; i < 5; i++) {
        add_card_to_bag(player,
                        &main_card[player->player_career][generate_random(2, main_cardnum[player->player_career] - 1)]);
    }
}

void hsws2(Player *player) {
    int index_x = 0, index_y = 0;
    bool flag = true;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j < main_collection_num[i]; j++) {
            if (!main_collection[i][j].get) {
                flag = false;
                break;
            }
        }
    }
    if (!flag) {
        do {
            index_x = generate_random(0, 3);
            index_y = generate_random(0, main_collection_num[index_x] - 1);
        } while (main_collection[index_x][index_y].get);
    }
    player_get_collection(player, index_x, index_y);
    sprintf(main_event[6].choice_end[1], "获得藏品：%s", main_collection[index_x][index_y].name);
}

void hsws3(Player *player) {
    int index_x = 6, index_y = 0;
    do {
        index_y = generate_random(0, main_collection_num[index_x] - 1);
    } while (main_collection[index_x][index_y].get);
    player_get_collection(player, index_x, index_y);
    sprintf(main_event[6].choice_end[2], "获得藏品：%s", main_collection[index_x][index_y].name);
}

void init_events() {
    meeting = (Events) {"相遇",
                        "你偶遇了一个衣衫褴褛的人，他请求与你同行",
                        3, "同意", "拒绝", "无视", "", "...",
                        "...", "...", "",
                        "前方的未知还在等待你们，获得藏品“背叛”",
                        "你拒绝了他，获得藏品“仇恨”",
                        "你假装没听见他的请求，转身离去了"
                        "", "", meeting1, meeting2, meeting3, NULL
    };
    main_event[0] = (Events) {"翅膀雕像",
                              "在形状不同的巨石之间，你看见一尊做工精细的翅膀形状的蓝色雕像。\n你可以看见雕像的裂缝中有金币掉出来。或许里面还有更多……",
                              3, "祈祷", "摧毁", "离开", "", "从你的牌组中 随机 移除一张牌。获得 7 生命",
                              "获得 50-80 金币", "", "",
                              "你曾听人提起过一个崇拜巨大鸟类的邪教。当你跪下祷告的时候，你开始觉得有一些头晕……过了一会儿，你醒了过来，感觉脚步有点变轻了。",
                              "你使出浑身的力气开始砸雕像。很快它就彻底裂开，里面是一大堆金币。你把钱尽可能收集起来，重新上路。",
                              "这个雕像让你觉得有点不安。你决定不要去惊扰它，直接离开了。"
                              "", "", Wings_Statue_wish, Wings_Statue_destroy, Wings_Statue_leave, NULL
    };
    main_event[1] = (Events) {"黏液世界",
                              "你掉进了一个水坑里。可是坑里全是史莱姆黏液！\n爬出来后，你发现自己的金币似乎变少了。\n你回头一看，发现水坑里不但有你掉落的钱，还有不少其他不幸的冒险者们落下的金币。",
                              2, "收集金币", "放手吧", "", "", "获得 75 金币。失去 11 生命。",
                              "失去 35-75 金币。", "", "",
                              "在长时间与黏液接触而导致你的皮肤被烧走之前，你成功地捞出了不少金币。",
                              "你决定这样做不值得。",
                              ""
                              "", "", Goop1, Goop2, NULL, NULL
    };
    main_event[2] = (Events) {"投资",
                              "付出金钱，收获金钱",
                              3, "白嫖", "小赌", "土块", "", "付出0块，25%收获0块，75%收获10块",
                              "付出50块，25%收获0块，50%收获50块，25%收获100块",
                              "付出100块，50%收获0块，25%收获100块\n20%收获150块，4%收获500块，1%收获1000块", "",
                              "",
                              "",
                              ""
                              "", "", money1, money2, money3, NULL
    };
    main_event[3] = (Events) {"追猎",
                              "森林里传来了异响，你似乎成为了猎物",
                              2, "反抗", "逃跑", "", "", "失去15生命值，获得藏品“复仇者”",
                              "获得20生命值和一个负面藏品",
                              "", "",
                              "在密林之中似乎出现了一个诡异的人影\n在“险路恶敌”中将会出现不同的敌人",
                              "你拼命逃窜，森林中诡异的声音消失了",
                              ""
                              "", "", zl1, zl2, NULL, NULL
    };
    main_event[4] = (Events) {"村庄",
                              "你来到了一处不知名的村庄\n在说明来意后村民热情的招待了你，并表示愿意提供帮助",
                              3, "村民向你分享了曼哈顿计划", "村民给你了一个绿宝石", "村民给你分享了一个板烧鸡腿堡", "",
                              "获得1个核弹",
                              "获得200金币",
                              "回复生命值", "",
                              "尤里卡！",
                              "哼？",
                              "麦门"
                              "", "", village1, village2, village3, NULL
    };
    main_event[5] = (Events) {"人生意义",
                              "你看到一张4格漫画\n两只白色的精灵伫立在乱石与惊涛之畔\n探讨着此世的真理",
                              2, "去码头整点薯条", "去银行整点金条", "", "",
                              "生命值回满",
                              "获得500块",
                              "", "",
                              "",
                              "",
                              ""
                              "", "", rsyy1, rsyy2, NULL, NULL
    };
    main_event[6] = (Events) {"好诗歪诗",
                              "你来到一处断壁，墙上刻了1首诗\n“商鞅知马力，比干见人心。孙膑脚扑朔，左丘眼迷离。”",
                              3, "豪诗", "歪诗", "看不懂思密达", "",
                              "获得5张牌",
                              "获得随机1个价值3及以下藏品",
                              "获得一个奇怪的藏品", "",
                              "",
                              "",
                              ""
                              "", "", hsws1, hsws2, hsws3, NULL
    };
    main_event_num = 7;
}

void draw_events(SDL_Renderer *renderer, Events *events, int alpha) {
    char *title = events->name, *text = events->discribe;
    TTF_Font *title_font = TTF_OpenFont("./res/ys_zt.ttf", 45), *text_font = TTF_OpenFont("./res/ys_zt.ttf", 20);
    draw_text_alpha(renderer, title_font, title, 200, 500, COLOR_BLACK, alpha);
    draw_text_alpha(renderer, text_font, text, 200, 600, COLOR_BLACK, alpha);
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
//    printf("init button finish!\n");
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
//            printf("%d\n", choose_potion);
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
//            printf("%d\n", choose_potion);
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
//    printf("init button finish!\n");
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
//            printf("%d\n", choose_potion);
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
//            printf("%d\n", choose_potion);
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