//
// Created by 48811 on 25-1-12.
//

#include "gamecreater.h"
#include "Color.h"
#include "Saves.h"

#define CHARACTER_COUNT 3
#define CHARACTER_WIDTH 200
#define CHARACTER_HEIGHT 260
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50

int max(int x, int y) {
    return x > y ? x : y;
}

int min(int x, int y) {
    return x < y ? x : y;
}

// 角色数据
Character characters[CHARACTER_COUNT];
int selectedCharacter = -1;  // 默认未选择角色

// 加载角色图片
void load_texture(SDL_Renderer *renderer, Character *character, const char *imagePath) {
    SDL_Surface *surface = IMG_Load(imagePath);
    if (surface == NULL) {
        printf("Error loading image: %s\n", SDL_GetError());
    }
    character->image = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void init_characters(SDL_Renderer *renderer, PlayerInfo info) {
    // 初始化角色数据
    characters[0] = (Character) {"战士", "战斗胜利回复6-12点生命值", NULL, 1};
    characters[1] = (Character) {"法师", "奇数回合行动点+1，上一回合未使用的行动点保留到下一回合", NULL, 0};
    characters[2] = (Character) {"巫师", "药水携带量增加，战斗胜利获得药水概率增加", NULL, 0};
    // 加载角色立绘和锁图标
    characters[0].color = COLOR_DARKGREY;
    characters[1].color = COLOR_LIGHT_RED;
    characters[2].color = COLOR_GREYGREEN;
    characters[0].hp = 80;
    characters[1].hp = 70;
    characters[2].hp = 70;
    load_texture(renderer, &characters[0], "./img/Character_Selection_Warrior.png");
    load_texture(renderer, &characters[1], "./img/Character_Selection_Mage.png");
    load_texture(renderer, &characters[2], "./img/Character_Selection_Witch.png");
    for (int i = 0; i < 3; i++) {
        characters[i].unlocked = info.Character_locked[i];
    }
}

void render_character_selection(SDL_Renderer *renderer, int windowsx, int windowsy) {
    int offsetX = windowsx / 2, offsetY = windowsy / 3, picw = CHARACTER_WIDTH + (windowsx - 1280) * 0.1, pich =
            picw * 1.5;
    int kuan = picw / 2;
    offsetX -= picw * 2;
    offsetY -= pich * 0.5;
    for (int i = 0; i < CHARACTER_COUNT; i++) {
        SDL_Rect dstRect = {offsetX + i * (picw + kuan), offsetY,
                            picw,
                            pich};
        characters[i].rect = dstRect;
        SDL_RenderCopy(renderer, characters[i].image, NULL, &dstRect);
        // 渲染角色立绘
        if (!characters[i].unlocked) {
            TTF_Font *font_lock = TTF_OpenFont("./res/ys_zt.ttf", (windowsy - 600) / 20 + 16);
            SDL_Color Color_lock = COLOR_LIGHT_RED;
            SDL_Surface *surface_lock = TTF_RenderUTF8_Blended(font_lock, "未解锁", Color_lock);
            SDL_Texture *texture_lock = SDL_CreateTextureFromSurface(renderer, surface_lock);

            SDL_Rect rect_lock = {.x = dstRect.x + dstRect.w / 2, .y = dstRect.y + dstRect.h / 2};
            SDL_QueryTexture(texture_lock, NULL, NULL, &rect_lock.w, &rect_lock.h);
            rect_lock.x -= rect_lock.w / 2;
            rect_lock.y -= rect_lock.h / 2;

            SDL_RenderCopy(renderer, texture_lock, NULL, &rect_lock);
//            SDL_RenderPresent(renderer);
            SDL_DestroyTexture(texture_lock);
            SDL_FreeSurface(surface_lock);
        }
    }
}

void select_character(int mouseX, int mouseY) {
    for (int i = 0; i < CHARACTER_COUNT; i++) {
        if (mouseX >= characters[i].rect.x && mouseX <= characters[i].rect.x + characters[i].rect.w &&
            mouseY >= characters[i].rect.y && mouseY <= characters[i].rect.y + characters[i].rect.h) {
            if (characters[i].unlocked) {
                selectedCharacter = i;  // 选择角色
                printf("Selected %d\n", i);
            }
            break;
        }
    }
}

void render_selected_character(SDL_Renderer *renderer, int windowsx, int windowsy) {
    if (selectedCharacter != -1) {
//        SDL_Rect textRect = {200, 300, BUTTON_WIDTH, BUTTON_HEIGHT};
//        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // 设置文本框背景颜色
//        SDL_RenderFillRect(renderer, &textRect);

        TTF_Font *font_skill = TTF_OpenFont("./res/ys_zt.ttf", (windowsy - 600) / 20 + 16),
                *font_name = TTF_OpenFont("./res/ys_zt.ttf", (windowsy - 600) / 15 + 20);
        SDL_Color Color_skill = COLOR_BLACK, Color_name = characters[selectedCharacter].color;
        SDL_Surface *surface_skill = TTF_RenderUTF8_Blended(font_skill, characters[selectedCharacter].skill,
                                                            Color_skill);
        SDL_Texture *texture_skill = SDL_CreateTextureFromSurface(renderer, surface_skill);
        SDL_Surface *surface_name = TTF_RenderUTF8_Blended(font_name, characters[selectedCharacter].name, Color_name);
        SDL_Texture *texture_name = SDL_CreateTextureFromSurface(renderer, surface_name);
        SDL_Rect rect_skill = {.x = windowsx * 0.5, .y = windowsy * 0.7};
        SDL_QueryTexture(texture_skill, NULL, NULL, &rect_skill.w, &rect_skill.h);
        SDL_Rect rect_name = {.x =rect_skill.x, .y=rect_skill.y - 2 * rect_skill.h};
        rect_skill.x -= rect_skill.w / 2;
        rect_skill.y -= rect_skill.h / 2;
        SDL_QueryTexture(texture_name, NULL, NULL, &rect_name.w, &rect_name.h);
        rect_name.x -= rect_name.w / 2;
        rect_name.y -= rect_name.h / 2;
        SDL_RenderCopy(renderer, texture_skill, NULL, &rect_skill);
        SDL_RenderCopy(renderer, texture_name, NULL, &rect_name);
//        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(texture_skill);
        SDL_FreeSurface(surface_skill);
        SDL_DestroyTexture(texture_name);
        SDL_FreeSurface(surface_name);
        // 渲染选中的角色技能描述
    }
}

void choose_card(SDL_Window *window, SDL_Renderer *renderer, Player *player) {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
    SDL_Rect card_rect[3] = {{400,  300, 300, 450},
                             {800,  300, 300, 450},
                             {1200, 300, 300, 450}};
    int a, b, c;
    int selected_card = -1;
    TTF_Font *font = TTF_OpenFont("./res/ys_zt.ttf", 25), *title_font = TTF_OpenFont("./res/ys_zt.ttf", 35);
    a = generate_random(2, main_cardnum[player->player_career]);
    b = generate_random(2, main_cardnum[player->player_career]);
    c = generate_random(2, main_cardnum[player->player_career]);
//    printf("%d %d %d\n", a, b, c);
    while (b == a) {
        b = generate_random(2, main_cardnum[player->player_career]);
    }
    while (c == a || c == b) {
        c = generate_random(2, main_cardnum[player->player_career]);
    }
    Card *card[3] = {&main_card[player->player_career][a], &main_card[player->player_career][b],
                     &main_card[player->player_career][c]};
    printf("%d %d %d\n", a, b, c);
    SDL_Event event;
    Title title;
    Title_init(&title, "请选择想要的卡牌", TTF_OpenFont("./res/ys_zt.ttf", 50), 0.5, 0.2, COLOR_BLACK);
    Button game_continue;
    initButton(&game_continue, (Rect) {0.75, 0.75, 0.15, 0.08}, window, COLOR_GREY,
               COLOR_GREYGREEN,
               COLOR_LIGHT_RED, "继续游戏", "./res/ys_zt.ttf", 12);
    updateButton(&game_continue, window);
    while (1) {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
        SDL_RenderClear(renderer);
        if (selected_card != -1) {
            drawButton(renderer, &game_continue);
        }


        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);


        Title_print(&title, window, renderer);
        int hover[3];
        for (int i = 0; i < 3; i++) {
            hover[i] = (mouse_x >= card_rect[i].x && mouse_x < card_rect[i].x + card_rect[i].w &&
                        mouse_y >= card_rect[i].y &&
                        mouse_y < card_rect[i].y + card_rect[i].h);

        }
        for (int i = 0; i < 3; i++) {
            if (hover[i]) {
                print_card(renderer, card[i], card_rect[i], 1, selected_card == i, font, title_font);
            } else {
                print_card(renderer, card[i], card_rect[i], 0, selected_card == i, font, title_font);
            }
        }

        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    TTF_CloseFont(font);
                    TTF_CloseFont(title_font);
                    Button_destroy(&game_continue);
                    Title_destroy(&title);
                    game_Quit(window, renderer);
                    break;
                case SDL_MOUSEMOTION:
                    game_continue.isHovered = isMouseInButton(event.motion.x, event.motion.y, &game_continue);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        for (int i = 0; i < 3; i++) {
                            if (hover[i]) selected_card = i;
                        }
                    }
                    game_continue.isPressed = isMouseInButton(event.motion.x, event.motion.y, &game_continue);
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (selectedCharacter != -1 && game_continue.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &game_continue)) {
                        // 按钮被点击，执行相应操作
//                        printf("game continue Clicked!\n");
                        Button_destroy(&game_continue);
                        Title_destroy(&title);
                        add_card_to_bag(player, card[selected_card]);
                        return;
                    }
                    game_continue.isPressed = false;
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
}

