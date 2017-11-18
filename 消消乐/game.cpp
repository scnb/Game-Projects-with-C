#include "stdafx.h"
#include "game.h"
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <time.h>
/*要播放音乐，则必须添加下面三个文件*/
#include <mmsystem.h>
#include <Windows.h>
#pragma comment (lib,"Winmm.lib") 


using std::cin;
using std::cout;
using std::endl;

COLORREF color_arr[6] = { RGB(255,0,0),RGB(0,255,0),RGB(0,0,255),RGB(255,255,0),RGB(255,0,255),RGB(0,255,255) };

PosCur pos_arr[1000];//记录相同小球的坐标

int index;//记录在一个小球周围有多少个相同的小球

int score = 0;

PosCur cur;//记录全局当前光标的位置

IMAGE img;

void game_init(void)
{
	initgraph(1000, 700);
	
	loadimage(&img, _T("F:\\编程之路\\消消乐\\消消乐\\消消乐\\pic.jpg"));//  F:\\pic.jpg"));
	putimage(200, 119, &img);
	Author_Verion();
	srand((unsigned int)time(NULL));
	settextcolor(YELLOW);
	settextstyle(40, 0, _T("黑体"));
	outtextxy(230, 32, _T("Loading……"));
	Sleep(3000);
	cleardevice();
}

void Author_Verion(void)
{
	settextcolor(WHITE);
	settextstyle(24, 0, _T("宋体"));
	/*输出数字必须要用sprintf函数把数字转换成字符串的形式*/
	outtextxy(200, 600, _T("东北大学秦皇岛分校"));
	outtextxy(200, 630, _T("商 超"));
	outtextxy(200,660,_T("3154501"));//三个参数分别是字体大小，字体粗细，文字数组
	settextstyle(32, 0, _T("微软雅黑"));
	outtextxy(760, 600, _T("V1.0"));
}

void game_begin(void)
{
	/*绘制边框*/
	setlinestyle(PS_SOLID, 10);//将画线设置为10像素粗
	setlinecolor(RGB(50,50,50));//设置画笔颜色为灰色
	rectangle(255, 45, 745, 655);//绘制矩形
	/*绘制小球（圆形）*/
	setlinestyle(PS_SOLID);//将画笔重新设置为默认值，即1像素
	for (int x = 280;x < 740;x += 40)
	{
		for(int y=70;y<650;y+=40)
		{
			/*设置画笔颜色*/
			COLORREF cl;
			cl = color_arr[rand() % 6];
			setlinecolor(cl);
			setfillcolor(cl);
			fillcircle(x, y, 18);
		}
	}
	/*绘制光标，在每次进入游戏时，初始光标可以设置在同一个合适的位置*/
	cur.x = 480;
	cur.y = 350;
	DrawCursor(cur,WHITE);
	/*绘制时间*/
	DrawTime(100);
	/*绘制得分*/
	DrawScore(0);
}

void game_play(void)
{
	for (int i = 999;i > -1;i--)
	{
		if (i % 10 == 0)
		{
			DrawTime(i / 10);
		}
		if (KEY_DOWN(VK_UP) && cur.y > 70)
		{
			DrawCursor(cur, BLACK);
			cur.y -= 40;
			DrawCursor(cur, WHITE);
		}
		else if (KEY_DOWN(VK_DOWN) && cur.y < 630)
		{
			DrawCursor(cur, BLACK);
			cur.y += 40;
			DrawCursor(cur, WHITE);
		}
		else if (KEY_DOWN(VK_LEFT) && cur.x > 280)
		{
			DrawCursor(cur, BLACK);
			cur.x -= 40;
			DrawCursor(cur, WHITE);
		}
		else if (KEY_DOWN(VK_RIGHT) && cur.x < 720)
		{
			DrawCursor(cur, BLACK);
			cur.x += 40;
			DrawCursor(cur, WHITE);
		}
		else if (KEY_DOWN(VK_SPACE)||KEY_DOWN(VK_RETURN))
		{
			/*先找到该小球周围所有颜色相同的小球，将其坐标存入数组中，并记录个数*/
			mciSendString(_T("open F:\\编程之路\\消消乐\\消消乐\\消消乐\\delete.mp3 alias delete"), 0, 0, 0);
			mciSendString(_T("play delete"), 0, 0, 0);
			mciSendString(_T("resume delete"),0, 0, 0);
			GetSameColor(cur, getpixel(cur.x, cur.y));

			/*再把这些小球的边框设置成黑色*/
			if (index > 1)
			{
				/*只要在多于1个圆的时候才能被删除*/
				for (int i = 0;i < index;i++)
				{
					setlinecolor(BLACK);
					setfillcolor(BLACK);
					fillcircle(pos_arr[i].x, pos_arr[i].y, 18);
				}
				Sleep(200);
				BallsFall();
				score += index;
				Increment(index);
				DrawScore(score);
				
			}
			index = 0;

			/*使上面的小球落下来以填充空缺的位置*/
		}
		Sleep(120);//延时120ms，防止在while循环中多次判断
	}
	mciSendString(_T("stop delete"), 0, 0, 0);
}

