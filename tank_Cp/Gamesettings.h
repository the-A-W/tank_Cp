#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include <conio.h>
#include <graphics.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib, "Winmm.lib")//导入音乐库

//获取键盘输入，用法参考：https://blog.csdn.net/JG_DF_/article/details/119238168
#define KEY_DOWN(VK_NONAME) (GetAsyncKeyState(VK_NONAME) & 0x8000)

//特殊宏定义，节省内存空间
#define Int unsigned short int
using namespace std;

const Int map_row = 26;
const Int map_col = 26;
const Int enemy_num = 10;

//方向枚举常量
enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DIRECTIONCOUNT
};

//键盘控制
enum Key
{
	Key_UP = 'W', Key_LEFT = 'A', Key_RIGHT = 'D', Key_DOWN = 'S', Key_J_Bullut = 'J', Key_P_Stop = 'P'
};

struct Tank
{
	int x;	//坦克在地图数组所在列
	int y;	//坦克在地图数组所在行
	DIRECTION direction;	//坦克的方向，上、下、左、右
	//int hp;	//坦克血量，为零则死亡
	bool live;//坦克是否死亡
};

struct Bullet
{
	//子弹的绘图坐标
	int pos_x;
	int pos_y;
	//方向
	DIRECTION direction;
	//子弹状态
	bool status;
};


const wchar_t map_file_path[] = _T("");//地图文件的路径名
const wchar_t map_file_name[] = _T("map.txt");//地图文件的文件名
const unsigned int max_stage = 35;//地图数量

const wchar_t*const mytank_filename[DIRECTIONCOUNT] =
{ _T("tank_up.jpg"),_T("tank_down.jpg") ,_T("tank_left.jpg") ,_T("tank_right.jpg") };

const wchar_t* const enemytank_filename[DIRECTIONCOUNT] =
{ _T("enemy_tank_up.jpg"),_T("enemy_tank_down.jpg") ,_T("enemy_tank_left.jpg") ,_T("enemy_tank_right.jpg") };