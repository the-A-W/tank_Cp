#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"

void display_1()
{
	//初始化窗口
	initgraph(650, 650);
	//显示主菜单菜单
	IMAGE display_1_img;
	loadimage(&display_1_img, _T("display_1.png"), 650, 650);
	putimage(0, 0, &display_1_img);

	MOUSEMSG mouse; //储存鼠标信息变量
	IMAGE help_img;//help菜单图片
	loadimage(&help_img, _T("help.bmp"), 650, 650);//加载图片

	bool finish = true;//用于结束主菜单循环
	
	//主菜单按钮功能实现
	while (finish) 
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
				setbkcolor(BLACK);//设置背景色
				cleardevice();
				bool result=game(2);
				gameover(result);
				system("pause");
				
				finish = false;
				break;
			}
			else if (mouse.x > 245 && mouse.x < 430 && mouse.y>235 && mouse.y < 300)
			{
				/*Log_in();*/
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