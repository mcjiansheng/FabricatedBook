//
// Created by 48811 on 24-12-27.
//

#include "button.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 按钮结构体

// 初始化按钮
#define FONT_DYNAMIC_SIZE 20

void updateButton(Button *button, SDL_Window *window) {
    int window_w, window_h;
    SDL_GetWindowSize(window, &window_w, &window_h);
    button->rect.x = window_w * button->rec.x;
    button->rect.y = window_h * button->rec.y;
    button->rect.w = window_w * button->rec.w;
    button->rect.h = window_h * button->rec.h;
    TTF_CloseFont(button->font);
    button->font = TTF_OpenFont(button->font_file, (window_h - 600) / FONT_DYNAMIC_SIZE + button->font_size);
//    printf("font size is %d\nwindow size is%d\n", window_h / FONT_DYNAMIC_SIZE + button->font_size, window_h);
//    if (button->font == NULL) {
//        printf("font is NULL\n");
//    }
}

void initButton(Button *button, Rect rec, SDL_Window *window, SDL_Color color,
                SDL_Color hoverColor, SDL_Color pressColor,
                char *text, char *font_file, int font_size) {
    button->rec = rec;
    int window_w, window_h;
    SDL_GetWindowSize(window, &window_w, &window_h);
    button->rect.x = window_w * rec.x;
    button->rect.y = window_h * rec.y;
    button->rect.w = window_w * rec.w;
    button->rect.h = window_h * rec.h;
    button->isHovered = false;
    button->isPressed = false;
    button->color = color;
    button->hoverColor = hoverColor;
    button->pressColor = pressColor;
    button->text = text;
    button->font_file = font_file;
    button->font_size = font_size;
    button->font = TTF_OpenFont(font_file, (window_h - 600) / FONT_DYNAMIC_SIZE + button->font_size);
}

// 绘制按钮
void drawButton(SDL_Renderer *renderer, Button *button) {
    SDL_Color currentColor;
    if (button->isPressed) {
        currentColor = button->pressColor;
    } else if (button->isHovered) {
        currentColor = button->hoverColor;
    } else {
        currentColor = button->color;
    }
    SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
    SDL_RenderFillRect(renderer, &button->rect);

    // 绘制按钮上的文本
    if (button->text != NULL && button->font != NULL) {
//        printf("trying to print text\n");
        SDL_Surface *surface = TTF_RenderUTF8_Blended(button->font, button->text,
                                                      (SDL_Color) {255, 255, 255, 255}); // 修改这里
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        int textWidth = surface->w;
        int textHeight = surface->h;
        SDL_FreeSurface(surface);
        SDL_Rect textRect = {button->rect.x + (button->rect.w - textWidth) / 2,
                             button->rect.y + (button->rect.h - textHeight) / 2, textWidth, textHeight};
        SDL_RenderCopy(renderer, texture, NULL, &textRect);
        SDL_DestroyTexture(texture);
    }
}

void Button_destroy(Button *button) {
    TTF_CloseFont(button->font);
}
// 检查鼠标是否在按钮内
bool isMouseInButton(int mouseX, int mouseY, Button *button) {
    if (mouseX >= button->rect.x && mouseX <= button->rect.x + button->rect.w &&
        mouseY >= button->rect.y && mouseY <= button->rect.y + button->rect.h) {
        return true;
    }
    return false;
}

void Title_init(Title *title, char *text, TTF_Font *font, double x, double y, SDL_Color color) {
    title->text = text;
    title->font = font;
    title->x = x;
    title->y = y;
    title->color = color;
}

void Title_print(Title *title, SDL_Window *window, SDL_Renderer *renderer) {
    SDL_Surface *surface = TTF_RenderUTF8_Blended(title->font, title->text,
                                                  title->color);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {.x=title->x * 1920, .y=title->y * 1080};
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x -= rect.w / 2;
    rect.y -= rect.h / 2;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
//    SDL_RenderPresent(renderer);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Title_destroy(Title *title) {
    TTF_CloseFont(title->font);
}

int generate_random(int lower, int upper) {
    srand(rand());
    return (rand() % (upper - lower + 1)) + lower;
}

int generate_random_with_weighted(int x[5]) {
    int i, sum = 0;
    for (i = 0; i < 5; i++) {
        sum += x[i];
    }
    int rd = rand() % sum;
    sum = 0;
    for (i = 0; i < 5; i++) {
        sum += x[i];
        if (rd < sum) {
            return i;
        }
    }
}

void draw_rectangle(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}


