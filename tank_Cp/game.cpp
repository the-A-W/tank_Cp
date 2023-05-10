#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"


//��ͼ�ö�ά����洢
//��������ǽΪ1������������ǽΪ2����ӥ ��3��4���з�̹�� 100~109,�ҷ�̹��200
int map[26][26];
/***************************************
* ����̹�˰���Ӧ�ķ����ƶ�
* ����ֵ��ʧ�� - false �ɹ� - true
***************************************/
bool tank_walk(Tank* tank,DIRECTION dir,IMAGE *img,int step);

void game()
{
	//��������
	//mciSendString(_T("play cxk_1.mp3 repeat"), NULL, 0, NULL);
	//�ҷ�̹��
	Tank my_tank;
	//�ҷ�̹�˷�����ӵ�
	Bullet my_bullet;

	//�з�̹��
	Tank enemy_tank[enemy_num];
	//�з�̹�˷�����ӵ�
	Bullet enemy_bullet[enemy_num];


	//���ص�ͼ
	Map();

	//�洢��������
	int key;
	//��¼��ǰ�ĳ�������ߴ�����ÿ��10ms
	int times = 0;
	//�з�̹�˴�������
	int enemy_total = 3;
	//�ӵ�Ŀǰ������
	my_bullet.status = false;
	

	//����̹��ͼƬ
	IMAGE img_mytank[DIRECTIONCOUNT];
	IMAGE img_enemytank[DIRECTIONCOUNT];
	loadimage(&img_mytank[UP], mytank_filename[UP], 50, 50);
	loadimage(&img_mytank[DOWN], mytank_filename[DOWN], 50, 50);
	loadimage(&img_mytank[LEFT],mytank_filename[LEFT], 50, 50);
	loadimage(&img_mytank[RIGHT], mytank_filename[RIGHT], 50, 50);
	loadimage(&img_enemytank[UP], enemytank_filename[UP], 50, 50);
	loadimage(&img_enemytank[DOWN], enemytank_filename[DOWN], 50, 50);
	loadimage(&img_enemytank[LEFT], enemytank_filename[LEFT], 50, 50);
	loadimage(&img_enemytank[RIGHT], enemytank_filename[RIGHT], 50, 50);
		
	//��ʼ��̹��
	my_tank.x = 8;
	my_tank.y = 24;
	my_tank.direction = UP;
	my_tank.live = 1;

	//map[my_tank.y][my_tank.x] = 200;
	//map[my_tank.y][my_tank.x+1] = 200;
	//map[my_tank.y+1][my_tank.x] = 200;
	//map[my_tank.y+1][my_tank.x+1] = 200;
	set_map(my_tank.x, my_tank.y, 200);

	//���õз�̹�˳���λ��
	for (int i = 0;i < enemy_num;i++)
	{
		if (i % 3 == 0)
		{
			enemy_tank[i].x = 0;
		}
		else if (i % 3 == 1)
		{
			enemy_tank[i].x = 12;
		}
		else if (i % 3 == 2)
		{
			enemy_tank[i].x = 24;
		}
		enemy_tank[i].y = 0;
		enemy_tank[i].live = 1;
		enemy_tank[i].direction = DOWN;
		set_map(enemy_tank[i].x, enemy_tank[i].y, 100 + i);
		enemy_bullet[i].status = false;
	}
	//�з�̹�˵ǳ�
	tank_walk(&enemy_tank[0], DOWN, &img_enemytank[DOWN], 0);
	tank_walk(&enemy_tank[1], DOWN, &img_enemytank[DOWN], 0);
	tank_walk(&enemy_tank[2], DOWN, &img_enemytank[DOWN], 0);
	enemy_total = 3;

	//��ʾ̹��		
	putimage(my_tank.x * 25, my_tank.y * 25, &img_mytank[my_tank.direction]);
	
	
	while (true)
	{
		//0.5s�ƶ�һ�εз�̹��
		if (times % 30 == 0)
		{
			for (int i = 0;i < enemy_total;i++)
			{
				if (enemy_tank[i].live)
				{
					enemy_tank_walk(&enemy_tank[i], enemy_tank[i].direction, &img_enemytank[enemy_tank[i].direction]);
				}
			}
		}
		if (times % 10 == 0)
		{
			if (_kbhit())
			{
				key = _getch();
				switch (key)
				{
				case 'a'://��
					//ǰ���ж��Ƿ�Խ�磬�����ж��Ƿ��ǿյ�
					if (my_tank.direction == LEFT && my_tank.x - 1 >= 0 && map[my_tank.y][my_tank.x - 1] == 0 && map[my_tank.y + 1][my_tank.x - 1] == 0)
					{
						tank_walk(&my_tank, LEFT, &img_mytank[my_tank.direction], 1);
					}
					else if (my_tank.direction != LEFT)
					{
						//��������
						my_tank.direction = LEFT;
						tank_walk(&my_tank, LEFT, &img_mytank[my_tank.direction], 0);
					}
					break;
				case 'w'://��
					if (my_tank.direction == UP && my_tank.y - 1 >= 0 && map[my_tank.y - 1][my_tank.x] == 0 && map[my_tank.y - 1][my_tank.x + 1] == 0)
					{
						tank_walk(&my_tank, UP, &img_mytank[my_tank.direction], 1);
					}
					else if (my_tank.direction != UP)
					{
						my_tank.direction = UP;
						tank_walk(&my_tank, UP, &img_mytank[my_tank.direction], 0);
					}
					break;

				case 's'://��
					if (my_tank.direction == DOWN && my_tank.y + 2 <= 25 && map[my_tank.y + 2][my_tank.x] == 0 && map[my_tank.y + 2][my_tank.x + 1] == 0)
					{
						tank_walk(&my_tank, DOWN, &img_mytank[my_tank.direction], 1);
					}
					else if (my_tank.direction != DOWN)
					{
						my_tank.direction = DOWN;
						tank_walk(&my_tank, DOWN, &img_mytank[my_tank.direction], 0);
					}
					break;

				case 'd'://��
					if (my_tank.direction == RIGHT && my_tank.x + 2 <= 25 && map[my_tank.y][my_tank.x + 2] == 0 && map[my_tank.y + 1][my_tank.x + 2] == 0)
					{
						tank_walk(&my_tank, RIGHT, &img_mytank[my_tank.direction], 1);
					}
					else if (my_tank.direction != RIGHT)
					{
						my_tank.direction = RIGHT;
						tank_walk(&my_tank, RIGHT, &img_mytank[my_tank.direction], 0);
					}
					break;

				case 'j'://����
					if (!my_bullet.status)
					{
						PlaySound(_T("paoji.wav"), NULL, SND_FILENAME | SND_ASYNC);
						if (my_tank.direction == UP)
						{
							//�ӵ���ͼ��������
							my_bullet.pos_x = my_tank.x * 25 + 23;
							my_bullet.pos_y = my_tank.y * 25 - 3;
						}
						else if (my_tank.direction == LEFT)
						{
							//�ӵ���ͼ��������
							my_bullet.pos_x = my_tank.x * 25 - 3;
							my_bullet.pos_y = my_tank.y * 25 + 23;
						}
						else if (my_tank.direction == DOWN)
						{
							//�ӵ���ͼ��������
							my_bullet.pos_x = my_tank.x * 25 + 23;
							my_bullet.pos_y = my_tank.y * 25 + 50;
						}
						else if (my_tank.direction == RIGHT)
						{
							//�ӵ���ͼ��������
							my_bullet.pos_x = my_tank.x * 25 + 50;
							my_bullet.pos_y = my_tank.y * 25 + 23;
						}
						//��ȡ�ӵ�����
						my_bullet.direction = my_tank.direction;
						//�ı��ӵ�״̬
						my_bullet.status = !my_bullet.status;
					}
					break;

				case 'p'://��ͣ
					system("pause");
					break;

				default:
					break;
				}
			}
		}
		
		
		if (my_bullet.status)
			bullet_action(&my_bullet);
		Sleep(10);
		times++;
	}
}