void game_choose_reward(SDL_Renderer *renderer, SDL_Window *window, Player *player) {

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
    Title title;
    Title_init(&title, "你上一次挑战成绩不错，可以选择奖励", TTF_OpenFont("./res/ys_zt.ttf", 40), 0.5, 0.2, COLOR_BLACK);
    SDL_Event event;
    Button Choose_1, Choose_2, Choose_3;
    initButton(&Choose_1, (Rect) {0.4, 0.35, 0.2, 0.1}, window, COLOR_BLACK,
               COLOR_GREY,
               COLOR_GREYGREEN, "最大生命值+5", "./res/ys_zt.ttf", 16);
    initButton(&Choose_2, (Rect) {0.4, 0.50, 0.2, 0.1}, window, COLOR_BLACK,
               COLOR_GREY,
               COLOR_GREYGREEN, "一张卡牌", "./res/ys_zt.ttf", 16);
    initButton(&Choose_3, (Rect) {0.4, 0.65, 0.2, 0.1}, window, COLOR_BLACK,
               COLOR_GREY,
               COLOR_GREYGREEN, "一袋金币", "./res/ys_zt.ttf", 16);
    updateButton(&Choose_1, window);
    updateButton(&Choose_2, window);
    updateButton(&Choose_3, window);
    while (1) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
//                    printf("quit!\n");
                    Button_destroy(&Choose_1);
                    Button_destroy(&Choose_2);
                    Button_destroy(&Choose_3);
                    game_Quit(window, renderer);
                    break;
                case SDL_MOUSEMOTION:
                    Choose_1.isHovered = isMouseInButton(event.motion.x, event.motion.y, &Choose_1);
                    Choose_2.isHovered = isMouseInButton(event.motion.x, event.motion.y, &Choose_2);
                    Choose_3.isHovered = isMouseInButton(event.motion.x, event.motion.y, &Choose_3);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    Choose_1.isPressed = isMouseInButton(event.motion.x, event.motion.y, &Choose_1);
                    Choose_2.isPressed = isMouseInButton(event.motion.x, event.motion.y, &Choose_2);
                    Choose_3.isPressed = isMouseInButton(event.motion.x, event.motion.y, &Choose_3);
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (Choose_1.isPressed && isMouseInButton(event.button.x, event.button.y, &Choose_1)) {
                        // 按钮被点击，执行相应操作
                        player->hp += 5;
                        player->maxhp += 5;
//                        printf("Choose_1 Clicked!\n");
                        Button_destroy(&Choose_1);
                        Button_destroy(&Choose_2);
                        Button_destroy(&Choose_3);
                        return;
                    }
                    Choose_1.isPressed = false;
                    if (Choose_2.isPressed && isMouseInButton(event.button.x, event.button.y, &Choose_2)) {
                        // 按钮被点击，执行相应操作
//                        printf("Choose_2 Clicked!\n");
                        Button_destroy(&Choose_1);
                        Button_destroy(&Choose_2);
                        Button_destroy(&Choose_3);
                        choose_card(window, renderer, player);
                        return;
                    }
                    Choose_2.isPressed = false;
                    if (Choose_3.isPressed && isMouseInButton(event.button.x, event.button.y, &Choose_3)) {
                        // 按钮被点击，执行相应操作
                        player->coin += generate_random(100, 200);
//                        printf("Choose_3 Clicked!\n");
                        Button_destroy(&Choose_1);
                        Button_destroy(&Choose_2);
                        Button_destroy(&Choose_3);
                        return;
                    }
                    Choose_3.isPressed = false;
                    break;
            }
        }
        SDL_RenderClear(renderer);
        drawButton(renderer, &Choose_1);
        drawButton(renderer, &Choose_2);
        drawButton(renderer, &Choose_3);
        Title_print(&title, window, renderer);
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
}

