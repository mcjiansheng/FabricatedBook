#include <stdio.h>
#include "tools/videos.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "tools/button.h"
#include "tools/Saves.h"
#include "tools/Color.h"
#include "tools/gamecreater.h"
#include "tools/card.h"
#include "tools/map.h"
#include "tools/fight.h"
#include "tools/events.h"

#define TTF_FILE "./res/ys_zt.ttf"
#undef main

Layer layers[MAX_LAYERS];
int seed;
int main_Enemynum;
Enemy main_enemy[3];
Card main_card[4][50];
int main_potion_num;
Potion main_potion[20];
int main_cardnum[4];
int windowWidth = 1920;
int windowHeight = 1080;
struct SUMMARY summary = {0, 0};
int round_times;
int main_collection_num[6];
Collection main_collection[6][10];
int Enemy_num_in_map[7][2];
Enemy Enemy_in_map[7][2][10];
int fight_in_map[7][2];
Fight fight_map[7][2][10];
PlayerInfo playerInfo;
Events Safe_house, decitions[2], rewards;
int main_event_num;
Events main_event[10];
Fight boss[3][3];

PPT first_floor, second_floor[2], third_floor[2], forth_floor[2], fifth_floor[2], small_path, sixth_floor[2];

void game_Quit(SDL_Window *window, SDL_Renderer *renderer) {
    free_picture_node();
    for (int i = 0; i < 6; i++) {
        free_layer(&layers[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
    savePlayerInfo(&playerInfo);
    exit(0);
}

void game_Welcoming(SDL_Window *window, SDL_Renderer *text_renderer, SDL_Texture *background_texture);

void game_start(SDL_Window *window, SDL_Renderer *renderer);

void game_main(SDL_Window *window, SDL_Renderer *renderer);


int main(int argc, char *argv[]) {

//    PleyInfo_reset();
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    TTF_Font *font_button;
    // 初始化 SDL
    // 创建可调整大小的窗口
    window = SDL_CreateWindow("The Explorer and Fabricated Book", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              windowWidth,
                              windowHeight,
                              SDL_WINDOW_SHOWN);
    // 创建渲染器
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface *icon = IMG_Load("./img/image.jpg");
    SDL_Texture *back_texture = IMG_LoadTexture(renderer, "./img/background.png");
    if (back_texture == NULL) {
        printf("background error\n");
    }
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);
    font_button = TTF_OpenFont(TTF_FILE, 16);
    int quit = 0;
    // 初始化 UI 元素
    Button But_Start, But_intr, But_Setting, But_exit, game_title;
    initButton(&But_Start, (Rect) {0.12, 0.45, 0.2, 0.1}, window, COLOR_BLACK,
               COLOR_GREY,
               COLOR_GREYRED, "开始游戏", TTF_FILE, 16);
    initButton(&But_intr, (Rect) {0.12, 0.56, 0.2, 0.1}, window, COLOR_BLACK,
               COLOR_GREY,
               COLOR_GREYGREEN, "游戏介绍", TTF_FILE, 16);
    initButton(&But_Setting, (Rect) {0.12, 0.67, 0.2, 0.1}, window, COLOR_BLACK,
               COLOR_GREY,
               COLOR_GREYGREEN, "设置", TTF_FILE, 16);
    initButton(&But_exit, (Rect) {0.12, 0.78, 0.2, 0.1}, window, COLOR_BLACK,
               COLOR_GREY,
               COLOR_DARKGREY, "游戏退出", TTF_FILE, 16);
//    uiElement.rect.x = windowWidth / 5;
//    uiElement.rect.y = windowHeight / 4;
//    uiElement.rect.w = windowWidth / 2;
//    uiElement.rect.h = windowHeight / 2;
    playerInfo = loadPlayerInfo();
    if (!playerInfo.firstTime) {
        printf("first time!\n");
        game_Welcoming(window, renderer, back_texture);
        playerInfo.firstTime = 1;
        savePlayerInfo(&playerInfo);
    }
    SDL_RenderCopy(renderer, back_texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    updateButton(&But_Start, window);
    updateButton(&But_intr, window);
    updateButton(&But_Setting, window);
    updateButton(&But_exit, window);
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
//                    printf("quit!\n");
                    game_Quit(window, renderer);
                    quit = 1;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
                        updateButton(&But_Start, window);
                        updateButton(&But_intr, window);
                        updateButton(&But_Setting, window);
                        updateButton(&But_exit, window);
                        updateButton(&game_title, window);
                    }
                    break;
                case SDL_MOUSEMOTION:
                    But_Start.isHovered = isMouseInButton(event.motion.x, event.motion.y, &But_Start);
                    But_intr.isHovered = isMouseInButton(event.motion.x, event.motion.y, &But_intr);
                    But_Setting.isHovered = isMouseInButton(event.motion.x, event.motion.y, &But_Setting);
                    But_exit.isHovered = isMouseInButton(event.motion.x, event.motion.y, &But_exit);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    But_Start.isPressed = isMouseInButton(event.motion.x, event.motion.y, &But_Start);
                    But_intr.isPressed = isMouseInButton(event.motion.x, event.motion.y, &But_intr);
                    But_Setting.isPressed = isMouseInButton(event.motion.x, event.motion.y, &But_Setting);
                    But_exit.isPressed = isMouseInButton(event.motion.x, event.motion.y, &But_exit);
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (But_Start.isPressed && isMouseInButton(event.button.x, event.button.y, &But_Start)) {
                        // 按钮被点击，执行相应操作
                        printf("But_Start Clicked!\n");
                        game_start(window, renderer);
                    }
                    But_Start.isPressed = false;
                    if (But_intr.isPressed && isMouseInButton(event.button.x, event.button.y, &But_intr)) {
                        // 按钮被点击，执行相应操作
                        printf("But_intr Clicked!\n");
                    }
                    But_intr.isPressed = false;
                    if (But_Setting.isPressed && isMouseInButton(event.button.x, event.button.y, &But_Setting)) {
                        // 按钮被点击，执行相应操作
                        printf("But_Setting Clicked!\n");
                    }
                    But_Setting.isPressed = false;
                    if (But_exit.isPressed && isMouseInButton(event.button.x, event.button.y, &But_exit)) {
                        // 按钮被点击，执行相应操作
                        game_Quit(window, renderer);
                        TTF_CloseFont(font_button);
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        TTF_Quit();
                        printf("But_exit Clicked!\n");
                        exit(0);
                    }
                    But_exit.isPressed = false;
                    break;
            }
        }


        // 清除渲染器
//        SDL_RenderPresent(renderer);
//        SDL_SetRenderDrawColor(renderer, 170, 170, 170, 170);
        SDL_RenderClear(renderer);

        // 绘制 UI 元素
        SDL_RenderCopy(renderer, back_texture, NULL, NULL);
        drawButton(renderer, &But_Start);
        drawButton(renderer, &But_intr);
        drawButton(renderer, &But_Setting);
        drawButton(renderer, &But_exit);

        // 显示渲染结果
        SDL_RenderPresent(renderer);
        SDL_Delay(5);
    }

    // 销毁渲染器和窗口，退出 SDL
    TTF_CloseFont(font_button);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
    return 0;
}

