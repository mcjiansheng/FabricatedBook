//
// Created by 48811 on 25-1-17.
//

#ifndef SLAYTHESPIRE_NODES_EVENT_H
#define SLAYTHESPIRE_NODES_EVENT_H

#include "Saves.h"
#include "card.h"
#include "color.h"
#include "button.h"
//#include "videos.h"
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

void game_fight(SDL_Window *window, SDL_Renderer *renderer, Fight *fight, Player *player);

//const char *sug[] = {, "请选择释放对象", "能量不足"};

#endif //SLAYTHESPIRE_NODES_EVENT_H
