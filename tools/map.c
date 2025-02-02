//
// Created by 48811 on 25-1-16.
//

#include "map.h"

extern int windowWidth, windowHeight;

extern Layer layers[MAX_LAYERS];
extern PPT first_floor, second_floor[2], third_floor[2], forth_floor[2], fifth_floor[2], small_path, sixth_floor[2];
extern int windowWidth, windowHeight;
int layer_probabilities[MAX_LAYERS][9] = {
        {60, 10, 0, 30, 0,  0,  0, 0, 0},  // 第1层
        {40, 20, 0, 10, 10, 10, 0, 0, 10},  // 第2层
        {40, 20, 0, 10, 10, 10, 0, 0, 10},  // 第3层
        {40, 20, 0, 10, 10, 10, 0, 0, 10},  // 第4层
        {40, 20, 0, 10, 10, 10, 0, 0, 10},  // 第5层
        {0,  0,  0, 0,  0,  0,  0, 0, 100}   // 第6层，固定线路
};
SDL_Texture *node_texture[10];

void init_picture_node(SDL_Renderer *renderer) {
    node_texture[1] = IMG_LoadTexture(renderer, "./img/fight.png");
    node_texture[2] = IMG_LoadTexture(renderer, "./img/Emergency.png");
    node_texture[3] = IMG_LoadTexture(renderer, "./img/boss.png");
    node_texture[4] = IMG_LoadTexture(renderer, "./img/unexpectedly.png");
    node_texture[5] = IMG_LoadTexture(renderer, "./img/reward.png");
    node_texture[6] = IMG_LoadTexture(renderer, "./img/shop.png");
    node_texture[7] = IMG_LoadTexture(renderer, "./img/another_path.png");
    node_texture[8] = IMG_LoadTexture(renderer, "./img/decision.png");
    node_texture[9] = IMG_LoadTexture(renderer, "./img/safe_house.png");
}

void free_picture_node() {
    for (int i = 1; i <= 9; i++) {
        SDL_DestroyTexture(node_texture[i]);
    }
}

void init_ppt() {
    first_floor = (PPT) {1, "荒野", "该区域环境平缓", &second_floor, &layers[0]};
    second_floor[0] = (PPT) {2, "森林", "进入非战斗节点时金币损失金币，战斗获得金币数量增加", &third_floor[0],
                             &layers[1]};
    second_floor[1] = (PPT) {5, "海港", "进入非战斗节点时金币损失金币，战斗获得金币数量增加", &third_floor[1],
                             &layers[1]};
    third_floor[0] = (PPT) {3, "诡异秘林", "每进入一个战斗节点，造成伤害-1，每进入一个非战斗节点，造成伤害+1，至多+-3\n",
                            &forth_floor[0], &layers[2]};
    third_floor[1] = (PPT) {6, "海洋", "每进入一个战斗节点，造成伤害-1，\n"
                                       "每进入一个非战斗节点，造成伤害+1，至多+-3", &forth_floor[1], &layers[2]};
    forth_floor[0] = (PPT) {4, "迷雾", "每次前进都有概率回复或损失生命值", NULL, &layers[3]};
    forth_floor[1] = (PPT) {7, "深海", "每次前进都有概率回复或损失生命值", NULL, &layers[3]};
    fifth_floor[0] = (PPT) {8, "高塔", "强大的敌人就在前方，战胜它", NULL, &layers[4]};
    fifth_floor[1] = (PPT) {9, "巴别塔", "。。。", NULL, &layers[4]};
    small_path = (PPT) {10, "洞穴", "每前进一步消耗少许金币", NULL, &layers[5]};
    sixth_floor[0] = (PPT) {11, "追忆之影", "", NULL, &layers[5]};
    sixth_floor[1] = (PPT) {12, "虚妄之书", "", NULL, &layers[5]};
}

