#pragma once
#ifndef GAME_H_
#define GAME_H_

//#pragma comment(lib,"Winmm.lib")


#include <graphics.h>
#include <conio.h>

#define KEY_DOWN(vk_c) (GetAsyncKeyState(vk_c)&0x8000?1:0)


/*定义位置结构体*/

typedef struct Position PosCur;

struct Position
{
	int x;
	int y;
};


void game_init(void);
void Author_Verion(void);
void game_begin(void);
void game_play(void);
void Increment(int score);
void game_over(void);
void game_close(void);
void DrawCursor(PosCur pos, COLORREF cl);
void DrawTime(int sec);
void DrawScore(int score);
void GetSameColor(PosCur cur, COLORREF cl);
int IsValid(PosCur cur, COLORREF cl);
void BallsFall();
void turn();

#endif // !GAME_H_