void Map() {
	int i, j;
	IMAGE img_home, img_wall_1, img_wall_2;

	loadimage(&img_home, _T("home_1.jpg"), 50, 50);// ��ӥ
	loadimage(&img_wall_1, _T("wall_1.jpg"), 25, 25);//����������ǽ
	loadimage(&img_wall_2, _T("wall_2.jpg"), 25, 25);//��������ǽ
	loadmap(1);


	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			if (map[i][j] == 1) {
				putimage(25 * j, 25 * i, &img_wall_1);
			}
			else if (map[i][j] == 2) {
				putimage(25 * j, 25 * i, &img_wall_2);
			}
			else if (map[i][j] == 3) {
				putimage(25 * j, 25 * i, &img_home);

				map[i][j] = 4;
				map[i][j + 1] = 4;
				map[i + 1][j] = 4;
				map[i + 1][j + 1] = 4;
			}
		}
	}
}


void loadmap(int stage)
{
	//��ͼ�ļ���
	ifstream map_file;
	//�����ͼ�ļ���
	wstring temp;
	temp = map_file_path;
	temp += map_file_name;
	int text = 0;
	map_file.open(temp);
	if (!map_file.is_open())
	{
		text = 1;
		cout << "�򿪵�ͼʧ�ܣ�" << endl;
		//exit(1);
	}

	//�����ļ���ȡλ�ã������ؿ���֮����ӵ�һ�ؿ�ʼ
	stage -= 1;
	stage = stage % max_stage;
	map_file.seekg(stage * map_row * map_col * 2);
	int num_temp;
	for (int row = 0;row < map_row;row++)
		for (int col = 0;col < map_col;col++)
		{
			map_file >> dec >> num_temp;
			map[row][col] = num_temp;
		}
	map_file.close();

}


