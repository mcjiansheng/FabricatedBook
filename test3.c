#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 假设 Player 结构体的定义
typedef struct Player {
    // 这里可以添加 Player 的具体成员
    int health;
} Player;

// Events 结构体定义
typedef struct events {
    char *name;
    char *discribe;
    int choice_num;
    char *choice_name[4];
    char *choice_discribe[4];
    char *choice_end[4];

    void (*effect[4])(Player *);
} Events;

// 示例 effect 函数
void effect1(Player *player) {
    player->health += 10;
    printf("Player's health increased by 10. New health: %d\n", player->health);
}

void effect2(Player *player) {
    player->health -= 5;
    printf("Player's health decreased by 5. New health: %d\n", player->health);
}

// 渲染文本函数
void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
    if (surface == NULL) {
        printf("TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

// Events_main 函数
void Events_main(Events *events, SDL_Renderer *renderer, Player *player) {
    // 初始化 TTF
    if (TTF_Init() == -1) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        return;
    }
    TTF_Font *font = TTF_OpenFont("./res/ys_zt.ttf", 24);
    if (font == NULL) {
        printf("TTF_OpenFont Error: %s\n", TTF_GetError());
        TTF_Quit();
        return;
    }

    SDL_Color textColor = {255, 255, 255, 255};
    int yOffset = 50;

    // 绘制事件名称
    renderText(renderer, font, events->name, 50, yOffset, textColor);
    yOffset += 30;

    // 绘制事件描述
    renderText(renderer, font, events->discribe, 50, yOffset, textColor);
    yOffset += 50;

    // 绘制选项
    for (int i = 0; i < events->choice_num; i++) {
        char choiceText[256];
        snprintf(choiceText, sizeof(choiceText), "%d. %s: %s", i + 1, events->choice_name[i],
                 events->choice_discribe[i]);
        renderText(renderer, font, choiceText, 50, yOffset, textColor);
        yOffset += 30;
    }

    SDL_RenderPresent(renderer);

    // 等待玩家选择
    SDL_Event event;
    int choice = -1;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            for (int i = 0; i < events->choice_num; i++) {
                SDL_Rect choiceRect = {50, 130 + i * 30, 400, 30};
                if (SDL_PointInRect(&((SDL_Point) {mouseX, mouseY}), &choiceRect)) {
                    choice = i;
                    break;
                }
            }
            if (choice != -1) {
                break;
            }
        }
    }

    // 执行选择的效果
    if (choice != -1) {
        if (events->effect[choice] != NULL) {
            events->effect[choice](player);
        }

        // 清空屏幕
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 绘制选择结果
        renderText(renderer, font, events->choice_end[choice], 50, 50, textColor);
        SDL_RenderPresent(renderer);

        // 等待一段时间
        SDL_Delay(3000);
    }

    TTF_CloseFont(font);
    TTF_Quit();
}

#undef main

int main(int argc, char *argv[]) {
    // 初始化 SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // 创建窗口
    SDL_Window *window = SDL_CreateWindow("Events Node", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // 创建渲染器
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 初始化 Player
    Player player = {100};

    // 初始化 Events
    Events events;
    events.name = "神秘事件";
    events.discribe = "你遇到了一个神秘的事件，做出你的选择。";
    events.choice_num = 2;
    events.choice_name[0] = "接受祝福";
    events.choice_discribe[0] = "获得一些生命值";
    events.choice_end[0] = "你获得了祝福，生命值增加。";
    events.effect[0] = effect1;
    events.choice_name[1] = "遭受诅咒";
    events.choice_discribe[1] = "失去一些生命值";
    events.choice_end[1] = "你遭受了诅咒，生命值减少。";
    events.effect[1] = effect2;

    // 调用 Events_main 函数
    Events_main(&events, renderer, &player);

    // 清理资源
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}