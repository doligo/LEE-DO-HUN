#include<windows.h>
#include "Card.h"
#include "Card_Manager.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("그림맞추기");


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
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
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

HDC hdc;
PAINTSTRUCT ps;
Card_Manager cm;
Card cd;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int num = 0;
	int card_num = 0;
	int mouse_x = 0;
	int mouse_y = 0;
	int value = 0;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 500, NULL);

		cm.GetInstance();
		cm.Init(hdc, g_hInst);

		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_TIMER:
		if (cm.count == 2)
		{
			value = cm.Check_Card(hWnd, hdc);
			if (value == TRUE)
			{
				cm.count = 0;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			else if (value == CLEAR)
			{
				if (MessageBox(hWnd, TEXT("클리어 했습니다 다시하려면 Y를 눌러주세요"), TEXT("Clear"), MB_YESNO) == IDYES)
				{
					value = 0;
					cm.Clear_And_Re(g_hInst, hWnd);
				}
				else
				{
					break;
				}
			}
			else
			{
				Sleep(1500);
				cm.BacktoCard(hWnd);
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		return 0;
	case WM_LBUTTONDOWN:
		mouse_x = LOWORD(lParam);
		mouse_y = HIWORD(lParam);

		cm.Click(hWnd, hdc, mouse_x, mouse_y);

		InvalidateRect(hWnd, NULL, TRUE);

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		cm.Draw(hWnd, hdc);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		DeleteDC(hdc);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
