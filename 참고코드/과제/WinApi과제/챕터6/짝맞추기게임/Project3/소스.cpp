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
Card* cd = NULL;
Card_Manager cm;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int x = 20;
	int y = 20;
	int num = 0;
	int card_num = 0;
	int mouse_x = 0;
	int mouse_y = 0;
	int flip_chage = FALSE;

	switch (iMessage)
	{
	case WM_CREATE:
		cd = new Card[CARD_MAX];

		for (int i = 0; i < CARD_MAX; i++)
		{
			if (num == 10)
			{
				x = 20;
				y += 250;
				card_num = 0;
			}

			cd[i].Init(hdc, g_hInst, IDB_BITMAP1 + card_num, x, y);

			x += 140;
			card_num++;
			num++;

		}
		return 0;
	case WM_LBUTTONDOWN:
		mouse_x = LOWORD(lParam);
		mouse_y = HIWORD(lParam);

		flip_chage = cm.Click(cd[0], mouse_x + 10, mouse_y + 10);
		if (flip_chage == TRUE)
			cd[0].flip_over = TRUE;

		InvalidateRect(hWnd, NULL, TRUE);
		flip_chage = FALSE;

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		for (int i = 0; i < CARD_MAX; i++)
		{
			cd[i].Draw(hdc, g_hInst);
		}

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}