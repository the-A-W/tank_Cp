#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"


//地图用二维数组存储
//可消除的墙为1，不可消除的墙为2，老鹰 （3，4）敌方坦克 100~109,我方坦克200
int map[26][26];

int game(int stage,int choice)
{
	setbkcolor(BLACK);//设置背景色
	cleardevice();
	//背景音乐
	mciSendString(_T("play cxk_1.mp3 repeat"), NULL, 0, NULL);
	//初始化随机数种子
	srand((unsigned int)time(NULL));
	

	//我方坦克
	Tank my_tank;
	//我方坦克发射的子弹
	Bullet my_bullet;

	//敌方坦克
	Tank enemy_tank[enemy_num];
	//敌方坦克发射的子弹
	Bullet enemy_bullet[enemy_num];


	//加载地图
	loadmap(stage);

	//Map(stage);

	//记录当前的程序的休眠次数，每次10ms
	int times = 0;
	//敌方坦克存在数量
	int enemy_total = 0;
	//子弹目前不存在
	my_bullet.status = 0;
	
	//测试
	

	//加载坦克图片
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
		
	//初始化坦克
	my_tank.x = 8;
	my_tank.y = 24;
	my_tank.direction = UP;
	my_tank.live = 1;
	//Tank tank_save = {0 ,2,DOWN,1 };
	//my_tank = tank_save;
	//map[my_tank.y][my_tank.x] = 200;
	//map[my_tank.y][my_tank.x+1] = 200;
	//map[my_tank.y+1][my_tank.x] = 200;
	//map[my_tank.y+1][my_tank.x+1] = 200;
	//set_map(my_tank.x, my_tank.y, 200);

	//设置敌方坦克出场位置
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
		enemy_tank[i].Is_Mycamp = 0;
		//set_map(enemy_tank[i].x, enemy_tank[i].y, 100 + i);
		enemy_bullet[i].status = 0;
	}

	enemy_total = 3;
	//enemy_tank[0].x = 4;
	//enemy_tank[0].y = 0;
	//enemy_tank[0].live = 0;
	//敌方坦克登场
	if (choice)
	{
		read(enemy_tank, &my_tank, enemy_bullet, &my_bullet, enemy_total, times, map);
	}
	choice = 0;
	//地图图片修正
	map[24][12]=3;
	Map(stage);
	for (int i = 0;i < enemy_total;i++)
	{
		if (enemy_tank[i].live)
		{
			set_map(enemy_tank[i].x, enemy_tank[i].y, 100 + i);
			do_tank_walk(&enemy_tank[i], enemy_tank[i].direction, &img_enemytank[enemy_tank[i].direction], 0);
		}

	}
	//set_map(enemy_tank[0].x, enemy_tank[0].y, 100 );
	//do_tank_walk(&enemy_tank[1], DOWN, &img_enemytank[DOWN], 0);
	//set_map(enemy_tank[1].x, enemy_tank[1].y, 101);
	//do_tank_walk(&enemy_tank[2], DOWN, &img_enemytank[DOWN], 0);
	//set_map(enemy_tank[2].x, enemy_tank[2].y, 102);
	//do_tank_walk(&enemy_tank[4], DOWN, &img_enemytank[DOWN], 0);
	//set_map(enemy_tank[3].x, enemy_tank[3].y, 103);
	

	//显示坦克	
	set_map(my_tank.x, my_tank.y, 200);
	putimage(my_tank.x * 25, my_tank.y * 25, &img_mytank[my_tank.direction]);
	
	
	while (1)
	{
		
		//防止坦克出生重叠
		if (map[enemy_tank[enemy_total-1].x][enemy_tank[enemy_total-1].y] == 0)
		{
			if (times > 0 && times % 1000 == 0 && enemy_total < enemy_num)
			{
				set_map(enemy_tank[enemy_total].x, enemy_tank[enemy_total].y, 100 + enemy_total);
				enemy_total++;
				times = 0;
			}
		}
		if (times>0 && times % 200 == 0)
		{
			for (int i = 0;i < enemy_total;i++)
			{
				if (!enemy_tank[i].live)
					continue;
				//攻击我方老巢
				if (i % 2 == 0)
				{
					DIRECTION d = enemy_direction(&enemy_tank[i], 12, 24);
					tank_walk(&enemy_tank[i], d, &img_enemytank[d]);
				}
				else
				{
					DIRECTION d = enemy_direction(&enemy_tank[i], my_tank.x, my_tank.y);
					tank_walk(&enemy_tank[i], d, &img_enemytank[d]);
				}
				tank_fire(&enemy_tank[i], &enemy_bullet[i]);
			}
			
		}
		
		//0.5s移动一次敌方坦克
		else if (times % 50 == 0)
		{
			for (int i = 0;i < enemy_total;i++)
			{
				if (enemy_tank[i].live)
				{
					tank_walk(&enemy_tank[i], enemy_tank[i].direction, &img_enemytank[enemy_tank[i].direction]);
				}
			}
		}
		if (times % 15 == 0)
		{
			//if (_kbhit())
			//{
			//	key = _getch();
			//	switch (key)
			//	{
			//	case 'a'://左
			//		//前者判断是否越界，后者判断是否是空地
			//		if (my_tank.direction == LEFT && my_tank.x - 1 >= 0 && map[my_tank.y][my_tank.x - 1] == 0 && map[my_tank.y + 1][my_tank.x - 1] == 0)
			//		{
			//			tank_walk(&my_tank, LEFT, &img_mytank[my_tank.direction], 1);
			//		}
			//		else if (my_tank.direction != LEFT)
			//		{
			//			//调整方向
			//			my_tank.direction = LEFT;
			//			tank_walk(&my_tank, LEFT, &img_mytank[my_tank.direction], 0);
			//		}
			//		break;
			//	case 'w'://上
			//		if (my_tank.direction == UP && my_tank.y - 1 >= 0 && map[my_tank.y - 1][my_tank.x] == 0 && map[my_tank.y - 1][my_tank.x + 1] == 0)
			//		{
			//			tank_walk(&my_tank, UP, &img_mytank[my_tank.direction], 1);
			//		}
			//		else if (my_tank.direction != UP)
			//		{
			//			my_tank.direction = UP;
			//			tank_walk(&my_tank, UP, &img_mytank[my_tank.direction], 0);
			//		}
			//		break;

			//	case 's'://下
			//		if (my_tank.direction == DOWN && my_tank.y + 2 <= 25 && map[my_tank.y + 2][my_tank.x] == 0 && map[my_tank.y + 2][my_tank.x + 1] == 0)
			//		{
			//			tank_walk(&my_tank, DOWN, &img_mytank[my_tank.direction], 1);
			//		}
			//		else if (my_tank.direction != DOWN)
			//		{
			//			my_tank.direction = DOWN;
			//			tank_walk(&my_tank, DOWN, &img_mytank[my_tank.direction], 0);
			//		}
			//		break;

			//	case 'd'://右
			//		if (my_tank.direction == RIGHT && my_tank.x + 2 <= 25 && map[my_tank.y][my_tank.x + 2] == 0 && map[my_tank.y + 1][my_tank.x + 2] == 0)
			//		{
			//			tank_walk(&my_tank, RIGHT, &img_mytank[my_tank.direction], 1);
			//		}
			//		else if (my_tank.direction != RIGHT)
			//		{
			//			my_tank.direction = RIGHT;
			//			tank_walk(&my_tank, RIGHT, &img_mytank[my_tank.direction], 0);
			//		}
			//		break;

			//	case 'j'://开火
			//		if (!my_bullet.status)
			//		{
			//			PlaySound(_T("paoji.wav"), NULL, SND_FILENAME | SND_ASYNC);
			//			if (my_tank.direction == UP)
			//			{
			//				//子弹绘图坐标修正
			//				my_bullet.pos_x = my_tank.x * 25 + 23;
			//				my_bullet.pos_y = my_tank.y * 25 - 3;
			//			}
			//			else if (my_tank.direction == LEFT)
			//			{
			//				//子弹绘图坐标修正
			//				my_bullet.pos_x = my_tank.x * 25 - 3;
			//				my_bullet.pos_y = my_tank.y * 25 + 23;
			//			}
			//			else if (my_tank.direction == DOWN)
			//			{
			//				//子弹绘图坐标修正
			//				my_bullet.pos_x = my_tank.x * 25 + 23;
			//				my_bullet.pos_y = my_tank.y * 25 + 50;
			//			}
			//			else if (my_tank.direction == RIGHT)
			//			{
			//				//子弹绘图坐标修正
			//				my_bullet.pos_x = my_tank.x * 25 + 50;
			//				my_bullet.pos_y = my_tank.y * 25 + 23;
			//			}
			//			//获取子弹方向
			//			my_bullet.direction = my_tank.direction;
			//			//改变子弹状态
			//			my_bullet.status = !my_bullet.status;
			//		}
			//		break;

			//	case 'p'://暂停
			//		system("pause");
			//		break;
			//	
			//	case 27://esc的ascii码值为27，键入esc时返回主菜单
			//		display_1();
			//		break;
			//	
			//	default:
			//		break;
			//	}
			//}
			if (KEY_DOWN(Key_LEFT))
			{
				tank_walk(&my_tank, LEFT, &img_mytank[LEFT]);
			}
			if (KEY_DOWN(Key_UP))
			{
				/*if (my_tank.direction == UP && my_tank.y - 1 >= 0 && map[my_tank.y - 1][my_tank.x] == 0 && map[my_tank.y - 1][my_tank.x + 1] == 0)
					{
						do_tank_walk(&my_tank, UP, &img_mytank[my_tank.direction], 1);
					}
					else if (my_tank.direction != UP)
					{
						my_tank.direction = UP;
						do_tank_walk(&my_tank, UP, &img_mytank[my_tank.direction], 0);
					}*/
				tank_walk(&my_tank, UP, &img_mytank[UP]);
			}
			if (KEY_DOWN(Key_DOWN))
			{
				/*if (my_tank.direction == DOWN && my_tank.y + 2 <= 25 && map[my_tank.y + 2][my_tank.x] == 0 && map[my_tank.y + 2][my_tank.x + 1] == 0)
				{
					do_tank_walk(&my_tank, DOWN, &img_mytank[my_tank.direction], 1);
				}
				else if (my_tank.direction != DOWN)
				{
					my_tank.direction = DOWN;
					do_tank_walk(&my_tank, DOWN, &img_mytank[my_tank.direction], 0);
				}*/
				tank_walk(&my_tank, DOWN, &img_mytank[DOWN]);
			}
			if (KEY_DOWN(Key_RIGHT))
			{
				/*if (my_tank.direction == RIGHT && my_tank.x + 2 <= 25 && map[my_tank.y][my_tank.x + 2] == 0 && map[my_tank.y + 1][my_tank.x + 2] == 0)
				{
					do_tank_walk(&my_tank, RIGHT, &img_mytank[my_tank.direction], 1);
				}
				else if (my_tank.direction != RIGHT)
				{
					my_tank.direction = RIGHT;
					do_tank_walk(&my_tank, RIGHT, &img_mytank[my_tank.direction], 0);
				}*/
				tank_walk(&my_tank, RIGHT, &img_mytank[RIGHT]);
			}
			//开火
			if (KEY_DOWN(Key_J_Bullut))
			{
				//if (!my_bullet.status)
				//{
				//	PlaySound(_T("paoji.wav"), NULL, SND_FILENAME | SND_ASYNC);
				//	if (my_tank.direction == UP)
				//	{
				//		//子弹绘图坐标修正
				//		my_bullet.pos_x = my_tank.x * 25 + 23;
				//		my_bullet.pos_y = my_tank.y * 25 - 3;
				//	}
				//	else if (my_tank.direction == LEFT)
				//	{
				//		//子弹绘图坐标修正
				//		my_bullet.pos_x = my_tank.x * 25 - 3;
				//		my_bullet.pos_y = my_tank.y * 25 + 23;
				//	}
				//	else if (my_tank.direction == DOWN)
				//	{
				//		//子弹绘图坐标修正
				//		my_bullet.pos_x = my_tank.x * 25 + 23;
				//		my_bullet.pos_y = my_tank.y * 25 + 50;
				//	}
				//	else if (my_tank.direction == RIGHT)
				//	{
				//		//子弹绘图坐标修正
				//		my_bullet.pos_x = my_tank.x * 25 + 50;
				//		my_bullet.pos_y = my_tank.y * 25 + 23;
				//	}
				//	//获取子弹方向
				//	my_bullet.direction = my_tank.direction;
				//	//改变子弹状态
				//	my_bullet.status = !my_bullet.status;
				//	
				//}
				PlaySound(_T("paoji.wav"), NULL, SND_FILENAME | SND_ASYNC);
				tank_fire(&my_tank, &my_bullet);
			}
			//暂停
			if (KEY_DOWN(Key_P_Stop))
			{
				mciSendString(_T("pause cxk_1.mp3"), 0, 0, 0);
				system("pause");
				mciSendString(_T("resume cxk_1.mp3"), 0, 0, 0);
			}
			if (KEY_DOWN(Key_ESC))
			{
				
				if (1)
				{
					save(stage,enemy_tank, &my_tank,enemy_bullet,&my_bullet, enemy_total, times,map);
				}
				mciSendString(_T("close cxk_1.mp3"), NULL, 0, NULL);
				display_1();
				//break;
			}
		}
		
		
		if (my_bullet.status)
		{
			if (bullet_action(&my_bullet, enemy_tank, my_tank.Is_Mycamp))
			{
				return 0;
			}
		}
		for (int i = 0;i < enemy_total;i++)
		{
			if (enemy_bullet[i].status)
			{
				if (bullet_action(&enemy_bullet[i], enemy_tank,0))
				{
					return 0;
				}
			}
		}
		//判断敌方坦克是否全部消灭
		int isWin = 0;
		for (int i = 0;i < enemy_total;i++)
		{
			if (enemy_tank[i].live == 0)
				isWin++;
			if (isWin == enemy_num)
				return 1;
		}
		Sleep(10);
		times++;
	}
}


