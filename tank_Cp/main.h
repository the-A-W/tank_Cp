#pragma once
#include"Gamesettings.h"

//菜单模块
void display_1();//主菜单
//void display_2();//二级菜单

//登陆模块
//void Log_in();

//游戏模块
void loadmap(int stage);
void Map(int stage);//地图_1
int game(int stage);//游戏模块
void gameover(int);
/***************************************
* 控制坦克按相应的方向移动
* 返回值：失败 - 0 成功 - 1
***************************************/
int do_tank_walk(Tank* tank, DIRECTION dir, IMAGE* img, int step);
//子弹移动函数
int bullet_action(Bullet* bullet, Tank* enemy_tank,int Is_mytank);
//设置地图函数
void set_map(int x, int y, int val);

//敌方坦克移动
void tank_walk(Tank* tank, DIRECTION direction, IMAGE* img);
DIRECTION enemy_direction(Tank* tank, int x, int y);
//坦克开火
void tank_fire(Tank* tank, Bullet* bullet);
