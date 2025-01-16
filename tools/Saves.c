//
// Created by 48811 on 24-12-29.
//

#include "Saves.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const PlayerInfo reset_playerinfo = {.firstTime=0, .Character_locked={1, 0, 0}, .reward=1};

// 保存玩家信息到文件
void savePlayerInfo(PlayerInfo *info) {
    FILE *file = fopen(PLAYER_INFO_FILE, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    fprintf(file, "%d\n", info->firstTime);
    for (int i = 0; i < 3; i++) {
        fprintf(file, "%d ", info->Character_locked[i]);
    }
    fprintf(file, "\n%d\n", info->reward);
    printf("Playerinfo save success!\n");
    fclose(file);
}

void PleyInfo_reset() {
    savePlayerInfo(&reset_playerinfo);
}

// 从文件读取玩家信息
PlayerInfo loadPlayerInfo() {
    PlayerInfo info = reset_playerinfo;  // 默认首次进入
    FILE *file = fopen(PLAYER_INFO_FILE, "r");
    if (file != NULL) {
        fscanf(file, "%d\n", &info.firstTime);
        for (int i = 0; i < 3; i++) {
            fscanf(file, "%d", &info.Character_locked[i]);
        }
        fscanf(file, "%d", &info.reward);
        fclose(file);
    }
    return info;
}