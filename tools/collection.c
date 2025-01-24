//
// Created by 48811 on 25-1-24.
//

#include "collection.h"

extern int main_collection_num[6];
extern Collection main_collection[6][10];

void init_collection() {
    main_collection_num[0] = 2;
    main_collection[0][0] = (Collection) {"热水壶", "生命值上限+5", 0, 0};
    main_collection[0][1] = (Collection) {"古旧钱币", "立即获得30金币", 0, 0};
    main_collection_num[1] = 1;
    main_collection[1][0] = (Collection) {"无暇宝玉", "立即获得100金币", 1, 0};
    main_collection_num[2] = 1;
    main_collection[2][0] = (Collection) {"微缩舞台模型", "战斗开始时获得3能量，额外抽2张牌", 2, 0};
    main_collection_num[3] = 1;
    main_collection[3][0] = (Collection) {"国王的长枪", "生命值低于10%时，造成伤害+50%", 3, 0};
    main_collection_num[4] = 1;
    main_collection[4][0] = (Collection) {"金酒之杯", "每拥有10金币，造成伤害+8%", 4, 0};
}

bool all_collections_had() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < main_collection_num[i]; j++) {
            if (!main_collection[i][j].get) {
                return false;
            }
        }
    }
    return true;
}
