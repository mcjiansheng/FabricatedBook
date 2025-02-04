# Fabricated Book

> Code by xht 2025/1/17

For the CPL final project at Nanjing University: Slay the Spire

* * *

# 杀戮尖塔详情文档

## 节点类型

战斗节点：  
1作战fight：常规战斗节点，胜利获得金币和卡牌  
2紧急作战Emergency：有一定难度增益的战斗节点，胜利获得藏品，金币和卡牌  
3险路恶敌boss：层低的强大boss

事件节点：  
4不期而遇unexpectedly：未知节点，里面有未知的事件  
5得偿所愿reward：选择藏品  
6诡异行商shop：商店  
7命运抉择decision：根据选择，更改探索方向  
8安全屋safe house ：获得补给

## 地图结构

1. 荒野：长度4 宽3 起点固定为一个战斗节点，结尾固定为一个命运抉择。  
   节点刷新概率：战斗60% 紧急作战10% 不期而遇30%  
   无环境效果

2. 森林：长度5 宽3 起点固定为一个战斗节点，结尾固定为一个商店。  
   节点刷新概率：战斗40% 紧急作战20% 不期而遇10% 安全屋10% 诡异行商10% 得偿所愿10%（后面同理）  
   环境效果：进入非战斗节点时金币损失金币，战斗获得金币数量增加

3. 诡异秘林:长度6 宽4 起点固定为一个得偿所愿，结尾固定为一个BOSS战  
   环境效果：每进入一个战斗节点，造成伤害-1，每进入一个非战斗节点，造成伤害+1，至多$\pm 3$

4. 迷雾:长度7 宽4 起点固定为一个紧急作战，结尾固定为一个BOSS战，然后是一个命运抉择  
   环境效果：每次前进都有概率回复或损失生命值

5. 高塔：长度7 宽4 起点固定为一个不期而遇，结尾固定为一个BOSS战  
   无环境效果

## 卡牌

### 战士 ：战斗胜利回复6-12点生命值 生命值上限：80

- 攻击attack 造成6点伤害 消耗1能量 价值0
- 防御defense 获得6点格挡 消耗1能量 价值0
- 痛击 painful blow 造成8点伤害，提供2点易伤 消耗2能量 价值1
- 横扫sweep 攻击 对所有单位造成5点伤害 消耗1能量 价值1
- 奇袭ambush 技能 造成5点伤害，并造成3点虚弱 消耗0能量 消耗（使用后直接消失，不进入弃牌堆） 价值1
- 反击counterattack 技能 根据格挡值造成伤害 消耗1能量 价值1
- 强力击powerful strike 攻击 造成10点伤害，手中每有一张攻击牌，使伤害增加3 消耗2能量 价值1
- 装甲armorer 装备 使用后使得我方在该场战斗中格挡值不再在回合结束时消失（buff：armor） 消耗 消耗 2 价值2
- 致命节奏deadly tempo 攻击 造成7点伤害，每使用一次该牌，伤害+1 消耗1能量 价值1
- 底牌ACE 技能 抽5张牌 消耗0能量 消耗 价值2
- 搏命挣扎struggle desperately 技能 在接下来的3回合，玩家血量降为0也不会死亡(buff:undead)，同时每回合额外获得2能量，但是3回合结束之后直接死亡
  消耗0能量 消耗 价值2