extern SDL_Texture *node_texture[10];

Node *last_node = NULL;

void game_main(SDL_Window *window, SDL_Renderer *renderer) {
    srand(time(NULL));
    seed = rand();
    Player *player = init_player(characters[selectedCharacter].hp, selectedCharacter);
    init_collection();
//    printf("init player finish!\n");
    init_card();
//    printf("init card finish!\n");
    init_potion();
//    printf("init potion finish!\n");
    last_node = NULL;
    if (playerInfo.reward) {
        game_choose_reward(renderer, window, player);
    }
//    playerInfo.reward = 0;
    push_beginning_cards(player);
//    printf("init beginning_cards finish!\n");
    init_every_layer();
//    printf("init layer finish!\n");
    init_ppt();
//    printf("init ppt finish!\n");
    event_init();
    init_events();
//    printf("init event finish!\n");
    init_enemy(renderer);
//    printf("init enemy finish!\n");
    PPT *now_ppt = &first_floor;
//    init_map(now_ppt);
    cutscene_animation(window, renderer, now_ppt);
    init_picture_node(renderer);
//    printf("init every finish!\n");
    int x = 0;
    int mouse_x, mouse_y;
    bool dragging = false;
    int quit = 1, choose_potion = -1;
    SDL_Event event;
    TTF_Font *State_font = TTF_OpenFont("./res/ys_zt.ttf", 45);
    char *hp_text = malloc(20 * sizeof(char)), *coin_text = malloc(20 * sizeof(char));
    int step = 0;
    init_map_printer(now_ppt->layer);
    Button map_reset, show_card, show_collection;
    initButton(&map_reset, (Rect) {0.05, 0.85, 0.15, 0.08}, window, COLOR_GREY,
               COLOR_DARKGREY,
               COLOR_BLACK, "复原", TTF_FILE, 12);
    initButton(&show_card, (Rect) {0.80, 0.05, 0.15, 0.08}, window, COLOR_GREY,
               COLOR_GREYGREEN,
               COLOR_LIGHT_RED, "卡牌", TTF_FILE, 12);
    initButton(&show_collection, (Rect) {0.80, 0.15, 0.15, 0.08}, window, COLOR_GREY,
               COLOR_GREYGREEN,
               COLOR_LIGHT_RED, "藏品", TTF_FILE, 12);
    Button potion_using, potion_discard;
    initButton(&potion_using, (Rect) {0.5, 0.2, 0.05, 0.025}, window, COLOR_GREY, COLOR_GREYGREEN, COLOR_LIGHT_RED,
               "使用", "./res/ys_zt.ttf", 5);
    initButton(&potion_discard, (Rect) {0.5, 0.2, 0.05, 0.025}, window, COLOR_GREY, COLOR_GREYGREEN, COLOR_BLACK,
               "丢弃", "./res/ys_zt.ttf", 5);
    printf("init button finish!\n");
    while (quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    Button_destroy(&map_reset);
                    Button_destroy(&show_card);
                    Button_destroy(&potion_using);
                    Button_destroy(&potion_discard);
                    Button_destroy(&show_collection);
                    free(hp_text);
                    free(coin_text);
                    TTF_CloseFont(State_font);
                    game_Quit(window, renderer);
                    break;
                case SDL_WINDOWEVENT:
                    break;
                case SDL_MOUSEMOTION:
                    map_reset.isHovered = isMouseInButton(event.motion.x, event.motion.y, &map_reset);
                    show_card.isHovered = isMouseInButton(event.motion.x, event.motion.y, &show_card);
                    potion_using.isHovered = isMouseInButton(event.motion.x, event.motion.y, &potion_using);
                    potion_discard.isHovered = isMouseInButton(event.motion.x, event.motion.y, &potion_discard);
                    show_collection.isHovered = isMouseInButton(event.motion.x, event.motion.y, &show_collection);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    player_choose_potion(player, mouse_x, mouse_y, &choose_potion);
                    map_reset.isPressed = isMouseInButton(event.motion.x, event.motion.y, &map_reset);
                    show_card.isPressed = isMouseInButton(event.motion.x, event.motion.y, &show_card);
                    potion_using.isPressed = isMouseInButton(event.motion.x, event.motion.y, &potion_using);
                    potion_discard.isPressed = isMouseInButton(event.motion.x, event.motion.y, &potion_discard);
                    show_collection.isPressed = isMouseInButton(event.motion.x, event.motion.y, &show_collection);
                    dragging = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if ((x > 1000 || x < -1000) && map_reset.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &map_reset)) {
                        x = 0;
                    }
                    map_reset.isPressed = false;
                    dragging = false;
                    if (show_card.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &show_card)) {
                        show_all_card(window, renderer, player);
                    }
                    show_card.isPressed = false;
                    if (show_collection.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &show_collection)) {
                        show_all_collection(window, renderer, player);
                    }
                    show_collection.isPressed = false;
                    check_choose_nodes(window, renderer, last_node, now_ppt->layer, mouse_x, mouse_y, x, player);
                    if (now_ppt->layer->tail == last_node) {
                        now_ppt = now_ppt->next_PPT;
                        last_node = NULL;
                        init_map_printer(now_ppt->layer);
                        cutscene_animation(window, renderer, now_ppt);
                        printf("next floor!\n");
                    }
                    if (player->hp <= 0) {
                        return;
                    }
                    if (choose_potion != -1 && potion_discard.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &potion_discard)) {
                        discard_potion(player, choose_potion);
                        choose_potion = -1;
                    }
                    potion_discard.isPressed = false;
                    break;
            }
            if (event.type == SDL_MOUSEMOTION && dragging) {
                // 更新矩形的位置，计算鼠标移动的距离
                int delta_x = event.motion.x - mouse_x;
                x += delta_x;
                SDL_GetMouseState(&mouse_x, &mouse_y);  // 更新鼠标位置
            }
        }
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);
        SDL_RenderClear(renderer);
        draw_Potion(renderer, player);
        if (choose_potion != -1) {
            print_potion_discribe(renderer, player, choose_potion, &potion_using, &potion_discard);
            drawButton(renderer, &potion_discard);
        }
        printf("draw potion!\n");
