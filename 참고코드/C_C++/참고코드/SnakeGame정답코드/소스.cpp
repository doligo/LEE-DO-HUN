#include<iostream>
#include<crtdbg.h>
#include"SnakeGame.h"
#include"Mecro.h"
using namespace std;

void main()
{
	srand(time(NULL));
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_crtBreakAlloc = 979;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", HEIGHT+3, WIDTH*2+1);
	system(buf);
	SnakeGame snakegame;
	snakegame.Display();
}