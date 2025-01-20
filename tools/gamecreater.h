//
// Created by 48811 on 25-1-12.
//

#ifndef SLAYTHESPIRE_GAMECREATER_H
#define SLAYTHESPIRE_GAMECREATER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Saves.h"
#include "Button.h"
#include "card.h"

typedef struct {
    const char *name;
    const char *skill;  // 角色技能描述
    SDL_Texture *image; // 角色立绘图片
    int unlocked;  // 0 表示未解锁，1 表示已解锁
    SDL_Rect rect;
    int hp;//基础生命值
    SDL_Color color;//人物颜色
} Character;

int max(int x, int y);

int min(int x, int y);

void init_characters(SDL_Renderer *renderer, PlayerInfo info);

void render_character_selection(SDL_Renderer *renderer, int windowsx, int windowsy);

void select_character(int mouseX, int mouseY);

void render_selected_character(SDL_Renderer *renderer, int windowsx, int windowsy);

extern Character characters[];
extern int selectedCharacter;

void game_choose_reward(SDL_Renderer *renderer, SDL_Window *window, Player *player);

void choose_card(SDL_Window *window, SDL_Renderer *renderer, Player *player);

void push_beginning_cards(Player *player);

void show_all_card(SDL_Window *window, SDL_Renderer *renderer, Player *player);

#endif //SLAYTHESPIRE_GAMECREATER_H
