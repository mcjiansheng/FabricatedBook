//
// Created by 48811 on 25-1-17.
//

#ifndef SLAYTHESPIRE_FIGHT_H
#define SLAYTHESPIRE_FIGHT_H

#include "Saves.h"
#include "card.h"
#include "color.h"

//#include "button.h"
//typedef struct Button Button;
#include "videos.h"
#include "gamecreater.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct FIGHT {
    int enemy_num;
    Enemy *enemy[3];
} Fight;

void event_init();

extern struct SUMMARY summary;

void game_fight(SDL_Window *window, SDL_Renderer *renderer, Fight *fight, Player *player, int dif, int layer_num);

void game_fail(SDL_Window *window, SDL_Renderer *renderer, Player *player);

void fight_success(SDL_Window *window, SDL_Renderer *renderer, Player *player, int dif, int layer_num);

void player_choose_potion(Player *player, int mouse_x, int mouse_y, int *choose_potion);

void draw_Potion(SDL_Renderer *renderer, Player *player);

void print_potion_discribe(SDL_Renderer *renderer, Player *player, int choose_potion, Button *potion_use,
                           Button *potion_discard);

#endif //SLAYTHESPIRE_FIGHT_H
