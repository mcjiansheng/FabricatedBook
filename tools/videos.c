//
// Created by 48811 on 25-1-14.
//

#include "videos.h"

extern PPT first_floor, second_floor[2], third_floor[2], forth_floor[2], fifth_floor[2], small_path, sixth_floor[2];
extern int windowWidth, windowHeight;

void init_ppt() {
    first_floor = (PPT) {1, "荒野", "该区域环境平缓", NULL};
    second_floor[0] = (PPT) {2, "森林", "", &third_floor[0]};
    second_floor[1] = (PPT) {5, "海港", "进入非战斗节点时金币损失金币，战斗获得金币数量增加", &third_floor[1]};
    third_floor[0] = (PPT) {3, "诡异秘林", "", &forth_floor[0]};
    third_floor[1] = (PPT) {6, "海洋", "每进入一个战斗节点，造成伤害-1，\n"
                                       "每进入一个非战斗节点，造成伤害+1，至多+-3", &forth_floor[1]};
    forth_floor[0] = (PPT) {4, "迷雾", "", NULL};
    forth_floor[1] = (PPT) {7, "深海", "", NULL};
    fifth_floor[0] = (PPT) {8, "高塔", "强大的敌人就在前方，战胜它", NULL};
    fifth_floor[1] = (PPT) {9, "巴别塔", "。。。", NULL};
    small_path = (PPT) {10, "洞穴", "每前进一步消耗少许金币", NULL};
    sixth_floor[0] = (PPT) {11, "追忆之影", "", NULL};
    sixth_floor[1] = (PPT) {12, "虚妄之书", "", NULL};
}

void cutscene_animation(SDL_Window *window, SDL_Renderer *renderer, PPT *ppt) {
    TTF_Font *textfont = TTF_OpenFont("./res/ys_zt.ttf", 30);
    TTF_Font *titlefont = TTF_OpenFont("./res/ys_zt.ttf", 70);
    SDL_Surface *textsurface, *titlesurface;
    int t = 0;
    SDL_Event event;
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    printf("show ppt\n");
    while (t < 255) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                game_Quit(window, renderer);
            }
        }
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);
        SDL_RenderClear(renderer);
        draw_text_with_alpha(renderer, textfont, ppt->description, windowWidth / 2, 500, COLOR_BLACK, t);
        draw_text_with_alpha(renderer, titlefont, ppt->title, windowWidth / 2, 200, COLOR_BLACK, t);
        SDL_RenderPresent(renderer);
        t += 8;
        SDL_Delay(50);
    }
    printf("waiting\n");
    int quit = 1;
    while (quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                game_Quit(window, renderer);
            }
            if (event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONUP) {
                quit = 0;
            }
        }
        SDL_Delay(50);
    }
    printf("quit\n");
    while (t > 0) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                game_Quit(window, renderer);
            }
        }
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
        SDL_RenderClear(renderer);
        draw_text_with_alpha(renderer, textfont, ppt->description, windowWidth / 2, 500, COLOR_BLACK, t);
        draw_text_with_alpha(renderer, titlefont, ppt->title, windowWidth / 2, 200, COLOR_BLACK, t);
        SDL_RenderPresent(renderer);
        t -= 8;
        SDL_Delay(50);
    }
}