void cutscene_animation(SDL_Window *window, SDL_Renderer *renderer, PPT *ppt) {
    TTF_Font *textfont = TTF_OpenFont("./res/ys_zt.ttf", 30);
    TTF_Font *titlefont = TTF_OpenFont("./res/ys_zt.ttf", 70);
    SDL_Surface *textsurface, *titlesurface;
    int t = 5;
    SDL_Event event;
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    printf("show ppt\n");
    while (t < 255) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                game_Quit(window, renderer);
            }
        }
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);
        SDL_RenderClear(renderer);
        draw_text_with_alpha(renderer, textfont, ppt->description, windowWidth / 2, 500, COLOR_BLACK, t);
        draw_text_with_alpha(renderer, titlefont, ppt->title, windowWidth / 2, 200, COLOR_BLACK, t);
        SDL_RenderPresent(renderer);
        t += 10;
        SDL_Delay(50);
    }
    printf("waiting\n");
    int quit = 1;
    while (quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                game_Quit(window, renderer);
            }
            if (event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONUP) {
                quit = 0;
            }
        }
        SDL_Delay(50);
    }
    printf("quit\n");
    while (t > 0) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                game_Quit(window, renderer);
            }
        }
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
        SDL_RenderClear(renderer);
        draw_text_with_alpha(renderer, textfont, ppt->description, windowWidth / 2, 500, COLOR_BLACK, t);
        draw_text_with_alpha(renderer, titlefont, ppt->title, windowWidth / 2, 200, COLOR_BLACK, t);
        SDL_RenderPresent(renderer);
        t -= 10;
        SDL_Delay(50);
    }
}

void free_layer(Layer *layer) {
    for (int i = 0; i < layer->length; i++) {
        for (int j = 0; j < layer->line_num[i]; j++) {
            free(layer->nodes[i][j]);
        }
    }
}

NodeType random_choice(int probabilities[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += probabilities[i];
    }

    int random = rand() % total;
    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += probabilities[i];
        if (random < sum) {
            return (NodeType) (i + 1);  // 1到9之间
        }
    }
    return FIGHT;  // 默认返回FIGHT
}

// 初始化一般层的节点
Node *create_node(NodeType type) {
    Node *new_node = malloc(sizeof(Node));
    new_node->type = type;
    new_node->nxt_num = 0;
    for (int i = 0; i < MAX_WIDTH; i++) {
        new_node->nxt[i] = NULL;
    }
    return new_node;
}