- 兴奋excited 技能 清除所有的负面效果 消耗1能量 消耗 价值2
- 治疗 技能 回复10生命值 消耗1能量 消耗 价值1
- 致命一击critical hit 攻击 造成 30点伤害 消耗3能量 价值2
- 沸血 技能 boiling blood 获得2回合力量，随机一张攻击牌 消耗0 价值1
- 肘击 攻击elbowing 造成6点伤害，25%造成1回合眩晕 消耗1 价值1
- 剑刃风暴 Bladestorm 攻击 对所有敌人造成3*3点伤害 消耗2 价值2
- 哈撒给 hasaki 攻击 造成4点伤害3回合易碎 消耗0 价值1
- 龙牙 Dragon Fang 攻击 造成造成9点伤害,若敌方生命值小于30伤害+5 消耗1 价值1
- 英雄登场hero entrance 技能 对所有敌人造成12点伤害，2回合脆弱和易碎，获得3点能量 消耗0 消耗 价值2
- 封尘绝念斩Fate_Sealed 攻击 对所有敌人造成16点伤害 消耗2 价值2
- 腐化 Corrupt攻击 造成4点凋零并引爆1次凋零 消耗1 价值1
- 瘟疫plague 技能 对所有敌人造成6点中毒，并使所有敌人中毒层数翻倍 消耗 消耗2 价值2
- 淬毒Poisoned 攻击 对敌人造成5*2点伤害，每次攻击有50%概率附加中毒 消耗1 价值2
- 弱点weakness 技能 造成1回合脆弱和易碎 消耗0 价值1
- 歪瓜Cheat 获得30点格挡 消耗0 消耗 价值2
- 爆裂黎明Blast Dawn 技能 大彻大悟 对所有敌人造成6*10点伤害 消耗 消耗5 价值3
- 凛神斩Reckoning 攻击 对所有敌人造成3点伤害，命中每个敌人提供5格挡 消耗1 价值1
- 肉斩骨断 攻击 对敌人造成5点伤害，每损失10生命值，伤害+3 消耗1 价值2
- 不屈Unyielding 防御 获得3点坚强，10点格挡 消耗2 价值1

## 效果(buff)

1.脆弱fragile：受到伤害增加25%  
2.易碎block_reduction：获得的格挡-50%  
3.抗性resistance：受到伤害减少 25%
4.坚强block_increase：获得格挡+50%  
5.虚弱weak：造成的减少25%  
6.力量strength：造成的伤害增加25%  
7.眩晕dizziness：下一回合无法行动  
8.中毒poisoning：回合开始时依据中毒层数受到数点伤害，中毒层数-1  
9.凋零withering：回合开始或受到特定技能会引爆，每次引爆伤害增加
技能中的效果：  
10.装甲armor  
11.不死 undead  
12.额外能量 extra_energy

## 药水

- 回血药水：回复10点生命值
- 攻击药水：对所有敌人造成10点伤害
- 护盾药水：获得30护盾
- 中毒药水：对所有敌人造成5点中毒
- 凋零药水：对所有敌人造成5点凋零并引爆一次
- 能量药水：获得三点能量，抽三张卡
- 碎盾药水：击碎所有敌人的护盾
- 眩晕药水：使所有敌人眩晕1回合
- 力量药水：获得5点力量
- 抗性药水：获得5点抗性

## 藏品

### 普通

- 热水壶：生命值上限+5
- 古旧钱币：立即获得30金币
- 古怪的长笛：战斗开始时获得1能量
- 一份演讲稿：获得一张牌
- 幸运硬币：金币+1，玩家变得幸运一点(无实际作用)
- A级连招：造成伤害+5%
- 靶子：敌方单位受到伤害有概率+10% (33%)
- 探灵伯爵：战斗胜利后获得藏品概率增加
- 年度最佳：角色获得lgbt元素（什么用都没有）

### 稀有

- 无暇宝玉：立即获得100金币
- 至宝指环：战斗获得金币+50%
- 石像鬼塑像：生命上限+10
- 饭碗：回复25%生命值
- 捡来的存折：每次进入商店获得25块
- 吸血鬼的尖牙：每使用1张牌，回复1点生命值
- 葵花宝典：角色造成伤害有概率+80%

### 史诗

- 微缩舞台模型：战斗开始时获得3能量，额外抽2张牌
- 道具箱：获得三张牌
- 投币玩具：每拥有10金币，造成伤害+3%
- 洗手液：受治疗效果+20%
- 悬丝木偶：敌人受到的中毒和凋零伤害+10%
- 5A级连招：造成伤害+25%

### 传说

- 国王的长枪：生命值低于10%时，造成伤害+50%
- 国王的铠甲：生命值低于10%时，每回合获得10点护盾且护盾获取量+50%
- 国王的水晶：战斗胜利时，若生命值高于10%，则损失5点生命值，获得额外20金币
- 刀光剑影：每拥有一个负面效果，造成伤害+20%
- 霜之哀伤：每通过1场战斗造成伤害+8%
- 窥秘之眼：敌方受到伤害+40%
- “我来助你”：回合开始时，所有敌人受到2点伤害
- 蓝卡坞安全衣：每拥有一个负面藏品，受到伤害-10%