void draw_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color) {
    char *str = strdup(text);  // 复制字符串，避免修改原始字符串
    char *token = strtok(str, "\n");
    int line_height = TTF_FontLineSkip(font);  // 获取字体的行高
    int num_lines = 0;
    while (token != NULL) {
        num_lines++;
        token = strtok(NULL, "\n");
    }
    int start_y = y - (line_height * num_lines / 2);  // 计算起始 Y 坐标，使文本居中
    token = strdup(text);
    token = strtok(token, "\n");
    int line = 0;
    while (token != NULL) {
        SDL_Surface *surface = TTF_RenderUTF8_Blended(font, token, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect = {x, start_y + (line * line_height), surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        line++;
        token = strtok(NULL, "\n");
    }
    free(str);
    free(token);
}

void
draw_text_alpha(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color, int alpha) {
    char *str = strdup(text);  // 复制字符串，避免修改原始字符串
    char *token = strtok(str, "\n");
    int line_height = TTF_FontLineSkip(font);  // 获取字体的行高
    int num_lines = 0;
    while (token != NULL) {
        num_lines++;
        token = strtok(NULL, "\n");
    }
    int start_y = y - (line_height * num_lines / 2);  // 计算起始 Y 坐标，使文本居中
    token = strdup(text);
    token = strtok(token, "\n");
    int line = 0;
    while (token != NULL) {
        SDL_Surface *surface = TTF_RenderUTF8_Blended(font, token, color);
        SDL_SetSurfaceAlphaMod(surface, alpha);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect = {x, start_y + (line * line_height), surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        line++;
        token = strtok(NULL, "\n");
    }
    free(str);
    free(token);
}

void draw_text_with_alpha(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color,
                          int alpha) {
    char *str = strdup(text);  // 复制字符串，避免修改原始字符串
    char *token = strtok(str, "\n");
    int line_height = TTF_FontLineSkip(font);  // 获取字体的行高
    int num_lines = 0;
    while (token != NULL) {
        num_lines++;
        token = strtok(NULL, "\n");
    }
    int start_y = y - (line_height * num_lines / 2);  // 计算起始 Y 坐标，使文本居中
    token = strdup(text);
    token = strtok(token, "\n");
    int line = 0;
    while (token != NULL) {
        SDL_Surface *surface = TTF_RenderUTF8_Blended(font, token, color);
        SDL_SetSurfaceAlphaMod(surface, alpha);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect = {x - (surface->w / 2), start_y + (line * line_height), surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        line++;
        token = strtok(NULL, "\n");
    }
    free(str);
    free(token);
}

void print_card(SDL_Renderer *renderer, Card *card, SDL_Rect rect, int hover, int selected, TTF_Font *font,
                TTF_Font *title_font) {
    SDL_Color border_color;
    switch (card->type) {
        case 1:
            border_color = COLOR_RED;
            break;
        case 2:
            border_color = COLOR_LIGHT_BLUE;
            break;
        case 3:
            border_color = COLOR_GREY;
            break;
        case 4:
            border_color = COLOR_LIGHT_GREEN;
            break;
    }
    if (selected) {
        SDL_Rect selected_rect = {rect.x - 20 - 20 * hover, rect.y - 20 - 20 * hover, rect.w + 40 + 40 * hover,
                                  rect.h + 40 + 40 * hover};
        draw_rectangle(renderer, selected_rect, COLOR_GOLD);
    }

    SDL_Rect border_rect = {rect.x - 5 - 5 * hover, rect.y - 5 - 5 * hover, rect.w + 10 + 10 * hover,
                            rect.h + 10 + 10 * hover};
    draw_rectangle(renderer, border_rect, border_color);

    draw_rectangle(renderer, rect, COLOR_LIGHT_GREY);
    SDL_Color text_color = COLOR_BLACK;
    draw_text(renderer, title_font, card->name, rect.x + 10, rect.y + 20, text_color);
    char cost_str[10];
    sprintf(cost_str, "费用: %d", card->cost);
    draw_text(renderer, font, cost_str, rect.x + 10, rect.y + rect.h / 3, text_color);
    if (card->exhaust) {
        draw_text(renderer, font, "消耗", rect.x + rect.w / 2, rect.y + rect.h / 3, text_color);
    }
    draw_text(renderer, font, card->description, rect.x + 10, rect.y + rect.h / 2, text_color);
}

void print_collection(SDL_Renderer *renderer, Collection *collection, SDL_Rect rect, TTF_Font *font,
                      TTF_Font *title_font) {
    SDL_Color border_color;
    switch (collection->value) {
        case 0:
            border_color = COLOR_BLACK;
            break;
        case 1:
            border_color = COLOR_LIGHT_BLUE;
            break;
        case 2:
            border_color = COLOR_PURPLE;
            break;
        case 3:
            border_color = COLOR_GOLD;
            break;
        case 5:
            border_color = COLOR_LIGHT_RED;
            break;
        case 6:
            border_color = COLOR_GREYGREEN;
            break;
    }
    SDL_Rect border_rect = {rect.x - 5, rect.y - 5, rect.w + 10,
                            rect.h + 10};
    draw_rectangle(renderer, border_rect, border_color);

    draw_rectangle(renderer, rect, COLOR_LIGHT_GREY);
    SDL_Color text_color = COLOR_BLACK;
    draw_text(renderer, title_font, collection->name, rect.x + 10, rect.y + 20, text_color);
    draw_text(renderer, font, collection->discribe, rect.x + 10, rect.y + rect.h / 2, text_color);
}