//        sprintf(show_collection.text, "藏品:%d", player->sum_collection);
//        sprintf(show_card.text, "卡牌:%d", player->sum_deck_size);
        printf("update button text\n");
        //渲染按钮
        if (x > 1000 || x < -1000) {
            drawButton(renderer, &map_reset);
        }
        drawButton(renderer, &show_card);
        drawButton(renderer, &show_collection);
        printf("draw button!\n");
        //渲染当前节点和可选下一步的节点
        print_nodes(renderer, last_node, now_ppt->layer, x);
        //渲染地图
        print_map(window, renderer, now_ppt->layer, x);
        //渲染生命值和金币
        sprintf(hp_text, "生命值: %d / %d", player->hp, player->maxhp);
        draw_text(renderer, State_font, hp_text, 50, 50, COLOR_LIGHT_RED);
        sprintf(coin_text, "金币: %d", player->coin);
        draw_text(renderer, State_font, coin_text, 800, 50, COLOR_DARK_YELLOW);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
    Button_destroy(&map_reset);
    Button_destroy(&show_card);
    free(hp_text);
    free(coin_text);
    TTF_CloseFont(State_font);
}

void game_start(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);
    SDL_RenderClear(renderer);
    init_characters(renderer, playerInfo);
    render_character_selection(renderer, windowWidth, windowHeight);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    SDL_Event event;
    Button game_continue, game_back;
    selectedCharacter = -1;
    initButton(&game_continue, (Rect) {0.75, 0.75, 0.15, 0.08}, window, COLOR_GREY,
               COLOR_GREYGREEN,
               COLOR_LIGHT_RED, "开始游戏", TTF_FILE, 12);
    initButton(&game_back, (Rect) {0.05, 0.75, 0.15, 0.08}, window, COLOR_GREY,
               COLOR_DARKGREY,
               COLOR_BLACK, "返回", TTF_FILE, 12);
    while (1) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