void init_layer(Layer *layer, int layer_idx) {

    // 随机生成每列的节点数（长度）
    for (int i = 1; i < layer->length; i++) {
        layer->line_num[i] = 1 + rand() % (layer->width);  // 每列有 1 到 3 个节点
    }
    layer->line_num[0] = 1;
    layer->line_num[layer->length - 1] = 1;
    // 生成每列的节点
    for (int col = 1; col <= layer->length - (layer_idx == 3 ? 3 : 2); col++) {
        for (int row = 0; row < layer->line_num[col]; row++) {
            // 确保最后一列才有 DECISION 类型节点
            NodeType type = random_choice(layer_probabilities[layer_idx], 9);
            layer->nodes[col][row] = create_node(type);
        }
    }

    // 设置特殊节点：起点和终点
    switch (layer_idx) {
        case 0:
            layer->nodes[0][0] = create_node(EMERGENCY);
            layer->nodes[0][0]->nxt_num = layer->line_num[1];
            for (int i = 0; i < layer->line_num[1]; i++) {
                layer->nodes[0][0]->nxt[i] = layer->nodes[1][i];
            }
            layer->nodes[layer->length - 1][0] = create_node(DECISION);
            layer->nodes[layer->length - 1][0]->nxt_num = 0;
            layer->nodes[layer->length - 1][0]->nxt[0] = NULL;
            break;
        case 1:
            layer->nodes[0][0] = create_node(FIGHT);
            layer->nodes[0][0]->nxt_num = layer->line_num[1];
            for (int i = 0; i < layer->line_num[1]; i++) {
                layer->nodes[0][0]->nxt[i] = layer->nodes[1][i];
            }
            layer->nodes[layer->length - 1][0] = create_node(SHOP);
            layer->nodes[layer->length - 1][0]->nxt_num = 0;
            layer->nodes[layer->length - 1][0]->nxt[0] = NULL;
            break;
        case 2:
            layer->nodes[0][0] = create_node(REWARD);
            layer->nodes[0][0]->nxt_num = layer->line_num[1];
            for (int i = 0; i < layer->line_num[1]; i++) {
                layer->nodes[0][0]->nxt[i] = layer->nodes[1][i];
            }
            layer->nodes[layer->length - 1][0] = create_node(BOSS);
            layer->nodes[layer->length - 1][0]->nxt_num = 0;
            layer->nodes[layer->length - 1][0]->nxt[0] = NULL;
            break;
        case 3:
            layer->nodes[0][0] = create_node(EMERGENCY);
            layer->nodes[0][0]->nxt_num = layer->line_num[1];
            for (int i = 0; i < layer->line_num[1]; i++) {
                layer->nodes[0][0]->nxt[i] = layer->nodes[1][i];
            }
            layer->nodes[layer->length - 2][0] = create_node(BOSS);
            layer->line_num[layer->length - 2] = 1;
            layer->nodes[layer->length - 1][0] = create_node(DECISION);
            layer->nodes[layer->length - 2][0]->nxt_num = 1;
            layer->nodes[layer->length - 2][0]->nxt[0] = layer->nodes[layer->length - 1][0];
            layer->nodes[layer->length - 1][0]->nxt_num = 0;
            layer->nodes[layer->length - 1][0]->nxt[0] = NULL;
            break;
        case 4:
            layer->nodes[0][0] = create_node(UNEXPECTEDLY);
            layer->nodes[0][0]->nxt_num = layer->line_num[1];
            for (int i = 0; i < layer->line_num[1]; i++) {
                layer->nodes[0][0]->nxt[i] = layer->nodes[1][i];
            }
            layer->nodes[layer->length - 1][0] = create_node(BOSS);
            layer->nodes[layer->length - 1][0]->nxt_num = 0;
            layer->nodes[layer->length - 1][0]->nxt[0] = NULL;
            break;
    }
    int tail = layer->length - (layer_idx == 3 ? 3 : 2);
    for (int i = 0; i < layer->line_num[tail]; i++) {
        layer->nodes[tail][i]->nxt_num = 1;
        layer->nodes[tail][i]->nxt[0] = layer->nodes[tail + 1][0];
    }
    for (int i = 1; i < tail; i++) {
        int x = 0, y = 0, size;
        for (int j = 0; j < layer->line_num[i]; j++) {
            size = layer->line_num[i + 1] - 1 - y;
            if (size > 0) {
                y = y + rand() % (size + 1);
            }
            if (j == layer->line_num[i] - 1 && y < layer->line_num[i + 1] - 1) {
                y = layer->line_num[i + 1] - 1;
            }
            layer->nodes[i][j]->nxt_num = y - x + 1;
            for (int k = x; k <= y; k++) {
                layer->nodes[i][j]->nxt[k - x] = layer->nodes[i + 1][k];
            }
            x = y;
        }
    }
    layer->head = layer->nodes[0][0];
    layer->tail = layer->nodes[layer->length - 1][0];
}

void init_layer_six(Layer *layer) {
    layer->width = 1;
    layer->length = 4;
    layer->num = 6;
    for (int i = 0; i < 4; i++) {
        layer->line_num[i] = 1;
    }
    layer->nodes[0][0] = create_node(SHOP);
    layer->nodes[1][0] = create_node(EMERGENCY);
    layer->nodes[2][0] = create_node(SAFE_HOUSE);
    layer->nodes[3][0] = create_node(BOSS);
    layer->nodes[0][0]->nxt_num = 1;
    layer->nodes[0][0]->nxt[0] = layer->nodes[1][0];
    layer->nodes[1][0]->nxt_num = 1;
    layer->nodes[1][0]->nxt[0] = layer->nodes[2][0];
    layer->nodes[2][0]->nxt_num = 1;
    layer->nodes[2][0]->nxt[0] = layer->nodes[3][0];
    layer->nodes[3][0]->nxt_num = 0;
    layer->nodes[3][0]->nxt[0] = NULL;
    layer->head = layer->nodes[0][0];
    layer->tail = layer->nodes[3][0];

}

