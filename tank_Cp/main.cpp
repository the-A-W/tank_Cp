#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"



void main()
{

	display_1();


	//initgraph(650, 650);

	////��ʾ���˵��˵�
	//IMAGE display_1_img;
	//loadimage(&display_1_img, _T("display_1.png"), 650, 650);
	//putimage(0, 0, &display_1_img);

	//IMAGE img;
	//loadimage(&img, _T("player1_0_left1"));
	system("pause");
}

//void display_1()
//{
//	
//}

//��ͼ�ö�ά����洢
//��������ǽΪ1������������ǽΪ2����ӥ ��3��4���з�̹�� 100~109,�ҷ�̹��200
//int map[26][26];



//void game()
//{
//
//	//while (1)
//		//���س�ʼ��ͼ
//	Map();
//
//	int key;//�洢��������
//	Tank my_tank;
//	//����̹��ͼƬ
//	IMAGE img_mytank[DIRECTIONCOUNT];
//	IMAGE img_mytankhide[DIRECTIONCOUNT];
//	loadimage(&img_mytank[UP], mytank_filename[UP], 50, 50);
//	loadimage(&img_mytank[DOWN], mytank_filename[DOWN], 50, 50);
//	loadimage(&img_mytank[LEFT], mytank_filename[LEFT], 50, 50);
//	loadimage(&img_mytank[RIGHT], mytank_filename[RIGHT], 50, 50);
//	//��ʼ��̹��
//	my_tank.x = 8;
//	my_tank.y = 24;
//	my_tank.direction = UP;
//	my_tank.live = 1;
//
//	map[my_tank.y][my_tank.x] = 200;
//	map[my_tank.y][my_tank.x + 1] = 200;
//	map[my_tank.y + 1][my_tank.x] = 200;
//	map[my_tank.y + 1][my_tank.x + 1] = 200;
//	//��ʾ̹��
//	putimage(my_tank.x * 25, my_tank.y * 25, &img_mytank[my_tank.direction]);
//
//	while (1)
//	{
//		if (_kbhit())
//		{
//			key = _getch();
//			switch (key)
//			{
//			case 'a'://��
//				//ǰ���ж��Ƿ�Խ�磬�����ж��Ƿ��ǿյ�
//				if (map[my_tank.y][my_tank.x - 1] >= 0 && map[my_tank.y][my_tank.x - 1] == 0 && map[my_tank.y + 1][my_tank.x - 1])
//				{
//					//���ԭ̹��������������
//					map[my_tank.y][my_tank.x] = 0;
//					map[my_tank.y][my_tank.x + 1] = 0;
//					map[my_tank.y + 1][my_tank.x] = 0;
//					map[my_tank.y + 1][my_tank.x + 1] = 0;
//
//					setfillcolor(BLACK);
//					solidrectangle(my_tank.x * 25, my_tank.y * 25, my_tank.x * 25 + 50, my_tank.y * 25 + 50);
//					//����̹�������Լ����µ�ͼ
//					my_tank.x--;
//					map[my_tank.y][my_tank.x] = 200;
//					map[my_tank.y][my_tank.x + 1] = 200;
//					map[my_tank.y + 1][my_tank.x] = 200;
//					map[my_tank.y + 1][my_tank.x + 1] = 200;
//
//					my_tank.direction = LEFT;
//					putimage(my_tank.x * 25, my_tank.y * 25, &img_mytank[my_tank.direction]);
//				}
//				break;
//			case 'w'://��
//
//				break;
//
//			case 's'://��
//
//				break;
//
//			case 'd'://��
//
//				break;
//
//			case 'j'://����
//
//				break;
//			case 'p'://��ͣ
//				system("pause");
//				break;
//			}
//		}
//		Sleep(10);
//	}
//
//
//}







//void Map() {
//	int i, j;
//	IMAGE img_home, img_wall_1, img_wall_2;
//
//	loadimage(&img_home, _T("home_1.jpg"), 50, 50);// ��ӥ
//	loadimage(&img_wall_1, _T("wall_1.jpg"), 25, 25);//����������ǽ
//	loadimage(&img_wall_2, _T("wall_2.jpg"), 25, 25);//��������ǽ
//	loadmap(1);
//
//
//	for (i = 0; i < 26; i++) {
//		for (j = 0; j < 26; j++) {
//			if (map[i][j] == 1) {
//				putimage(25 * j, 25 * i, &img_wall_1);
//			}
//			else if (map[i][j] == 2) {
//				putimage(25 * j, 25 * i, &img_wall_2);
//			}
//			else if (map[i][j] == 3) {
//				putimage(25 * j, 25 * i, &img_home);
//
//				map[i][j] = 4;
//				map[i][j + 1] = 4;
//				map[i + 1][j] = 4;
//				map[i + 1][j + 1] = 4;
//			}
//		}
//	}
//}
//
//
//void loadmap(int stage)
//{
//	//��ͼ�ļ���
//	ifstream map_file;
//	//�����ͼ�ļ���
//	wstring temp;
//	temp = map_file_path;
//	temp += map_file_name;
//	int text = 0;
//	map_file.open(temp);
//	if (!map_file.is_open())
//	{
//		text = 1;
//		cout << "�򿪵�ͼʧ�ܣ�" << endl;
//		//exit(1);
//	}
//
//	//�����ļ���ȡλ�ã������ؿ���֮����ӵ�һ�ؿ�ʼ
//	stage -= 1;
//	stage = stage % max_stage;
//	map_file.seekg(stage * map_row * map_col * 2);
//	int num_temp;
//	for (int row = 0;row < map_row;row++)
//		for (int col = 0;col < map_col;col++)
//		{
//			map_file >> dec >> num_temp;
//			map[row][col] = num_temp;
//		}
//	map_file.close();
//
//}