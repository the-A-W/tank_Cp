#pragma once
#include"Gamesettings.h"

//菜单模块
void display_1();//主菜单
//void display_2();//二级菜单

//登陆模块
//void Log_in();

//游戏模块
void loadmap(int stage);
void Map();//地图_1
void game();//游戏模块
/***************************************
* 控制坦克按相应的方向移动
* 返回值：失败 - false 成功 - true
***************************************/
bool tank_walk(Tank* tank, DIRECTION dir, IMAGE* img, int step);
//子弹移动函数
void bullet_action(Bullet* bullet);
//设置地图函数
void set_map(int x, int y, int val);

//敌方坦克移动
void enemy_tank_walk(Tank* tank, DIRECTION direction, IMAGE* img);