void Map(int stage) {
	int i, j;
	IMAGE img_home, img_wall_1, img_wall_2;

	loadimage(&img_home, _T("home_1.jpg"), 50, 50);// 老鹰
	loadimage(&img_wall_1, _T("wall_1.jpg"), 25, 25);//可消除的墙
	loadimage(&img_wall_2, _T("wall_2.png"), 25, 25);//不可消除的墙


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
	//地图文件流
	ifstream map_file;
	//保存地图文件名
	wstring temp;
	temp = map_file_path;
	temp += map_file_name;
	int text = 0;
	map_file.open(temp);
	if (!map_file.is_open())
	{
		text = 1;
		cout << "打开地图失败！" << endl;
		//exit(1);
	}

	//调整文件读取位置，到最大关卡数之后则从第一关开始
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


int do_tank_walk(Tank* tank,DIRECTION dir,IMAGE *img,int step)
{
	int new_x = tank->x;
	int new_y = tank->y;
	int old_map = map[tank->y][tank->x];
	if (step) 
	{
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
			return 0;
		}
		//清除地图数组上原坦克位置

		set_map(tank->x, tank->y, 0);
		//擦除原位置的坦克图像
		
	}
	setfillcolor(BLACK);
	solidrectangle(tank->x * 25, tank->y * 25, tank->x * 25 + 50, tank->y * 25 + 50);
	if (step)
	{
		//更新地图数组坦克位置
		
		set_map(new_x, new_y, old_map);

		//更新坦克坐标
		tank->x = new_x;
		tank->y = new_y;
	}
	putimage(tank->x * 25, tank->y * 25, img);
	return 1;
}