void game_over(void)
{
	cleardevice();
	settextcolor(RED);
	TCHAR game_over[] = _T("GAME   OVER!");
	settextstyle(150, 0, _T("微软雅黑"));
	outtextxy(85, 280, game_over);
	DrawScore(score);
	mciSendString(_T("stop playing"), NULL, 0, NULL);
	mciSendString(_T("close playing"), NULL, 0, NULL);
	Sleep(2000);
}

void game_close(void)
{
	getchar();
	closegraph();
}

void DrawCursor(PosCur pos, COLORREF cl)
{
	setlinestyle(PS_SOLID, 3);
	setlinecolor(cl);
	rectangle(pos.x - 20, pos.y - 20,pos.x + 20,pos.y + 20);
}

void DrawTime(int sec)
{
	TCHAR time[30];
	settextcolor(RED);
	settextstyle(32, 0, _T("微软雅黑"));
	/*输出数字必须要用sprintf函数把数字转换成字符串的形式*/
	_stprintf(time, _T("剩余时间：%3d"), sec); // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(10, 150, time);//三个参数分别是字体大小，字体粗细，文字数组
	outtextxy(185, 150, 's');
}



void DrawScore(int score)
{
	TCHAR str[30];
	settextcolor(YELLOW);
	settextstyle(32, 0, _T("微软雅黑"));
	/*输出数字必须要用sprintf函数把数字转换成字符串的形式*/
	_stprintf(str, _T("得分：%d 分"), score);        // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(10, 500, str);
}

void GetSameColor(PosCur cur, COLORREF cl)
{
	pos_arr[index].x = cur.x;
	pos_arr[index].y = cur.y;
	index++;
	PosCur temp;
	for (int k = 0;k < 4;k++)
	{
		switch (k)
		{
		case 0:temp.x = cur.x;temp.y = cur.y - 40;break;//检查上面的圆
		case 1:temp.x = cur.x;temp.y = cur.y + 40;break;//检查下面的圆
		case 2:temp.x = cur.x - 40;temp.y = cur.y;break;//检查左面的圆
		case 3:temp.x = cur.x + 40;temp.y = cur.y;break;//检查右面的圆
		}
		if (IsValid(temp, cl))
		{
			GetSameColor(temp,cl);
		}
	}
}

void Increment(int score)
{
	TCHAR str[10];
	settextcolor(YELLOW);
	settextstyle(50, 0, _T("幼圆"));
	_stprintf(str, _T("+ %d 分"), score);
	outtextxy(820, 330, str);
	Sleep(500);
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	clearrectangle(820, 330, 1000, 400);
}

int IsValid(PosCur cur, COLORREF cl)
{
	if (getpixel(cur.x, cur.y) != cl)//如果颜色不同，则肯定无效，直接退出
	{
		return 0;
	}
	else
	{
		/*要判断一下是否在pos_arr数组中已经存在该圆了*/
		for (int i = 0;i < index;i++)
		{
			if (cur.x == pos_arr[i].x && cur.y == pos_arr[i].y)
			{
				return 0;
			}
		}
		return 1;
	}
}

void turn()//必须要把pos_arr数组中的点按照从小到大的顺序来放，才不会导致在一个纵列上，纵坐标大的点复制了纵坐标小的点的颜色（即黑色），导致无法显示
{
	for (int i = 0;i < index;i++)
	{
		for (int j = 0;j < index - i - 1;j++)
		{
			if (pos_arr[j].x > pos_arr[j + 1].x)
			{
				PosCur temp;
				temp = pos_arr[j];
				pos_arr[j] = pos_arr[j + 1];
				pos_arr[j + 1] = temp;
			}
			if (pos_arr[j].y > pos_arr[j + 1].y)
			{
				PosCur temp;
				temp = pos_arr[j];
				pos_arr[j] = pos_arr[j + 1];
				pos_arr[j + 1] = temp;
			}
		}
	}
}

void BallsFall()
{
	COLORREF cl;
	turn();
	for (int i = 0;i < index;i++)
	{
		for (int k = pos_arr[i].y;k > 70;k -= 40)
		{
			cl = getpixel(pos_arr[i].x, k - 40);
			setlinecolor(cl);
			setfillcolor(cl);
			fillcircle(pos_arr[i].x, k, 18);
		}
		cl = color_arr[rand() % 6];
		setlinecolor(cl);
		setfillcolor(cl);
		fillcircle(pos_arr[i].x, 70, 18);
	}
	
}
