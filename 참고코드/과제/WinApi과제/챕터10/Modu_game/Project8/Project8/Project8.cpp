#include <windows.h>
#include <iostream>
#include <vector>
#include "JEngine.h"
#include "EngineMain.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char g_szClassName[256] = "모두의 게임";
#pragma comment(lib, "msimg32.lib") // 링커 2019 오류 뜨면 추가해주면 된다
#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "comctl32.lib")


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{

	JEngine::EngineMain modu("모두의 게임", 1024, 768);
	// 엔진 돌아가는 원리 이해하기 ( 함수들 )
	// 타이틀씬, 게임씬 순서로 추가하기

	return (int)modu.StartEngine(hInstance);
}