int bullet_action(Bullet* bullet,Tank* enemy_tank,int Is_Mytank)
{
	//子弹在地图中二维数组的坐标
	int x, y,x1,y1;
	x = bullet->pos_x / 25;
	y = bullet->pos_y / 25;

	//擦除上一次绘制的子弹
	setfillcolor(BLACK);
	solidrectangle(bullet->pos_x, bullet->pos_y, bullet->pos_x+3, bullet->pos_y+3);

	//根据方向计算子弹的坐标
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
		return 0;
	}
	if (bullet->pos_x < 0 || bullet->pos_x>650 || bullet->pos_y < 0 || bullet->pos_y>650)
	{
		bullet->status = 0;
		return 0;
	}
	
	//碰撞检查
	if (map[y][x] == 4 || map[y1][y1] == 4)
	{
		bullet->status = 0;
		//PlaySound(_T("boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return 1;
	}

	//击中我方坦克
	if (map[y][x] == 200 || map[y1][x1] == 200)
	{
		//判断是否是敌方坦克发射的子弹
		if(Is_Mytank==0)
		return 1;
	}

	//击中敌方坦克
	if ((map[y][x] >= 100 && map[y][x] <= 109) || (map[y1][x1] >= 100 && map[y1][x1] <= 109))
	{
		//判断是否是我方发射的子弹
		if (Is_Mytank == 1)
		{
			Tank* tank = NULL;
			bullet->status = 0;
			if (map[y][x] > 100 && map[y][x] <= 109)
				tank = enemy_tank + (map[y][x] - 100);
			else
				tank = enemy_tank + (map[y1][x1] - 100);

			tank->live = 0;
			set_map(tank->x, tank->y, 0);
			setfillcolor(BLACK);
			solidrectangle(tank->x * 25, tank->y * 25, tank->x * 25 + 50, tank->y * 25 + 50);
		}
	}


	//子弹击中可消除的墙
	if (map[y][x] == 1)
	{
		map[y][x] = 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x * 25, y * 25, x * 25 + 25, y * 25 + 25);
	}
	else if(map[y][x]==2)//击中不可消除的墙
	{
		bullet->status = 0;
	}
	//子弹击中可消除的墙
	if (map[y1][x1] == 1)
	{
		map[y1][x1] = 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x1 * 25, y1 * 25, x1 * 25 + 25, y1 * 25 + 25);
	}
	else if (map[y1][x1] == 2)//击中不可消除的墙
	{
		bullet->status = 0;
	}


	//重新绘制子弹
	if (bullet->status)
	{
		setfillcolor(WHITE);
		solidrectangle(bullet->pos_x, bullet->pos_y, bullet->pos_x + 3, bullet->pos_y + 3);
	}
	//setfillcolor(BLACK);
    //solidrectangle(bullet->pos_x, bullet->pos_y, bullet->pos_x+3, bullet->pos_y+3);

	return 0;
}

