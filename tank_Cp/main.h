#pragma once
#include"Gamesettings.h"

//�˵�ģ��
void display_1();//���˵�
//void display_2();//�����˵�

//��½ģ��
//void Log_in();

//��Ϸģ��
void loadmap(int stage);
void Map();//��ͼ_1
void game();//��Ϸģ��
/***************************************
* ����̹�˰���Ӧ�ķ����ƶ�
* ����ֵ��ʧ�� - false �ɹ� - true
***************************************/
bool tank_walk(Tank* tank, DIRECTION dir, IMAGE* img, int step);
//�ӵ��ƶ�����
void bullet_action(Bullet* bullet);
//���õ�ͼ����
void set_map(int x, int y, int val);

//�з�̹���ƶ�
void enemy_tank_walk(Tank* tank, DIRECTION direction, IMAGE* img);