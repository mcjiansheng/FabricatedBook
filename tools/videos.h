//
// Created by 48811 on 25-1-14.
//

#ifndef SLAYTHESPIRE_VIDEOS_H
#define SLAYTHESPIRE_VIDEOS_H

#include "map.h"
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
#include "button.h"


typedef struct PPT {
    int num;
    char *title, *description;
    struct PPT *next_PPT;
    Map *map;
} PPT;


void init_ppt();

void cutscene_animation(SDL_Window *window, SDL_Renderer *renderer, PPT *ppt);


#endif //SLAYTHESPIRE_VIDEOS_H