### 神话

- 金酒之杯：每拥有10金币，造成伤害+8%
- 老蒲扇：每拥有一张卡牌，造成伤害+1%
- 迷迭香小队: 敌人造成伤害-30% 造成伤害+30%
- 苍白花冠：生命值回复量+35%
- “凋零风暴”：敌人受到的凋零伤害+50%，每回合额外结算一次凋零伤害
- 止戈，受到伤害变为70%

### 特殊藏品

- 背叛：1-4层造成伤害+20%，第五层敌人血量+20%，战斗进入不同结局
- 仇恨：1-4层造成伤害-20%，第五层敌人血量-20%，战斗进入不同结局
- “复仇者”：造成伤害有概率（三分之一）增加30%，险路恶敌中出现其他敌人（迷失的守林人）
- “巴别塔”：团结起来，不惜一切。险路恶敌中出现其他敌人
- “集权”：进入一个战斗节点，造成伤害+5%
- “寡头”：每进入一个非战斗节点，获得20金币

### 负面藏品

- 海神的代谢：敌人生命值+25%
- 宽容：敌方造成伤害+20%
- 谦虚：生命值-30%

## 敌人

### 荒野

#### 普通战斗

1.**拾荒者**:生命值45  
a.攻击造成2\*3点伤害（3点伤害攻击两次）(atk)  
b.使用简单的武器武装自己，接下来3回合获得力量(inc)  
c.攻击造成5点伤害，并使角色获得1回合易碎(atk)

2.**秃鹫\*3**:生命值25  
a.飞行，获得3点护盾  
b.啄，造成3点伤害(atk)  
c.俯冲，造成7点伤害
3.**盗贼\*2**:生命值35
A.攻击，造成2点伤害和3点中毒
b.攻击2，造成5点伤害和2脆弱
c.获得5点格挡

#### 紧急战斗

1.**拾荒者\*3**
2.**孤魂野鬼**:生命值40
a获得抗性和力量5点，获得10生命值
b攻击造成8*2点伤害，每次攻击50%造成1层凋零
c.使角色获得5回合脆弱和虚弱
d.攻击造成8点伤害，引爆凋零
E.获得10点护盾

### 森林

#### 普通战斗

1.**猎人**:生命值65
a.获得3回合力量和10格挡
b.造成2*5点伤害，每次攻击25%造成1层虚弱
c.造成9点伤害，获得3回合坚强
D.造成10点伤害，如果我方有格挡，伤害+5

2.**树人**：生命值 90
a.回合开始时获得3格挡（被动）
b.造成8点伤害，25%造成中毒
c.造成4*4点伤害，每次攻击50%造成1回合易碎
d,获得10点格挡，如果生命值小于30，获得无限的装甲（格挡不会消失）

3.**哥布林*2**:生命值60
a.战斗开始的前3回合获得力量，从第4回合开始获得虚弱（被动）
b.所有敌人回复5点生命值
c.攻击造成6点伤害，造成3层中毒
d.攻击造成8点伤害，并获得4点格挡

4.**史莱姆*3**:生命值40
A.获得8格挡
b.为全队提供3格挡
C.造成（2+50%格挡数）点伤害
D.为我方单位提供与自身格挡相同的格挡

#### 紧急战斗

1.**老猎人**:生命值95
a. 使角色获得3回合脆弱和易碎，造成3*5点伤害
b. 获得4回合力量和20点格挡
c. 造成2*7点伤害，每次攻击50%造成1层虚弱
d 造成12点伤害，获得2回合坚强

2.**哥布林统领**:生命值100
a.战斗开始的前5回合获得力量，从第6回合开始获得虚弱
c.攻击造成9点伤害，造成3层中毒
d.攻击造成8点伤害，并获得10点格挡
e.造成5*3点伤害，使我方单位获得2回合虚弱
f.获得10格挡，回复场上所有单位7点生命值

