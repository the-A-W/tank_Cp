#pragma once
#include"Gamesettings.h"

//�˵�ģ��
void display_1();//���˵�
//void display_2();//�����˵�

//��½ģ��
//void Log_in();

//��Ϸģ��
void loadmap(int stage);
void Map(int stage);//��ͼ_1
bool game(int stage);//��Ϸģ��
void gameover(bool);
/***************************************
* ����̹�˰���Ӧ�ķ����ƶ�
* ����ֵ��ʧ�� - false �ɹ� - true
***************************************/
bool do_tank_walk(Tank* tank, DIRECTION dir, IMAGE* img, int step);
//�ӵ��ƶ�����
bool bullet_action(Bullet* bullet, Tank* enemy_tank,bool Is_mytank);
//���õ�ͼ����
void set_map(int x, int y, int val);

//�з�̹���ƶ�
void tank_walk(Tank* tank, DIRECTION direction, IMAGE* img);
DIRECTION enemy_direction(Tank* tank, int x, int y);
//̹�˿���
void tank_fire(Tank* tank, Bullet* bullet);
