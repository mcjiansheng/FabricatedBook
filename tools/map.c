//
// Created by 48811 on 25-1-16.
//

#include "map.h"

extern PPT first_floor, second_floor[2], third_floor[2], forth_floor[2], fifth_floor[2], small_path, sixth_floor[2];

void wilderness(int length, int width, Map *map) {
    Node *new_node = malloc(sizeof(Node));
    new_node->type = 1;
    map->head = new_node;
    Node *ptr;
    int last_wid;
    Node **last_nodes;
    for (int i = 2; i <= width; i++) {
        int wid = generate_random(2, 3);
        Node *new_nodes = malloc(sizeof(Node) * wid);
        if (i == 2) {
            new_node->generate_nxt = new_nodes;
        } else {
            ptr->generate_nxt = new_nodes;
        }
        if (i == 2) {
            new_node->nxt_num = wid;
            new_node->nxt = malloc(wid * sizeof(Node *));
        }
        for (int j = 0; j < wid; j++) {
            if (j > 0) {
                (*(new_nodes + (j - 1) * sizeof(Node))).generate_nxt = new_nodes + j * sizeof(Node);
            }
            Node *now_node = new_nodes + j * sizeof(Node);
            int num = generate_random(1, 10);
            if (num >= 1 && num <= 6) {
                now_node->type = 1;
            } else if (num == 7) {
                now_node->type = 2;
            } else {
                now_node->type = 4;
            }
            if (i == 2) {
                new_node->nxt[j] = now_node;
            }
        }
        ptr = new_node + (wid - 1) * sizeof(Node);
        if (i > 2) {
            for (int j = 0; j < last_wid; j++) {
                last_nodes[j]->nxt_num = generate_random(1, wid);
                int a[10];
                for (int k = 0; k < wid; k++) {
                    a[k] = 1;
                }
                for (int k = 0; k < last_nodes[j]->nxt_num; k++) {
                    int x_nxt = generate_random(0, wid - 1);
                    while (!a[x_nxt]) {
                        x_nxt = generate_random(0, wid - 1);
                    }
                    a[x_nxt] = 0;
                    last_nodes[j]->nxt[k] = new_nodes + x_nxt * sizeof(Node);
                }
            }
//            free(last_nodes);
        }
        last_wid = wid;
        last_nodes = malloc(wid * sizeof(Node *));
        for (int j = 0; j < wid; j++) {
            last_nodes[j] = new_nodes + j * sizeof(Node);
        }
        map->size[i] = last_wid;
        map->nodes[i] = last_nodes;
    }
    Node *tail_node = malloc(sizeof(Node));
    tail_node->type = 8;
    tail_node->nxt_num = 0;
    tail_node->nxt = NULL;
    tail_node->generate_nxt = NULL;
    for (int i = 0; i < last_wid; i++) {
        last_nodes[i]->nxt_num = 1;
        last_nodes[i]->nxt[0] = tail_node;
    }
//    free(last_nodes);
    map->tail = tail_node;
}

void init_map(PPT *ppt) {
    ppt->map = malloc(sizeof(Map));
    switch (ppt->num) {
        case 1:
            ppt->map = (Map) {4, 3};
            ppt->map->generate = wilderness;
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
    }
}
