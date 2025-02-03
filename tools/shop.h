//
// Created by 48811 on 25-2-3.
//

#ifndef SLAYTHESPIRE_SHOP_H
#define SLAYTHESPIRE_SHOP_H

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
#include "fight.h"
#include "events.h"
#include "collection.h"

extern int discard_coin;
typedef struct shop {
    Card *card[7];
    int card_coin[7];
    Collection *collection[3];
    int collection_x[3], collection_y[3];
    int collection_coin[3];
    Potion *potion[3];
    int potion_coin[3];
    bool discard_able;
} Shop;

Shop *init_shop(Player *player);

void enter_shop(SDL_Window *window, SDL_Renderer *renderer, Player *player, Shop *shop);

void free_shop(Shop *shop);

void player_choose_card_to_discard(SDL_Window *window, SDL_Renderer *renderer, Player *player);

#endif //SLAYTHESPIRE_SHOP_H
