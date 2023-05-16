#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"

void display_1()
{
	//初始化窗口
	initgraph(650, 650);
	//显示主菜单菜单
	IMAGE display_1_img;
	loadimage(&display_1_img, _T("display_1.jpg"), 650, 650);
	putimage(0, 0, &display_1_img);

	MOUSEMSG mouse; //储存鼠标信息变量
	IMAGE help_img;//help菜单图片
	loadimage(&help_img, _T("help.png"), 650, 650);//加载图片

	//int finish = 1;//用于结束主菜单循环
	
	//主菜单按钮功能实现
	while (1) 
	{
		mouse = GetMouseMsg();

		switch (mouse.uMsg)
		{
		//help功能显示
		case WM_MOUSEMOVE:
			if (mouse.x > 245 && mouse.x <430 && mouse.y>320 && mouse.y < 385)
				putimage(0, 0, &help_img);
			else
				putimage(0, 0, &display_1_img);
			break;
		case WM_LBUTTONDOWN:
			if (mouse.x > 245 && mouse.x < 430 && mouse.y>155 && mouse.y < 225)
			{
				//setbkcolor(BLACK);//设置背景色
				//cleardevice();
				int stage = 1;
				while (1)
				{
					int result = game(stage, 0);
					gameover(result);
					while (1)
					{
						system("pause");
						if (KEY_DOWN(Key_ENTER))
							break;
					}
					if (result)
						stage++;
				}
				break;
			
			}
				
			else if (mouse.x > 245 && mouse.x < 430 && mouse.y>235 && mouse.y < 300)
			{
				int stage = 1;
				fstream file;
				file.open("save.txt");
				file >> stage;
				int choice=1;
				while (1)
				{
		
					int result = game(stage, choice);
					gameover(result);
					while (1)
					{
						system("pause");
						if (KEY_DOWN(Key_ENTER))
							break;
					}
					if (result)
						stage++;
					choice = 0;
				}
				break;
			}
			else if (mouse.x > 245 && mouse.x < 430 && mouse.y>400 && mouse.y < 470)
			{
				exit(0);
				break;
			}
		}


	}
}