### 诡异秘林 （拥有森林全部小怪和精英怪）

#### 普通战斗

1.**腐尸**:生命值150
a.回合开始时回复5点生命值（被动）
b.攻击造成6点伤害2层中毒
c.攻击造成2*7点伤害
d.自己获得5点脆弱

#### 紧急战斗

1.**堕落守林人**:生命值100
a.自身获得脆弱（被动）
b.攻击造成12-20点伤害

#### 险路恶敌（BOSS）

1,**凋零之树**:生命值200
攻击有概率引爆凋零或附加凋零（被动）(25%)
A,回复10-25生命值
B,攻击造成15伤害，附加3层凋零
C,造成4*7点伤害，获得5格挡
D,引爆玩家的凋零，同时自身获得3点抗性
E,攻击造成15点伤害，同时引爆凋零
F,引爆玩家的凋零，根据造成伤害回复生命值

2,**人中菌**: 生命值250
回合开始时为角色附加1层中毒（被动）
c.造成7点伤害，2点中毒
d.造成5*4点伤害，每次攻击有概率提升中毒层数（25%）
e.造成10点伤害，攻击时依据角色当前中毒层数回复生命值，（每3层中毒回 一点生命值）
D.使角色获得3点中毒和3点脆弱

3,**迷失的守林人**：生命值250
> 漫无边际的森林之中，黑暗与阴影无处不在，守林人的提灯本应照亮那些角落，直到他被黑暗吞没之前 **（隐藏boss，需要：“复仇者”）**

无法预知下一步动作（被动）
攻击有概率提升20%伤害（被动）（20%)
a.攻击造成18点伤害，
b.攻击造成6*3点伤害
c.对自己和玩家造成3回合脆弱
d.获得8格挡
e.什么都不做

### 迷雾

#### 普通战斗

1,**腐化的守林人**：生命值120
使玩家获得易碎（被动）
a.攻击造成13-20点伤害
B.获得8-20格挡

2.**雾鬼**:生命值100
每次攻击造成1层中毒（被动）
a.获得3回合力量
b.攻击造成2*10点伤害
c.攻击造成12点伤害，造成2回合脆弱

3,**幻影**:生命值300
回合开始时损失随机20-40生命值（被动）
每次攻击造成1层凋零（被动）
a攻击造成3* 4点伤害
b造成2回合虚弱
c攻击造成5* 2 点伤害，每次攻击有（10%）概率引爆凋零

4,**雾行鸟**：生命值120
d攻击造成12点伤害，
e获得2回合力量，12点格挡
f攻击造成2*4点伤害

#### 紧急战斗

1,**雾鬼+幻影**

2,**腐烂山鬼**:生命值200
每次攻击后回复3点生命值，回合开始时回复5点生命值（被动）
a.攻击造成8点伤害3点护盾
b.攻击造成2*9点伤害
c.获得3点抗性
d.获得10点护盾

3,**迷途旅人**:生命值300
a造成3*8点伤害
b造成2*10点伤害
c获得12点格挡
d获得2回合力量和抗性

#### 险路恶敌（BOSS）

1,**最后的哨兵**:生命值500
> 哨兵所效忠的国家早已被迷雾所吞没，但这并不影响它继续履行它的义务

战斗开始时生成2个炮台 (被动)
生命值低于50%时，自己和炮塔获得力量 (被动)
a 攻击造成18点伤害
b 自己和炮塔获得10格挡
c 根据场上敌人数量获得格挡，一个15格挡
d 自己和炮塔回复7生命值
e 炮塔回复20生命值
**炮塔**:生命值100
当最后的哨兵死亡，炮塔自毁(被动)
a 攻击造成8点伤害
b 攻击造成12点伤害，自己损失5生命值

### 高塔

#### 普通战斗

1,**剑卫**:生命值250
战斗开始5回合后，获得力量（被动）
a造成2*16点伤害
b获得12点格挡
c造成28点伤害

2,**盾卫**:生命值500
A 获得30点格挡，获得无限装甲
B 造成格挡值50%的伤害，有50%概率眩晕自己
C 造成10+格挡值10%伤害，获得10格挡
D 使全队获得5点抗性