void push_beginning_cards(Player *player) {
    for (int i = 0; i < 5; i++) {
        add_card_to_bag(player, &main_card[player->player_career][0]);
        add_card_to_bag(player, &main_card[player->player_career][1]);
    }
    add_card_to_bag(player, &main_card[player->player_career][0]);
    add_card_to_bag(player, &main_card[player->player_career][2]);
}

void show_all_card(SDL_Window *window, SDL_Renderer *renderer, Player *player) {
    int y = 0;
    int mouse_x, mouse_y;
    bool dragging = false;
    int quit = 1;
    SDL_Event event;
    Button game_back;
    initButton(&game_back, (Rect) {0.05, 0.85, 0.15, 0.08}, window, COLOR_GREY,
               COLOR_DARKGREY,
               COLOR_BLACK, "返回", "./res/ys_zt.ttf", 12);
    while (quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    Button_destroy(&game_back);
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
                    game_back.isHovered = isMouseInButton(event.motion.x, event.motion.y, &game_back);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    game_back.isPressed = isMouseInButton(event.motion.x, event.motion.y, &game_back);
                    dragging = true;
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    dragging = false;
                    if (game_back.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &game_back)) {
                        Button_destroy(&game_back);
                        return;
                    }
                    game_back.isPressed = false;
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
        print_everycard(renderer, player, y);
        drawButton(renderer, &game_back);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }

}

void show_all_collection(SDL_Window *window, SDL_Renderer *renderer, Player *player) {
    int y = 0;
    int mouse_x, mouse_y;
    bool dragging = false;
    int quit = 1;
    SDL_Event event;
    Button game_back;
    initButton(&game_back, (Rect) {0.05, 0.85, 0.15, 0.08}, window, COLOR_GREY,
               COLOR_DARKGREY,
               COLOR_BLACK, "返回", "./res/ys_zt.ttf", 12);
    while (quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    Button_destroy(&game_back);
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
                    game_back.isHovered = isMouseInButton(event.motion.x, event.motion.y, &game_back);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    game_back.isPressed = isMouseInButton(event.motion.x, event.motion.y, &game_back);
                    dragging = true;
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    dragging = false;
                    if (game_back.isPressed &&
                        isMouseInButton(event.button.x, event.button.y, &game_back)) {
                        Button_destroy(&game_back);
                        return;
                    }
                    game_back.isPressed = false;
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
        print_everycollection(renderer, player, y);
        drawButton(renderer, &game_back);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }

}