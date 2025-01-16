//
// Created by 48811 on 24-12-29.
//

#ifndef SLAYTHESPIRE_SAVES_H
#define SLAYTHESPIRE_SAVES_H

#define PLAYER_INFO_FILE "player_info.txt"

typedef struct {
    int firstTime;
    int Character_locked[3];
    int reward;
} PlayerInfo;

extern PlayerInfo playerInfo;

void savePlayerInfo(PlayerInfo *info);


PlayerInfo loadPlayerInfo();

void PleyInfo_reset();

#endif //SLAYTHESPIRE_SAVES_H
