//
// Created by 48811 on 25-1-24.
//

#ifndef SLAYTHESPIRE_EVENTS_H
#define SLAYTHESPIRE_EVENTS_H

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
#include "fight.h"

typedef struct events {
    char *name;
    char *discribe;
    int choice_num;
    char *choice_name[4], *choice_discribe[4], *choice_end[4];

    void (*effect[4])(Player *);
} Events;
typedef struct rewards {
    Events *events;
    int x[4], y[4];
} Rewards;

//Rewards events_rewards;
void init_events();

void init_rewards();

void init_decition();

void init_safehouse();

void enter_events(SDL_Window *window, SDL_Renderer *renderer, Player *player, Events *events);

void enter_rewards(SDL_Window *window, SDL_Renderer *renderer, Player *player, Rewards *rewards);

#endif //SLAYTHESPIRE_EVENTS_H
