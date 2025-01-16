#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


// 卡牌结构体
typedef struct Card {
    char *name;
    char *description;
    int cost;
    int exhaust;
    int type;
} Card;


// 初始化 SDL
int init_SDL(SDL_Window **window, SDL_Renderer **renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    *window = SDL_CreateWindow("Slay the Spire Card Selection", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920,
                               1080, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 0;
    }
    return 1;
}


// 加载 SDL 字体
TTF_Font *load_font() {
    TTF_Font *font = TTF_OpenFont("./res/ys_zt.ttf", 20);  // 使用宋体字体，可根据需要修改
    if (font == NULL) {
        printf("Failed to open font! SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    }
    return font;
}


// 绘制矩形
void draw_rectangle(SDL_Renderer *renderer, SDL_Rect rect, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &rect);
}


// 绘制文本
void draw_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int r, int g, int b, int a) {
    SDL_Color color = {r, g, b, a};
    SDL_Surface *surface = TTF_RenderUTF8_Solid(font, text, color);  // 使用 UTF-8 编码绘制中文
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect text_rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &text_rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


// 绘制卡牌
void draw_card(SDL_Renderer *renderer, Card *card, SDL_Rect rect, int hover, int selected, TTF_Font *font) {

    int border_r = 255, border_g = 255, border_b = 255, border_a = 255;
    switch (card->type) {
        case 1:
            border_r = 255;
            border_g = 0;
            border_b = 0;
            break;
        case 2:
            border_r = 0;
            border_g = 0;
            border_b = 255;
            break;
        case 3:
            border_r = 128;
            border_g = 128;
            border_b = 128;
            break;
        case 4:
            border_r = 0;
            border_g = 255;
            border_b = 0;
            break;
    }
    if (selected) {
        SDL_Rect selected_rect = {rect.x - 20, rect.y - 20, rect.w + 40, rect.h + 40};
        draw_rectangle(renderer, selected_rect, 255, 215, 0, 255);
    }

    SDL_Rect border_rect = {rect.x - 5, rect.y - 5, rect.w + 10, rect.h + 10};
    draw_rectangle(renderer, border_rect, border_r, border_g, border_b, border_a);

    int red = 240, green = 240, blue = 240, alpha = 255;
    draw_rectangle(renderer, rect, red, green, blue, alpha);
    SDL_Color text_color = {0, 0, 0, 255};
    draw_text(renderer, font, card->name, rect.x + 10, rect.y + 10, text_color.r, text_color.g, text_color.b,
              text_color.a);
    char cost_str[10];
    sprintf(cost_str, "费用: %d", card->cost);
    draw_text(renderer, font, cost_str, rect.x + 10, rect.y + 50, text_color.r, text_color.g, text_color.b,
              text_color.a);
    draw_text(renderer, font, card->description, rect.x + 10, rect.y + 100, text_color.r, text_color.g, text_color.b,
              text_color.a);
}

#undef main

// 主函数
int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;


    if (!init_SDL(&window, &renderer)) {
        return 1;
    }


    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    TTF_Font *font = load_font();
    if (font == NULL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    Card card1 = {"打击", "造成 6 点伤害", 1, 0, 1};
    Card card2 = {"防御", "获得 5 点格挡", 1, 0, 2};
    Card card3 = {"重击", "造成 8 点伤害，施加易伤", 2, 0, 1};


    SDL_Rect card1_rect = {400, 500, 200, 300};
    SDL_Rect card2_rect = {860, 500, 200, 300};
    SDL_Rect card3_rect = {1320, 500, 200, 300};


    int running = 1;
    int selected_card = -1;
    SDL_Event event;


    while (running) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);


        int hover1 = (mouse_x >= card1_rect.x && mouse_x < card1_rect.x + card1_rect.w && mouse_y >= card1_rect.y &&
                      mouse_y < card1_rect.y + card1_rect.h);
        int hover2 = (mouse_x >= card2_rect.x && mouse_x < card2_rect.x + card2_rect.w && mouse_y >= card2_rect.y &&
                      mouse_y < card2_rect.y + card2_rect.h);
        int hover3 = (mouse_x >= card3_rect.x && mouse_y >= card3_rect.y && mouse_y < card3_rect.y + card3_rect.h);


        if (hover1) {
            draw_card(renderer, &card1, card1_rect, 1, selected_card == 0, font);
        } else {
            draw_card(renderer, &card1, card1_rect, 0, selected_card == 0, font);
        }


        if (hover2) {
            draw_card(renderer, &card2, card2_rect, 1, selected_card == 1, font);
        } else {
            draw_card(renderer, &card2, card2_rect, 0, selected_card == 1, font);
        }


        if (hover3) {
            draw_card(renderer, &card3, card3_rect, 1, selected_card == 2, font);
        } else {
            draw_card(renderer, &card3, card3_rect, 0, selected_card == 2, font);
        }


        SDL_RenderPresent(renderer);


        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (hover1) selected_card = 0;
                    else if (hover2) selected_card = 1;
                    else if (hover3) selected_card = 2;
                }
            }
        }
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();


    if (selected_card != -1) {
        switch (selected_card) {
            case 0:
                printf("选择的卡牌: %s\n", card1.name);
                break;
            case 1:
                printf("选择的卡牌: %s\n", card2.name);
                break;
            case 2:
                printf("选择的卡牌: %s\n", card3.name);
                break;
        }
    }


    return 0;
}