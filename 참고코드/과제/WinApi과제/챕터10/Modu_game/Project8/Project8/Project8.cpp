#include <windows.h>
#include <iostream>
#include <vector>

#include "Title_Scene.h"
#include "Game_Scene.h"
#include "Game2_Scene.h"

#include "JEngine.h"
#include "EngineMain.h"
#include "SceneManager.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
#pragma comment(lib, "msimg32.lib") // 링커 2019 오류 뜨면 추가해주면 된다
#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "comctl32.lib")


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	JEngine::EngineMain modu("모두의 게임", 1024, 768);
	JEngine::SceneManager::GetInstance()->RegistScene(new Title_Scene);
	JEngine::SceneManager::GetInstance()->RegistScene(new Game_Scene);
	JEngine::SceneManager::GetInstance()->RegistScene(new Game2_Scene);

	// 엔진 돌아가는 원리 이해하기
	// 타이틀씬, 게임씬 게임2씬으로 추가하기

	return (int)modu.StartEngine(hInstance);
}