void set_map(int x,int y,int val)
{
	map[y][x] = val;
	map[y][x+1] = val;
	map[y+1][x] = val;
	map[y+1][x+1] = val;
}

void tank_walk(Tank* tank, DIRECTION direction, IMAGE* img)
{
	switch (direction)
	{
	case LEFT://左
		//前者判断是否越界，后者判断是否是空地
		if (tank->direction == LEFT && tank->x - 1 >= 0 && map[tank->y][tank->x - 1] == 0 && map[tank->y + 1][tank->x - 1] == 0)
		{
			do_tank_walk(tank, LEFT, img, 1);
		}
		else if (tank->direction != LEFT)
		{
			//调整方向
			tank->direction = LEFT;
			do_tank_walk(tank, LEFT, img, 0);
		}
		break;
	case UP://上
		if (tank->direction == UP && tank->y - 1 >= 0 && map[tank->y - 1][tank->x] == 0 && map[tank->y - 1][tank->x + 1] == 0)
		{
			do_tank_walk(tank, UP, img, 1);
		}
		else if (tank->direction != UP)
		{
			tank->direction = UP;
			do_tank_walk(tank, UP, img, 0);
		}
		break;

	case DOWN://下
		if (tank->direction == DOWN && tank->y + 2 <= 25 && map[tank->y + 2][tank->x] == 0 && map[tank->y + 2][tank->x + 1] == 0)
		{
			do_tank_walk(tank, DOWN, img, 1);
		}
		else if (tank->direction != DOWN)
		{
			tank->direction = DOWN;
			do_tank_walk(tank, DOWN, img, 0);
		}
		break;

	case RIGHT://右
		if (tank->direction == RIGHT && tank->x + 2 <= 25 && map[tank->y][tank->x + 2] == 0 && map[tank->y + 1][tank->x + 2] == 0)
		{
			do_tank_walk(tank, RIGHT, img, 1);
		}
		else if (tank->direction != RIGHT)
		{
			tank->direction = RIGHT;
			do_tank_walk(tank, RIGHT, img, 0);
		}
		break;
	}
}