bool tank_walk(Tank* tank,DIRECTION dir,IMAGE *img,int step)
{
	int new_x = tank->x;
	int new_y = tank->y;

	if (step) {
		if (dir == UP)
		{
			new_y--;
		}
		else if (dir == DOWN)
		{
			new_y++;
		}
		else if (dir == LEFT)
		{
			new_x--;
		}
		else if (dir == RIGHT)
		{
			new_x++;
		}
		else
		{
			return false;
		}
		//�����ͼ������ԭ̹��λ��
		//map[tank->y][tank->x] = 0;
		//map[tank->y][tank->x + 1] = 0;
		//map[tank->y + 1][tank->x] = 0;
		//map[tank->y + 1][tank->x + 1] = 0;
		set_map(tank->x, tank->y, 0);
	}
	//����ԭλ�õ�̹��ͼ��
	setfillcolor(BLACK);
	solidrectangle(tank->x * 25, tank->y * 25, tank->x * 25 + 50, tank->y * 25 + 50);
	if (step)
	{
		//���µ�ͼ����̹��λ��
		//map[new_y][new_x] = 200;
		//map[new_y][new_x + 1] = 200;
		//map[new_y + 1][new_x] = 200;
		//map[new_y + 1][new_x + 1] = 200;
		set_map(new_x, new_y, 200);

		//����̹������
		tank->x = new_x;
		tank->y = new_y;
	}
	//��������Ӧ���ⲿʵ�֣�����ᴫ�����ǰ��̹�˷���
	//��������
	//tank->direction = dir;
	putimage(tank->x * 25, tank->y * 25, img);
	return true;
}

