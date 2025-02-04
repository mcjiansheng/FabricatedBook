//
// Created by 48811 on 25-1-24.
//

#include "collection.h"

extern int main_collection_num[7];
extern Collection main_collection[7][10];

void init_collection() {
    main_collection_num[0] = 10;
    main_collection[0][0] = (Collection) {"热水壶", "生命值上限+5", 0, 0};
    main_collection[0][1] = (Collection) {"古旧钱币", "立即获得30金币", 0, 0};
    main_collection[0][2] = (Collection) {"古怪的长笛", "战斗开始时获得1能量", 0, 0};
    main_collection[0][3] = (Collection) {"一份演讲稿", "获得一张牌", 0, 0};
    main_collection[0][4] = (Collection) {"幸运硬币", "金币+1\n玩家变得幸运一点", 0, 0};
    main_collection[0][5] = (Collection) {"A级连招", "造成伤害+5%", 0, 0};
    main_collection[0][6] = (Collection) {"靶子", "敌方单位受到伤害有概率+10%", 0, 0};
    main_collection[0][7] = (Collection) {"美味蟹堡", "战斗胜利后回复10% 生命值", 0, 0};
    main_collection[0][8] = (Collection) {"探灵伯爵", "战斗胜利后获得藏品概率增加", 0, 0};
    main_collection[0][9] = (Collection) {"年度最佳", "角色获得lgbt元素", 0, 0};
    main_collection_num[1] = 7;
    main_collection[1][0] = (Collection) {"无暇宝玉", "立即获得100金币", 1, 0};
    main_collection[1][1] = (Collection) {"至宝指环", "战斗获得金币+50%", 1, 0};
    main_collection[1][2] = (Collection) {"石像鬼塑像", "生命上限+10", 1, 0};
    main_collection[1][3] = (Collection) {"饭碗", "回复25%生命值", 1, 0};
    main_collection[1][4] = (Collection) {"捡来的存折", "每次进入商店获得25块", 1, 0};
    main_collection[1][5] = (Collection) {"吸血鬼的尖牙", "每使用1张牌，回复1点生命值", 1, 0};
    main_collection[1][6] = (Collection) {"葵花宝典", "角色造成伤害有概率+80%", 0, 0};
    main_collection_num[2] = 6;
    main_collection[2][0] = (Collection) {"微缩舞台模型", "战斗开始时获得3能量\n额外抽2张牌", 2, 0};
    main_collection[2][1] = (Collection) {"道具箱", "获得三张牌", 2, 0};
    main_collection[2][2] = (Collection) {"投币玩具", "每拥有10金币\n造成伤害+3%", 2, 0};
    main_collection[2][3] = (Collection) {"洗手液", "受治疗效果+20%", 2, 0};
    main_collection[2][4] = (Collection) {"悬丝木偶", "敌人的中毒和凋零伤害+10%", 2, 0};
    main_collection[2][5] = (Collection) {"5A级连招", "造成伤害+25%", 2, 0};

    main_collection_num[3] = 8;
    main_collection[3][0] = (Collection) {"国王的长枪", "生命值低于10%时\n造成伤害+50%", 3, 0};
    main_collection[3][1] = (Collection) {"国王的铠甲", "生命值低于10%时\n每回合获得10点护盾\n护盾获取量+50%", 3, 0};
    main_collection[3][2] = (Collection) {"国王的水晶", "战斗胜利时\n若生命值高于10%\n则损失5点生命值\n获得额外20金币",
                                          3, 0};
    main_collection[3][3] = (Collection) {"刀光剑影", "每拥有一个负面效果\n造成伤害+20%",
                                          3, 0};
    main_collection[3][4] = (Collection) {"霜之哀伤", "每通过1场战斗造成伤害+8%",
                                          3, 0};
    main_collection[3][5] = (Collection) {"窥秘之眼", "敌方受到伤害+40%",
                                          3, 0};
    main_collection[3][6] = (Collection) {"“我来助你”", "回合开始时\n所有敌人受到2点伤害", 3,
                                          0};
    main_collection[3][7] = (Collection) {"蓝卡坞安全衣", "每拥有一个负面藏品\n受到伤害-10%", 3, 0};

    main_collection_num[4] = 6;
    main_collection[4][0] = (Collection) {"金酒之杯", "每拥有10金币\n造成伤害+8%", 4, 0};
    main_collection[4][1] = (Collection) {"老蒲扇", "每拥有一张卡牌\n 造成伤害+1%", 4, 0};
    main_collection[4][2] = (Collection) {"迷迭香小队", "敌人造成伤害-30%\n造成伤害+30%", 4, 0};
    main_collection[4][3] = (Collection) {"苍白花冠", "受到治疗+35%", 4, 0};
    main_collection[4][4] = (Collection) {"“凋零风暴”", "敌人受到的凋零伤害+50%\n每回合额外结算一次凋零伤害", 4, 0};
    main_collection[4][5] = (Collection) {"“止戈”", "受到伤害变为70%", 4, 0};
    main_collection_num[5] = 7;
    main_collection[5][0] = (Collection) {"背叛", "1-4层造成伤害+20%\n第五层敌人血量+20%\n战斗进入不同结局", 5, 0};
    main_collection[5][1] = (Collection) {"仇恨", "1-4层造成伤害-20%\n第五层敌人血量-20%\n战斗进入不同结局", 5, 0};
    main_collection[5][2] = (Collection) {"“我来助你”", "回合开始时\n所有敌人受到2点伤害", 5,
                                          0};
    main_collection[5][3] = (Collection) {"“复仇者”", "造成伤害有概率增加30%\n险路恶敌中出现其他敌人", 5,
                                          0};
    main_collection[5][4] = (Collection) {"“巴别塔”", "团结起来，不惜一切\n险路恶敌中出现其他敌人", 5,
                                          0};
    main_collection[5][5] = (Collection) {"“集权”", "进入一个战斗节点\n造成伤害+5%", 5,
                                          0};
    main_collection[5][6] = (Collection) {"“寡头”", "每进入一个非战斗节点\n获得20金币", 5,
                                          0};
    main_collection_num[6] = 3;
    main_collection[6][0] = (Collection) {"海神的代谢", "敌人生命值+25%", 6,
                                          0};
    main_collection[6][1] = (Collection) {"宽容", "敌方造成伤害+20%", 6, 0};
    main_collection[6][2] = (Collection) {"谦虚", "生命值-30%", 6, 0};
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