DIRECTION enemy_direction(Tank* tank, int x, int y)
{
	int ret = rand() % 100;
	//目标在左方
	if (tank->x > x)
	{
		//在左上方
		if (tank->y > y)
		{
			if (ret <= 50)
				return UP;
			else
				return LEFT;
		}
		//在左下方
		else
		{
			if (ret <= 50)
				return DOWN;
			else
				return LEFT;
		}
	}
	//目标在右方
	else
	{
		//右上方
		if (tank->y > y)
		{
			if (ret <= 50)
				return UP;
			else
				return RIGHT;
		}
		//右下方
		else
		{
			if (ret <= 50)
				return DOWN;
			else
				return RIGHT;
		}
	}
}

void tank_fire(Tank* tank, Bullet* bullet)
{
	if (!bullet->status)
	{
		//PlaySound(_T("paoji.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (tank->direction == UP)
		{
			//子弹绘图坐标修正
			bullet->pos_x = tank->x * 25 + 23;
			bullet->pos_y = tank->y * 25 - 3;
		}
		else if (tank->direction == LEFT)
		{
			//子弹绘图坐标修正
			bullet->pos_x = tank->x * 25 - 3;
			bullet->pos_y = tank->y * 25 + 23;
		}
		else if (tank->direction == DOWN)
		{
			//子弹绘图坐标修正
			bullet->pos_x = tank->x * 25 + 23;
			bullet->pos_y = tank->y * 25 + 50;
		}
		else if (tank->direction == RIGHT)
		{
			//子弹绘图坐标修正
			bullet->pos_x = tank->x * 25 + 50;
			bullet->pos_y = tank->y * 25 + 23;
		}
		//获取子弹方向
		bullet->direction = tank->direction;
		//改变子弹状态
		bullet->status = !bullet->status;
	}
}

