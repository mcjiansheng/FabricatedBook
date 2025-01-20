//
// Created by 48811 on 25-1-16.
//

#ifndef SLAYTHESPIRE_MAP_H
#define SLAYTHESPIRE_MAP_H

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
#include "nodes_event.h"

#define MAX_NODE_TYPES 9

#define MAX_LAYERS 6
#define MAX_WIDTH 5
#define MAX_LENGTH 9

typedef enum {
    FIGHT = 1,
    EMERGENCY,
    BOSS,
    UNEXPECTEDLY,
    REWARD,
    SHOP,
    ANOTHER_PATH,
    DECISION,
    SAFE_HOUSE
} NodeType;

typedef struct Node {
    int x, y;
    NodeType type;
    int nxt_num;
    struct Node *nxt[MAX_WIDTH];
} Node;

typedef struct Layer {
    int width;
    int length;
    int num;
    int line_num[MAX_LENGTH];
    Node *head, *tail;
    Node *nodes[MAX_LENGTH][MAX_WIDTH];  // 2D array of nodes
} Layer;

// 定义每一层的节点生成概率
extern int layer_probabilities[MAX_LAYERS][9];
//extern SDL_Texture *node_texture[10];

void init_every_layer();

void free_picture_node();

void free_layer(Layer *layer);

NodeType random_choice(int probabilities[], int size);

Node *create_node(NodeType type);

void init_layer(Layer *layer, int layer_idx);

void init_layer_six(Layer *layer);

void print_layer(Layer *layer);

extern SDL_Texture *node_texture[10];

void init_picture_node(SDL_Renderer *renderer);

typedef struct ppt {
    int num;
    char *title, *description;
    struct ppt *next_PPT;
    Layer *layer;
} PPT;

void init_ppt();

void cutscene_animation(SDL_Window *window, SDL_Renderer *renderer, PPT *ppt);

void init_map_printer(Layer *layer);

void print_map(SDL_Window *window, SDL_Renderer *renderer, Layer *layer, int x);

void print_nodes(SDL_Renderer *renderer, Node *node, Layer *layer, int x);

void
check_choose_nodes(SDL_Window *window, SDL_Renderer *renderer, Node *now_node, Layer *layer, int mouse_x, int mouse_y,
                   int x,
                   Player *player);

void goin_nodes(SDL_Window *window, SDL_Renderer *renderer, Node *node, Layer *layer, Player *player);

#endif //SLAYTHESPIRE_MAP_H
