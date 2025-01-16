//
// Created by 48811 on 25-1-16.
//

#ifndef SLAYTHESPIRE_MAP_H
#define SLAYTHESPIRE_MAP_H

#include "Saves.h"
#include "card.h"
#include "color.h"
#include "button.h"
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

typedef struct node {
    int type;//1fight 2 Emergency 3boss 4 unexpectedly 5reward 6shop 7another path 8decision 9safe house
    int nxt_num;
    struct node **nxt;
    struct node *generate_nxt;
} Node;

typedef struct map {
    int length, width;
    Node *head, *tail;

    int size[10];
    Node **nodes[10];

    void (*generate)(int length, int width, struct map *map);
} Map;

void init_map(PPT *ppt);

void print_map(SDL_Window *window, SDL_Renderer *renderer);

#endif //SLAYTHESPIRE_MAP_H