void gameover(int result)
{
	IMAGE img;
	if (result == 1)
	{
		loadimage(&img, _T("success_1.jpg"), 500, 250);
		putimage(80, 200, &img);
		mciSendString(_T("close cxk_1.mp3"), NULL, 0, NULL);
		PlaySound(_T("success.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	else
	{
		loadimage(&img, _T("failure.jpg"), 500, 250);
		putimage(80, 200, &img);
		mciSendString(_T("close cxk_1.mp3"), NULL, 0, NULL);
		PlaySound(_T("boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	
}

void save(int stage,Tank* enemy_tank, Tank* my_tank, Bullet* enemy_bullet, Bullet* my_bullet, int& enemy_total, int& times, int map[map_row][map_col])
{
	ofstream file_save;
	file_save.open("save.txt", ios::trunc | ios::in);
	file_save << setw(2) << stage << endl;
	file_save << enemy_total << endl;
	for (int i = 0;i<enemy_total;i++)
	{
		file_save << (enemy_tank + i)->x << " " << (enemy_tank + i)->y << " " << (enemy_tank + i)->direction << " " << (enemy_tank + i)->Is_Mycamp << " " << (enemy_tank + i)->live << endl;
		file_save << (enemy_bullet + i)->pos_x << " " << (enemy_bullet + i)->pos_y << " " << (enemy_bullet + i)->direction << " " << (enemy_bullet + i)->status << endl;
	}
	file_save << my_tank->x << " " << my_tank->y << " " << my_tank->direction << " " << my_tank->Is_Mycamp << " " << my_tank->live << endl;
	file_save << times << endl;
	for (int i = 0;i < map_row;i++)
	{
		for (int j = 0;j < map_col;j++)
		{
			file_save << map[i][j] << " ";
		}
	}
	file_save.close();
}

void read(Tank* enemy_tank, Tank* my_tank, Bullet* enemy_bullet, Bullet* my_bullet, int& enemy_total, int& times, int map[map_row][map_col])
{
	int stage;
	ifstream file_read;
	file_read.open("save.txt", ios::out);
	//移动读取的指针，因为关卡数站两个字节，还有一个回车占两个字节所以需要移动4个字节（实际移动两个字节也行，因为不会读取回车）
	file_read.seekg(4);
	file_read >> enemy_total;
	for (int i = 0;i < enemy_total;i++)
	{
		int dir_temp = 0;
		file_read >> (enemy_tank + i)->x >> (enemy_tank + i)->y >> dir_temp >> (enemy_tank + i)->Is_Mycamp >> (enemy_tank + i)->live;
		//不能用 >> 直接把值赋值给枚举常量
		switch (dir_temp)
		{
		case 0:
			(enemy_tank + i)->direction = UP;
			break;
		case 1:
			(enemy_tank + i)->direction = DOWN;
			break;
		case 2:
			(enemy_tank + i)->direction = LEFT;
			break;
		case 3:
			(enemy_tank + i)->direction = RIGHT;
			break;
		default:
			break;
		}
		file_read >> (enemy_bullet + i)->pos_x >> (enemy_bullet + i)->pos_y >> dir_temp >> (enemy_bullet + i)->status;
		switch (dir_temp)
		{
		case 0:
			(enemy_bullet + i)->direction = UP;
			break;
		case 1:
			(enemy_bullet + i)->direction = DOWN;
			break;
		case 2:
			(enemy_bullet + i)->direction = LEFT;
			break;
		case 3:
			(enemy_bullet + i)->direction = RIGHT;
			break;
		default:
			break;
		}
	}
	int mydir_temp;
	file_read >> my_tank->x >> my_tank->y >> mydir_temp >> my_tank->Is_Mycamp >> my_tank->live;
	switch (mydir_temp)
	{
	case 0:
		my_tank->direction = UP;
		break;
	case 1:
		my_tank->direction = DOWN;
		break;
	case 2:
		my_tank->direction = LEFT;
		break;
	case 3:
		my_tank->direction = RIGHT;
		break;
	default:
		break;
	}
	file_read  >> times;
	for (int i = 0;i < map_row;i++)
	{
		for (int j = 0;j < map_col;j++)
		{
			file_read >> map[i][j];
		}
	}
}