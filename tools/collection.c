//
// Created by 48811 on 25-1-24.
//

#include "collection.h"

extern int main_collection_num[6];
extern Collection main_collection[6][10];

void init_collection() {
    main_collection_num[0] = 4;
    main_collection[0][0] = (Collection) {"热水壶", "生命值上限+5", 0, 0};
    main_collection[0][1] = (Collection) {"古旧钱币", "立即获得30金币", 0, 0};
    main_collection[0][2] = (Collection) {"古怪的长笛", "战斗开始时获得1能量", 0, 0};
    main_collection[0][3] = (Collection) {"一份演讲稿", "获得一张牌", 0, 0};
    main_collection_num[1] = 3;
    main_collection[1][0] = (Collection) {"无暇宝玉", "立即获得100金币", 1, 0};
    main_collection[1][1] = (Collection) {"至宝指环", "战斗获得金币+50%", 1, 0};
    main_collection[1][2] = (Collection) {"石像鬼塑像", "生命上限+10", 1, 0};

    main_collection_num[2] = 2;
    main_collection[2][0] = (Collection) {"微缩舞台模型", "战斗开始时获得3能量\n额外抽2张牌", 2, 0};
    main_collection[2][1] = (Collection) {"道具箱", "获得三张牌", 2, 0};
    main_collection_num[3] = 3;
    main_collection[3][0] = (Collection) {"国王的长枪", "生命值低于10%时\n造成伤害+50%", 3, 0};
    main_collection[3][1] = (Collection) {"国王的铠甲", "生命值低于10%时\n每回合获得10点护盾\n护盾获取量+50%", 3, 0};
    main_collection[3][2] = (Collection) {"国王的水晶", "战斗胜利时\n若生命值高于10%\n则损失5点生命值\n获得额外20金币",
                                          3, 0};
    main_collection_num[4] = 1;
    main_collection[4][0] = (Collection) {"金酒之杯", "每拥有10金币\n造成伤害+8%", 4, 0};
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
