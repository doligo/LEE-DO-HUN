#include <windows.h>
#include <iostream>
#include <vector>

#include "Title_Scene.h"
#include "Select_Scene.h"
#include "Game_Scene.h"
#include "Game2_Scene.h"

#include "JEngine.h"
#include "EngineMain.h"
#include "SceneManager.h"
#include <Windows.h>
#include <time.h>
#include <stdio.h>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
#pragma comment(lib, "msimg32.lib") // 링커 2019 오류 뜨면 추가해주면 된다
#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "comctl32.lib")


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	srand((unsigned int)time(NULL));

	JEngine::EngineMain modu("모두의 게임", 414, 642);
	JEngine::SceneManager::GetInstance()->RegistScene(new Title_Scene); //0
	JEngine::SceneManager::GetInstance()->RegistScene(new Select_Scene); //1
	JEngine::SceneManager::GetInstance()->RegistScene(new Game_Scene); //2
	JEngine::SceneManager::GetInstance()->RegistScene(new Game2_Scene); //3

	// 앵커함수는 글자정렬과 같은의미로 쓸수있다

	return (int)modu.StartEngine(hInstance);
}