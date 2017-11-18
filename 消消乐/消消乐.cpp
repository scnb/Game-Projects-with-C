//消消乐消除.cpp : 定义控制台应用程序的入口点。
//注意在用mciSendString插入音乐的时候，一定要加上绝对路径，且路径中用\\隔开
//V1.0目前背景音乐已能正常播放，但是消除小球的特效音乐只能在第一次消除时播放出来。
//V1.1添加了开头图片和作者的相关信息

#include "stdafx.h"
#include "game.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
	mciSendString(_T("open F:\\编程之路\\消消乐\\消消乐\\消消乐\\playing.mp3 alias playing"), 0, 0, 0);
	
	mciSendString(_T("play playing repeat"), 0, 0, 0);
	game_init();
	game_begin();
	game_play();
	game_over();
	game_close();
	return 0;
}

