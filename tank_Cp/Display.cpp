#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"

void display_1()
{
	//��ʼ������
	initgraph(650, 650);
	//��ʾ���˵��˵�
	IMAGE display_1_img;
	loadimage(&display_1_img, _T("display_1.png"), 650, 650);
	putimage(0, 0, &display_1_img);

	MOUSEMSG mouse; //���������Ϣ����
	IMAGE help_img;//help�˵�ͼƬ
	loadimage(&help_img, _T("help.bmp"), 650, 650);//����ͼƬ

	int finish = 1;//���ڽ������˵�ѭ��
	
	//���˵���ť����ʵ��
	while (finish) 
	{
		mouse = GetMouseMsg();

		switch (mouse.uMsg)
		{
		//help������ʾ
		case WM_MOUSEMOVE:
			if (mouse.x > 245 && mouse.x <430 && mouse.y>320 && mouse.y < 385)
				putimage(0, 0, &help_img);
			else
				putimage(0, 0, &display_1_img);
			break;
		case WM_LBUTTONDOWN:
			if (mouse.x > 245 && mouse.x < 430 && mouse.y>155 && mouse.y < 225)
			{
				setbkcolor(BLACK);//���ñ���ɫ
				cleardevice();
				int stage = 1;
				while (1)
				{
					int result = game(stage);
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
				
				
				finish = 0;
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