//                    printf("quit!\n");
                    Button_destroy(&game_continue);
                    Button_destroy(&game_back);
                    game_Quit(window, renderer);
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
                        updateButton(&game_continue, window);
                        updateButton(&game_back, window);
                    }
                    break;
                case SDL_MOUSEMOTION:
                    game_continue.isHovered = isMouseInButton(event.motion.x, event.motion.y, &game_continue);
                    game_back.isHovered = isMouseInButton(event.motion.x, event.motion.y, &game_back);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    game_continue.isPressed = isMouseInButton(event.motion.x, event.motion.y, &game_continue);
                    game_back.isPressed = isMouseInButton(event.motion.x, event.motion.y, &game_back);
                    select_character(event.button.x, event.button.y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (selectedCharacter != -1 && game_continue.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &game_continue)) {
                        printf("game continue Clicked!\n");
                        Button_destroy(&game_continue);
                        Button_destroy(&game_back);
                        game_main(window, renderer);
                        return;
                    }
                    game_continue.isPressed = false;
                    if (game_back.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &game_back)) {
                        printf("game back Clicked!\n");
                        Button_destroy(&game_continue);
                        Button_destroy(&game_back);
                        return;
                    }
                    game_back.isPressed = false;
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);
        SDL_RenderClear(renderer);
        if (selectedCharacter != -1) {
            drawButton(renderer, &game_continue);
        }
        drawButton(renderer, &game_back);
        render_character_selection(renderer, windowWidth, windowHeight);
        render_selected_character(renderer, windowWidth, windowHeight);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);


    }
}

