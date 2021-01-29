#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")
#include"GameManager.h"
#include<crtdbg.h>
#include <iostream>
#include <winsock2.h>
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