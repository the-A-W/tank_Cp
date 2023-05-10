#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include <conio.h>
#include <graphics.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib, "Winmm.lib")//�������ֿ�

//��ȡ�������룬�÷��ο���https://blog.csdn.net/JG_DF_/article/details/119238168
#define KEY_DOWN(VK_NONAME) (GetAsyncKeyState(VK_NONAME) & 0x8000)

//����궨�壬��ʡ�ڴ�ռ�
#define Int unsigned short int
using namespace std;

const Int map_row = 26;
const Int map_col = 26;
const Int enemy_num = 10;

//����ö�ٳ���
enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DIRECTIONCOUNT
};

//���̿���
enum Key
{
	Key_UP = 'W', Key_LEFT = 'A', Key_RIGHT = 'D', Key_DOWN = 'S', Key_J_Bullut = 'J', Key_P_Stop = 'P'
};

struct Tank
{
	int x;	//̹���ڵ�ͼ����������
	int y;	//̹���ڵ�ͼ����������
	DIRECTION direction;	//̹�˵ķ����ϡ��¡�����
	//int hp;	//̹��Ѫ����Ϊ��������
	bool live;//̹���Ƿ�����
};

struct Bullet
{
	//�ӵ��Ļ�ͼ����
	int pos_x;
	int pos_y;
	//����
	DIRECTION direction;
	//�ӵ�״̬
	bool status;
};


const wchar_t map_file_path[] = _T("");//��ͼ�ļ���·����
const wchar_t map_file_name[] = _T("map.txt");//��ͼ�ļ����ļ���
const unsigned int max_stage = 35;//��ͼ����

const wchar_t*const mytank_filename[DIRECTIONCOUNT] =
{ _T("tank_up.jpg"),_T("tank_down.jpg") ,_T("tank_left.jpg") ,_T("tank_right.jpg") };

const wchar_t* const enemytank_filename[DIRECTIONCOUNT] =
{ _T("enemy_tank_up.jpg"),_T("enemy_tank_down.jpg") ,_T("enemy_tank_left.jpg") ,_T("enemy_tank_right.jpg") };