void print_layer(Layer *layer) {
    for (int i = 0; i < layer->length; i++) {
        printf("line:%d num:%d\n", i, layer->line_num[i]);
        for (int j = 0; j < layer->line_num[i]; j++) {
            printf("type:%d nxt_num:%d\n", layer->nodes[i][j]->type, layer->nodes[i][j]->nxt_num);
            for (int k = 0; k < layer->nodes[i][j]->nxt_num; k++) {
                printf("%d\n", layer->nodes[i][j]->nxt[k]->type);
            }
        }
    }
}

void init_every_layer() {
    srand(time(NULL));

    layers[0] = (Layer) {3, 4, 1};
    layers[1] = (Layer) {3, 5, 2};
    layers[2] = (Layer) {4, 6, 3};
    layers[3] = (Layer) {4, 7, 4};
    layers[4] = (Layer) {4, 7, 5};
    // 初始化前五层
    for (int i = 0; i < MAX_LAYERS - 1; i++) {
        init_layer(&layers[i], i);
    }

    // 初始化第六层（专门处理）
    init_layer_six(&layers[5]);

}

void init_map_printer(Layer *layer) {
    int i, j, size;
    int now_x = 200, step_x = 500, now_y, step_y;
    for (i = 0; i < layer->length; i++) {
        size = layer->line_num[i];
        now_y = windowHeight / 2;
        if (size == 3) {
            step_y = windowHeight / 4;
            now_y -= step_y;
        } else if (size == 2) {
            step_y = windowHeight / 3;
            now_y -= step_y / 2;
        } else if (size == 4) {
            step_y = windowHeight / 5;
            now_y -= step_y * 1.5;
        } else {
            step_y = 0;
        }
        for (j = 0; j < layer->line_num[i]; j++) {
            layer->nodes[i][j]->x = now_x;
            layer->nodes[i][j]->y = now_y;
            now_y += step_y;
        }
        now_x += step_x;
    }
}

void print_map(SDL_Window *window, SDL_Renderer *renderer, Layer *layer, int x) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    int i, j, k;
    for (i = 0; i < layer->length; i++) {
        for (j = 0; j < layer->line_num[i]; j++) {
            for (k = 0; k < layer->nodes[i][j]->nxt_num; k++) {
//                thickLineRGBA(renderer, 100, 100, 700, 500, 10, 255, 0, 0, 255);
                SDL_RenderDrawLine(renderer, layer->nodes[i][j]->x + x, layer->nodes[i][j]->y,
                                   layer->nodes[i][j]->nxt[k]->x + x, layer->nodes[i][j]->nxt[k]->y);
//                SDL_RenderPresent(renderer);
            }
        }
    }
    for (i = 0; i < layer->length; i++) {
        for (j = 0; j < layer->line_num[i]; j++) {
            SDL_Rect dstRect = {layer->nodes[i][j]->x + x, layer->nodes[i][j]->y};
            SDL_QueryTexture(node_texture[layer->nodes[i][j]->type], NULL, NULL, &dstRect.w, &dstRect.h);
            dstRect.x -= dstRect.w / 2;
            dstRect.y -= dstRect.h / 2;
            SDL_RenderCopy(renderer, node_texture[layer->nodes[i][j]->type], NULL, &dstRect);
//            SDL_RenderPresent(renderer);
        }
    }
}

SDL_Rect nodes_rect(Node *node, int x) {
    SDL_Rect rect = {node->x + x, node->y};
    SDL_QueryTexture(node_texture[node->type], NULL, NULL, &rect.w, &rect.h);
    rect.w += 20;
    rect.h += 20;
    rect.x -= rect.w / 2;
    rect.y -= rect.h / 2;
    return rect;
}

bool mouse_in_rect(SDL_Rect rect, int mouse_x, int mouse_y) {
    if (mouse_x >= rect.x && mouse_x <= rect.x + rect.w &&
        mouse_y >= rect.y && mouse_y <= rect.y + rect.h) {
        return true;
    }
    return false;
}

