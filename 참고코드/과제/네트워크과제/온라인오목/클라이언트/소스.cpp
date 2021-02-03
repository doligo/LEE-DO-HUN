#include"GameManager.h"
#include<crtdbg.h>
#include <iostream>
#include <stdlib.h>
#include <process.h>
using namespace std;

void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_crtBreakAlloc = 979;

	GameManager gameManager;
	gameManager.GameMain();
}