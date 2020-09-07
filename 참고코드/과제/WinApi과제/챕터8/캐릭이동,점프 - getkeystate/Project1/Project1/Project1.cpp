#include <windows.h>
#include <vector>
#include "Move_Character.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char g_szClassName[256] = "GetKeyState으로 캐릭터이동,점프 구현";
#pragma comment(lib, "msimg32.lib") // 링커 2019 오류 뜨면 추가해주면 된다.

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = g_szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

Move_Character *MC;
int Jump_Trigger = TRUE;
int Jump_Degree = 0;
int X_Trigger = TRUE;
int Y_Trigger = TRUE;


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:

		SetTimer(hWnd, 1, 10, NULL);

		MC = new Move_Character();
		MC->Init(hWnd, g_hInst);

		return 0;
	case WM_KEYDOWN:
		if (GetKeyState(VK_LEFT) & 0x8000)
		{

		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{

		}
		if (GetKeyState(VK_UP) & 0x8000)
		{

		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{

		}
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			if (Jump_Trigger == TRUE)
			{
				Jump_Trigger = FALSE;
				SetTimer(hWnd, 1, 10, NULL);
			}
		}
		return 0;
	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		MC->Draw(hdc);

		EndPaint(hWnd, &ps);

		return 0;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			MC->Jump(Jump_Degree);
			Jump_Degree += 10;
			if (Jump_Degree == 180)
			{
				Jump_Trigger = FALSE;
				KillTimer(hWnd, 1);
				Jump_Degree = 0;
			}
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		}

		InvalidateRect(hWnd, NULL, TRUE);

		return 0;

	case WM_DESTROY:

		delete MC;
		KillTimer(hWnd, 1);
		PostQuitMessage(0);

		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