void game_Welcoming(SDL_Window *window, SDL_Renderer *text_renderer, SDL_Texture *background_texture) {
    char *sen[14] = {
            "所谓末法时代，神明不出，奇异不显",
            "某一脉神秘传承的末代传人，你被卷入社会上众多的血汗熔炉之中",
            "用时间与健康聊以谋生",
            "偶尔在先祖遗留的典籍之中追忆那个剑与魔法的幻想世界",
            "-真渴望亲眼去见证那传说之中的史诗",
            "-如果可以呢",
            "一道声音从身后响起",
            "-你是谁",
            "对于沉溺于神秘世界多年的你而言，这种情况熟悉而陌生",
            "你早已幻想多次，却从未想过它真的发生在你身边",
            "-一个讲故事的人",
            "-我愿一试",
            "-好，故事即将开始",
            "一个俗套的异世界勇者击败魔王的故事缓缓展开，或许你可以让它有所不同。",
    };
    SDL_Color sen_color[14] = {COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_LIGHT_GREEN, COLOR_LIGHT_RED,
                               COLOR_WHITE,
                               COLOR_LIGHT_GREEN, COLOR_WHITE, COLOR_WHITE, COLOR_LIGHT_RED, COLOR_LIGHT_GREEN,
                               COLOR_LIGHT_RED, COLOR_WHITE};
    int quit = 0;
    SDL_Event event;
    int sentenceIndex = 0;
    TTF_Font *textfont = TTF_OpenFont("./res/ys_zt.ttf", 20 + (windowWidth - 800) / 100);
    if (text_renderer == NULL) {
        printf("text_renderer is null!\n");
        return;
    }
    while (!quit) {
        SDL_Surface *textSurface = TTF_RenderUTF8_Blended(textfont, sen[sentenceIndex],
                                                          sen_color[sentenceIndex]);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(text_renderer, textSurface);
        if (textSurface == NULL) {
            printf("textSurface is NULL\n");
        }
        SDL_SetRenderDrawColor(text_renderer, 0, 0, 0, 255);
        SDL_Rect rect_title;
        SDL_QueryTexture(texture, NULL, NULL, &rect_title.w, &rect_title.h);
        rect_title.x = (windowWidth - rect_title.w) / 2;
        rect_title.y = (windowHeight - rect_title.h) / 2;
        SDL_RenderCopy(text_renderer, texture, NULL, &rect_title);

        SDL_RenderPresent(text_renderer);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(texture);
        SDL_RenderClear(text_renderer);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
//                    printf("quit!\n");
                    TTF_CloseFont(textfont);
                    game_Quit(window, text_renderer);
                    exit(0);
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
                        TTF_CloseFont(textfont);
                        textfont = TTF_OpenFont("./res/ys_zt.ttf", 20 + (windowWidth - 800) / 100);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
//                    printf("mouse click! %d\n", sentenceIndex);
                    sentenceIndex++;
                    break;
            }
        }
        if (sentenceIndex >= 14) {
            break;
        }
        SDL_Delay(5);
    }
    SDL_RenderClear(text_renderer);
    SDL_Rect rect;
    const int fadeSpeed = 3;
    SDL_QueryTexture(background_texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = 0;
    rect.y = 0;
    int alpha = 0;  // 初始透明度为 0
    int step = 5;  // 透明度增加的步长
    while (alpha < 255) {
        SDL_RenderClear(text_renderer);
        SDL_SetTextureAlphaMod(background_texture, alpha);
        SDL_RenderCopy(text_renderer, background_texture, NULL, &rect);
        SDL_RenderPresent(text_renderer);
        alpha += step;
        SDL_Delay(50);
    }
    TTF_CloseFont(textfont);
}