3,**铳卫**:生命值180
每次攻击后有25%额外造成3点伤害（被动）
a造成4*5点伤害，2回合脆弱，眩晕自己一回合（上弹）
b造成3*7点伤害，2回合易碎，眩晕自己一回合（上弹）

4,**法师**：生命值150
每次攻击将引爆1次凋零（被动）
a 造成2* 5点伤害
b 造成3* 8点伤害
c 获得12点格挡，20点生命值
d 为玩家附上3层凋零

#### 紧急作战

1,**石像鬼**:生命值300
a获得20点格挡
b造成3*8点伤害，2回合易碎
c造成28点伤害
d获得2回合力量

2,**卫士统领+剑卫+铳卫**

3,**卫士统领+盾卫+法师**

**卫士统领**:生命值240
战斗开始时获得35点格挡（被动）
a 造成5*3点伤害
b 所有友方单位获得5点格挡
c 获得15点格挡
d 为所有友方单位回复5生命值
e 眩晕一个队友，为其回复20生命值

4,**影卫**:生命值200
a自身获得5脆弱，造成20伤害
b造成36点伤害
c造成4回合脆弱和易碎
d造成2*16点伤害

#### 险路恶敌（BOSS)

1，**魔王**：生命值 700
每次攻击将引爆1次凋零，造成2层中毒（被动）
a造成3* 9点伤害，获得20点格挡
b移除自身当前所有负面效果，获得40点格挡
c蓄力：（没有力量时）眩晕2回合，获得5点力量（有力量时）造成30伤害，提供2凋零
d造成8* 4点伤害，攻击有20%概率被闪避，若命中，获得2凋零
E获得5点坚强，对我方造成5点易碎

2,**幕后黑手**：生命值1000
战斗开始时生成一个傀儡
A,获得20格挡，若傀儡未死亡回复傀儡全部生命值
B,造成3* 14点伤害
C,造成3* 14点伤害（你以为真的是吗？实际：偷取玩家所有格挡并提供给自己和傀儡，同时使自己和傀儡获得3点装甲）
D,对玩家造成5点凋零并引爆一次，根据引爆的数值回复生命值
E,将自身的负面效果转移给傀儡，然后对玩家造成20伤害
F,对玩家造成3点虚弱，3点凋零，3点脆弱，自身获得10格挡
G,对玩家造成5点伤害并有50%概率眩晕玩家1回合

**傀儡**：生命值150
傀儡的时候，每回合对幕后黑手随机提供一个增益效果3点（抗性，力量，坚强）
A,傀儡将自己的10点生命值提供给幕后黑手
B,傀儡引爆玩家的凋零
C,傀儡为幕后黑手提供10格挡

## 节点详解

**安全屋** : 抓紧时间整理物资、放松身心、规划路线，新的挑战很快就到。

选项：

- 好好休息：回复20%生命值
- 进行治疗：花费50%金币，恢复全部生命值
- 获取补给：获得一些金币（50-200）, 有0.1%的概率获得999金币

**得偿所愿**：散落的珠宝，未知的财务，你索取，???回应  
从随机三个收藏品中选择一个获得

- 价值0 （普通） 谢谢！30%
- 价值1 （稀有） 拿走一件藏品25%
- 价值2 （史诗） 许愿.... 20%
- 价值3 （传说） 我需要的是这个！ 15%
- 价值4 （神话） 你曾经在神话中所闻的物件，如今出现在你的面前 10%

**命运抉择**：固定位置刷新
第一层：**迷雾**
迷雾渐起，前途未知，你将何去何从？
选择下一层的方向：
1，前进：突破迷雾，进入森林
2，回头：结束游戏

**诡异行商**：商店类节点
出售物品：7张卡牌，3个藏品，3个药水，1个弃牌
**定价**：
> 卡牌：1价值 50-70 2价值90-110
> 藏品：价值*25+（55-70）随机
> 药水：30-70随机
> 弃牌：初始75，每次购买+25（一个商店只能购买一次）

## 事件

