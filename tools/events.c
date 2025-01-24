//
// Created by 48811 on 25-1-24.
//

#include "events.h"

extern Events Safe_house, decitions[2], rewards;
extern Events main_event[10];

void init_events() {
    Safe_house.name = "安全屋";
    Safe_house.discribe = "抓紧时间整理物资、放松身心、规划路线，新的挑战很快就到。";
    Safe_house.choice_num = 3;
    Safe_house.choice_name[0] = "好好休息";
    Safe_house.choice_discribe[0] = "回复20%生命值";
    Safe_house.choice_end[0] = "你好好的睡了一觉";
    Safe_house.choice_name[1] = "整理物资";
    Safe_house.choice_discribe[1] = "删除一张卡牌";
    Safe_house.choice_end[1] = "抛去了不用的东西，你感到浑身轻松";
    Safe_house.choice_name[2] = "获取补给";
    Safe_house.choice_discribe[2] = "获得一些金币";
    Safe_house.choice_end[2] = "你获得了一些补给";
}