void draw_nodes(SDL_Renderer *renderer, Node *node, SDL_Color Color, int x) {
    draw_rectangle(renderer, nodes_rect(node, x), Color);
}

void print_nodes(SDL_Renderer *renderer, Node *node, Layer *layer, int x) {
    if (node == NULL) {
        draw_nodes(renderer, layer->head, COLOR_GOLD, x);
    } else {
        draw_nodes(renderer, node, COLOR_BLACK, x);
        for (int i = 0; i < node->nxt_num; i++) {
            draw_nodes(renderer, node->nxt[i], COLOR_GOLD, x);
        }
    }
}


void
check_choose_nodes(SDL_Window *window, SDL_Renderer *renderer, Node *now_node, Layer *layer, int mouse_x, int mouse_y,
                   int x,
                   Player *player) {
    if (now_node == NULL) {
        if (mouse_in_rect(nodes_rect(layer->head, x), mouse_x, mouse_y)) {
            goin_nodes(window, renderer, layer->head, layer, player);
        }
    } else {
        for (int i = 0; i < now_node->nxt_num; i++) {
            if (mouse_in_rect(nodes_rect(now_node->nxt[i], x), mouse_x, mouse_y)) {
                goin_nodes(window, renderer, now_node->nxt[i], layer, player);
                return;
            }
        }
    }
}

extern Node *last_node;

extern int fight_in_map[7][2];
extern Fight fight_map[7][2][10];
extern Fight boss[3][3];
extern Collection main_collection[6][10];

Fight *generate_boss(Layer *layer) {
    int x = layer->num - 2, y;
    if (layer->num == 2) {
        if (main_collection[5][3].get) {
            y = 2;
        } else {
            y = generate_random(0, 1);
        }
    } else if (layer->num == 2) {
        if (main_collection[5][4].get) {
            y = 1;
        } else {
            y = 0;
        }
    } else {
        if (main_collection[5][3].get) {
            y = 1;
        } else {
            y = generate_random(0, 1);
        }
    }
    return &boss[x][y];
}

extern Events Safe_house, decitions[2], events_rewards;
extern int main_event_num;
extern Events main_event[10];
extern Rewards rewards;

void goin_nodes(SDL_Window *window, SDL_Renderer *renderer, Node *node, Layer *layer, Player *player) {
    printf("goin!\n");
    last_node = node;
    if (layer->num == 2) {
        if (node->type != 1 && node->type != 2 && node->type != 3) {
            player->coin -= generate_random(10, 20);
            if (player->coin < 0) {
                player->coin = 0;
            }
        }
    }
    if (layer->num == 3) {
        if (node->type != 1 && node->type != 2 && node->type != 3) {
            player->extra_damage++;
            if (player->extra_damage > 3) {
                player->extra_damage = 3;
            }
        } else {
            player->extra_damage--;
            if (player->extra_damage < -3) {
                player->extra_damage = -3;
            }
        }
    }
    if (layer->num == 4) {
        if (generate_random(1, 2) == 1) {
            player_get_hp(player, generate_random(5, 30));
        } else {
            player->hp -= generate_random(1, 20);
            if (player->hp <= 0) {
                player->hp = 1;
            }
        }
    }
    switch (node->type) {
        case 1:
            game_fight(window, renderer,
                       &fight_map[layer->num][0][generate_random(0, fight_in_map[layer->num][0] - 1)], player, 0,
                       layer->num);
            break;
        case 2:
            game_fight(window, renderer, &fight_map[layer->num][1][generate_random(0, fight_in_map[layer->num][1] - 1)],
                       player, 1, layer->num);
            break;
        case 3:
            game_fight(window, renderer, generate_boss(layer), player, 1, layer->num);
            break;
        case 4:
            enter_events(window, renderer, player, &main_event[generate_random(0, main_event_num - 1)]);
            break;
        case 5:
            init_rewards();
            enter_rewards(window, renderer, player, &rewards);
            break;
        case 8:
            init_decition();
            if (layer->num == 1) {
                enter_events(window, renderer, player, &decitions[0]);
            }
            break;
        case 9:
            init_safehouse();
            enter_events(window, renderer, player, &Safe_house);
            break;
    }
}