- 相遇：
  你偶遇了一个衣衫褴褛的人，他请求与你同行
    - 同意：
      前方的未知还在等待你们，获得藏品“背叛”
    - 拒绝：
      你拒绝了他，获得藏品“仇恨”
    - 无视：
      你假装没听见他的请求，转身离去了

- 翅膀雕像：在形状不同的巨石之间，你看见一尊做工精细的翅膀形状的蓝色雕像。你可以看见雕像的裂缝中有金币掉出来。或许里面还有更多……
    - 祈祷：从你的牌组中移除一张牌。失去 7 生命。  
      你曾听人提起过一个崇拜巨大鸟类的邪教。当你跪下祷告的时候，你开始觉得有一些头晕……过了一会儿，你醒了过来，感觉脚步有点变轻了。
    - 摧毁：获得 50-80 金币。  
      你使出浑身的力气开始砸雕像。很快它就彻底裂开，里面是一大堆金币。你把钱尽可能收集起来，重新上路。
    - 离开  
      这个雕像让你觉得有点不安。你决定不要去惊扰它，直接离开了。

- 黏液世界：
  你掉进了一个水坑里。
  可是坑里全是史莱姆黏液！
  爬出来后，你发现自己的金币似乎变少了。你回头一看，发现水坑里不但有你掉落的钱，还有不少其他不幸的冒险者们落下的金币。
    - 收集金币：获得 75 金币。失去 11 生命。
      在长时间与黏液接触而导致你的皮肤被烧走之前，你成功地捞出了不少金币。
    - 放手吧：失去 35-75 金币。
      你决定这样做不值得。

- 投资：付出金钱，收获金钱
    - 付出0块，25%收获0块，75%收获10块
    - 付出50块，25%收获0块，50%收获50块，25%收获100块
    - 付出100块，50%收获0块，25%收获100块，20%收获150块，4%收获200块，1% 收获1000块

- 追猎：森林里传来了异响，你似乎成为了猎物
    - 反抗：失去15生命值，获得藏品“复仇者”
      在密林之中似乎出现了一个诡异的人影，在“险路恶敌”中将会出现不同的敌人
    - 逃跑：获得20生命值和一个负面藏品
      你拼命逃窜，森林中诡异的声音消失了

- 村庄：你来到了一处不知名的村庄，在说明来意后村民热情的招待了你，并表示愿意提供帮助
    - 村民向你分享了曼哈顿计划 获得1个核弹
    - 村民给你了一个绿宝石 获得200金币
    - 村民给你分享了一个板烧鸡腿堡 回复生命值

- 人生意义：你看到一张4格漫画，两只白色的精灵伫立在乱石与惊涛之畔，探讨着此世的真理
    - 去码头整点薯条；生命值回满
    - 去银行整点金条；获得500块

- 好诗歪诗：你来到一处断壁，墙上刻了1首诗“商鞅知马力，比干见人心。孙膑脚扑朔，左丘眼迷离。”
    - 好诗：获得5张牌
    - 歪诗：获得随机1个价值3及以下藏品
    - 看不懂思密达：获得一个奇怪（负面）的藏品

## 结局

1. *失败* 在战斗中生命值变为 **0** 则战斗失败

2. *讲述中断* 在**迷雾**抉择中选择 `回头` 将会提前结束游戏，获得隐藏结局**讲述中断**
   > 这一切都太过诡异，你决定立马离开

3. *故事终局* 在**高塔**中战胜敌人 `魔王` 即可通关游戏，获得普通结局**故事终局**
   > 你战胜了一个俗套故事中的最终boss，它无恶不作，损人不利己，为了为恶而为恶，它或许有着悲惨的过往但不值得同情

4. *沉入虚妄* 在**相遇**中获得 `背叛` 或 `仇恨` ，在**门扉**中选择 `反抗` ，获得藏品 `巴别塔` ，即可在**高塔**中遇见隐藏boss
   `“幕后黑手”` ，战胜后获得隐藏结局**沉入虚妄**

   > 诸天神魔？以玩弄人间为乐，你？魔王？无外乎一场取悦的游戏罢了。  
   反抗？背后的背后，请神明睁眼，告诉我一切为何发生。