void bullet_action(Bullet* bullet)
{
	//�ӵ��ڵ�ͼ�ж�ά���������
	int x, y,x1,y1;
	x = bullet->pos_x / 25;
	y = bullet->pos_y / 25;

	//������һ�λ��Ƶ��ӵ�
	setfillcolor(BLACK);
	solidrectangle(bullet->pos_x, bullet->pos_y, bullet->pos_x+3, bullet->pos_y+3);

	//���ݷ�������ӵ�������
	if (bullet->direction == UP)
	{
		bullet->pos_y -= 2;
		x1 = x + 1;
		y1 = y;
	}
	else if (bullet->direction == DOWN)
	{
		bullet->pos_y += 2;
		x1 = x + 1;
		y1 = y;
	}
	else if (bullet->direction == LEFT)
	{
		bullet->pos_x -= 2;
		x1 = x;
		y1 = y + 1;
	}
	else if (bullet->direction == RIGHT)
	{
		bullet->pos_x += 2;
		x1 = x;
		y1 = y + 1;
	}
	else
	{
		return;
	}
	if (bullet->pos_x < 0 || bullet->pos_x>650 || bullet->pos_y < 0 || bullet->pos_y>650)
	{
		bullet->status = false;
		return;
	}
	
	//��ײ���
	if (map[y][x] == 4 || map[y1][y1] == 4)
	{
		PlaySound(_T("boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return;
	}
	//�ӵ����п�������ǽ
	if (map[y][x] == 1)
	{
		map[y][x] = 0;
		bullet->status = false;
		setfillcolor(BLACK);
		solidrectangle(x * 25, y * 25, x * 25 + 25, y * 25 + 25);
	}
	else if(map[y][x]==2)//���в���������ǽ
	{
		bullet->status = false;
	}
	//�ӵ����п�������ǽ
	if (map[y1][x1] == 1)
	{
		map[y1][x1] = 0;
		bullet->status = false;
		setfillcolor(BLACK);
		solidrectangle(x1 * 25, y1 * 25, x1 * 25 + 25, y1 * 25 + 25);
	}
	else if (map[y1][x1] == 2)//���в���������ǽ
	{
		bullet->status = false;
	}


	//���»����ӵ�
	if (bullet->status)
	{
		setfillcolor(WHITE);
		solidrectangle(bullet->pos_x, bullet->pos_y, bullet->pos_x + 3, bullet->pos_y + 3);
	}
}

void set_map(int x,int y,int val)
{
	map[y][x] = val;
	map[y][x+1] = val;
	map[y+1][x] = val;
	map[y+1][x+1] = val;
}

void enemy_tank_walk(Tank* tank, DIRECTION direction, IMAGE* img)
{
	switch (direction)
	{
	case LEFT://��
		//ǰ���ж��Ƿ�Խ�磬�����ж��Ƿ��ǿյ�
		if (tank->direction == LEFT && tank->x - 1 >= 0 && map[tank->y][tank->x - 1] == 0 && map[tank->y + 1][tank->x - 1] == 0)
		{
			tank_walk(tank, LEFT, img, 1);
		}
		else if (tank->direction != LEFT)
		{
			//��������
			tank->direction = LEFT;
			tank_walk(tank, LEFT, img, 0);
		}
		break;
	case UP://��
		if (tank->direction == UP && tank->y - 1 >= 0 && map[tank->y - 1][tank->x] == 0 && map[tank->y - 1][tank->x + 1] == 0)
		{
			tank_walk(tank, UP, img, 1);
		}
		else if (tank->direction != UP)
		{
			tank->direction = UP;
			tank_walk(tank, UP, img, 0);
		}
		break;

	case DOWN://��
		if (tank->direction == DOWN && tank->y + 2 <= 25 && map[tank->y + 2][tank->x] == 0 && map[tank->y + 2][tank->x + 1] == 0)
		{
			tank_walk(tank, DOWN, img, 1);
		}
		else if (tank->direction != DOWN)
		{
			tank->direction = DOWN;
			tank_walk(tank, DOWN, img, 0);
		}
		break;

	case RIGHT://��
		if (tank->direction == RIGHT && tank->x + 2 <= 25 && map[tank->y][tank->x + 2] == 0 && map[tank->y + 1][tank->x + 2] == 0)
		{
			tank_walk(tank, RIGHT, img, 1);
		}
		else if (tank->direction != RIGHT)
		{
			tank->direction = RIGHT;
			tank_walk(tank, RIGHT, img, 0);
		}
		break;
	}
}