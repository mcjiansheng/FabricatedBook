//
// Created by 48811 on 24-12-27.
//

#ifndef SLAYTHESPIRE_BUTTON_H
#define SLAYTHESPIRE_BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Saves.h"
#include <time.h>
#include "card.h"
#include "color.h"
#include <string.h>

extern int seed;

void game_Quit(SDL_Window *window, SDL_Renderer *renderer);

typedef struct {
    double x, y, w, h;
} Rect;

typedef struct {
    Rect rec;
    SDL_Rect rect;
    bool isHovered;
    bool isPressed;
    SDL_Color color;
    SDL_Color hoverColor;
    SDL_Color pressColor;
    char *text;
    TTF_Font *font;
    FILE *font_file;
    int font_size;
} Button;

void initButton(Button *button, Rect rec, SDL_Window *window, SDL_Color color,
                SDL_Color hoverColor, SDL_Color pressColor,
                char *text, FILE *font_file, int font_size);

void drawButton(SDL_Renderer *renderer, Button *button);

bool isMouseInButton(int mouseX, int mouseY, Button *button);

void updateButton(Button *button, SDL_Window *window);

void Button_destroy(Button *button);

typedef struct {
    char *text;
    TTF_Font *font;
    double x, y;
    SDL_Color color;
} Title;

void Title_init(Title *title, char *text, TTF_Font *font, double x, double y, SDL_Color color);

void Title_print(Title *title, SDL_Window *window, SDL_Renderer *renderer);

void Title_destroy(Title *title);

int generate_random(int lower, int upper);

void draw_rectangle(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color);

void draw_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color);

void draw_text_with_alpha(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color,
                          int alpha);

void print_card(SDL_Renderer *renderer, Card *card, SDL_Rect rect, int hover, int selected, TTF_Font *font,
                TTF_Font *title_font);

#endif //SLAYTHESPIRE_BUTTON_H
