//
// Created by 48811 on 25-1-24.
//

#include "events.h"

extern Events Safe_house, decitions[2], rewards;
extern int main_event_num;
extern Events main_event[10];

void safe_house_sleep(Player *player) {
    player_get_hp(player, player->maxhp * 0.2);
}

void safe_house_recover(Player *player) {
    player->hp = player->maxhp;
    player->coin /= 2;
}

void safe_house_coin(Player *player) {
    if (generate_random(1, 1000) == 234) {
        player->coin += 999;
        Safe_house.choice_end[2] = "你发现了隐藏的巨款，真是意外之喜";
    } else {
        player->coin += generate_random(50, 200);
    }
}

void init_safehouse() {
    Safe_house.name = "安全屋";
    Safe_house.discribe = "抓紧时间整理物资、放松身心、规划路线，新的挑战很快就到。";
    Safe_house.choice_num = 3;
    Safe_house.choice_name[0] = "好好休息";
    Safe_house.choice_discribe[0] = "回复20%生命值";
    Safe_house.effect[0] = safe_house_sleep;
    Safe_house.choice_end[0] = "你好好的睡了一觉";
    Safe_house.choice_name[1] = "进行治疗";
    Safe_house.choice_discribe[1] = "花费50%金币，恢复全部生命值";
    Safe_house.effect[1] = safe_house_recover;
    Safe_house.choice_end[1] = "抛去了不用的东西，你感到浑身轻松";
    Safe_house.choice_name[2] = "获取补给";
    Safe_house.choice_discribe[2] = "获得一些金币";
    Safe_house.choice_end[2] = "你获得了一些补给";
    Safe_house.effect[2] = safe_house_coin;
}

void Wings_Statue_wish(Player *player) {
    delete_card_from_bag(player, generate_random(0, player->sum_deck_size - 1));
}

void Wings_Statue_destroy(Player *player) {
    player->coin += generate_random(50, 80);
}

void Wings_Statue_leave(Player *player) {
    return;
}

void init_events() {
    main_event_num = 1;
    main_event[0] = (Events) {"翅膀雕像",
                              "在形状不同的巨石之间，你看见一尊做工精细的翅膀形状的蓝色雕像。你可以看见雕像的裂缝中有金币掉出来。或许里面还有更多……",
                              3, "祈祷", "摧毁", "离开", "", "从你的牌组中 随机 移除一张牌。获得 7 生命",
                              "获得 50-80 金币", "", "",
                              "你曾听人提起过一个崇拜巨大鸟类的邪教。当你跪下祷告的时候，你开始觉得有一些头晕……过了一会儿，你醒了过来，感觉脚步有点变轻了。",
                              "你使出浑身的力气开始砸雕像。很快它就彻底裂开，里面是一大堆金币。你把钱尽可能收集起来，重新上路。",
                              "这个雕像让你觉得有点不安。你决定不要去惊扰它，直接离开了。"
                              "", "", Wings_Statue_wish, Wings_Statue_destroy, Wings_Statue_leave, NULL
    };
}