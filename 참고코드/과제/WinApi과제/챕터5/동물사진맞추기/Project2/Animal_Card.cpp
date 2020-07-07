#include "Animal_Card.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("동물그림");
static RECT rt[MAX_RT] = {};

Animal_Card::Animal_Card()
{

}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 여기서 처음 브러쉬
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, MemDC = 0;
	PAINTSTRUCT ps;
	HBITMAP myBitmap = 0, oldBitmap = 0;
	Animal_Card Animal;

	int x = 0;
	int y = 0;

	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		Animal.Draw(hdc, MemDC, myBitmap, oldBitmap, g_hInst, 101);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		for (int i = 0; i < 11; i++)
		{
			if (rt[i].left <= x && rt[i].right >= x && rt[i].top <= y && rt[i].bottom >= y)
			{
				Animal.Animal_Name(hWnd, i);
				break;
			}

		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void Animal_Card::Draw(HDC hdc, HDC mhdc, HBITMAP my, HBITMAP old, HINSTANCE hin, int card_num)
{
	int x = 0;
	int input_left = 0;
	int input_right = 0;

	for (int i = 0; i < 4; i++)
	{
		mhdc = CreateCompatibleDC(hdc);
		my = LoadBitmap(hin, MAKEINTRESOURCE(card_num + i));
		old = (HBITMAP)SelectObject(mhdc, my);
		BitBlt(hdc, 20 + x, 100, 145 + x, 235, mhdc, 0, 0, SRCCOPY);
		input_left = 20 + x;
		input_right = 145 + x;
		rt[i] = { input_left, 100, input_right + 15, 325 }; // 범위 차이때문에 right와 bottom의 값을 더해주었다.
		SelectObject(mhdc, old);
		DeleteObject(my);
		DeleteDC(mhdc);
		x += 150;
	}

	x = 0;

	for (int j = 4; j < 11; j++)
	{
		mhdc = CreateCompatibleDC(hdc);
		my = LoadBitmap(hin, MAKEINTRESOURCE(card_num + j));
		old = (HBITMAP)SelectObject(mhdc, my);
		BitBlt(hdc, 20 + x, 400, 145 + x, 535, mhdc, 0, 0, SRCCOPY);
		input_left = 20 + x;
		input_right = 145 + x;
		rt[j] = { input_left, 400, input_right + 15, 625 };
		SelectObject(mhdc, old);
		DeleteObject(my);
		DeleteDC(mhdc);
		x += 150;
	}
}
void Animal_Card::Animal_Name(HWND hWnd, int num)
{
	if (num == 0)
	{
		MessageBox(hWnd, TEXT("강아지"), TEXT("MessageBox"), MB_OK);
	}
	else if (num == 1)
	{
		MessageBox(hWnd, TEXT("호랑이"), TEXT("MessageBox"), MB_OK);
	}
	else if (num == 2)
	{
		MessageBox(hWnd, TEXT("오리"), TEXT("MessageBox"), MB_OK);
	}
	else if (num == 3)
	{
		MessageBox(hWnd, TEXT("코끼리"), TEXT("MessageBox"), MB_OK);
	}
	else if (num == 4)
	{
		MessageBox(hWnd, TEXT("소"), TEXT("MessageBox"), MB_OK);
	}
	else if (num == 5)
	{
		MessageBox(hWnd, TEXT("말"), TEXT("MessageBox"), MB_OK);
	}
	else if (num == 6)
	{
		MessageBox(hWnd, TEXT("고양이"), TEXT("MessageBox"), MB_OK);
	}
	else if (num == 7)
	{
		MessageBox(hWnd, TEXT("원숭이"), TEXT("MessageBox"), MB_OK);
	}
	else if (num == 8)
	{
		MessageBox(hWnd, TEXT("개구리"), TEXT("MessageBox"), MB_OK);
	}
	else if (num == 9)
	{
		MessageBox(hWnd, TEXT("닭"), TEXT("MessageBox"), MB_OK);
	}
	else if (num == 10)
	{
		MessageBox(hWnd, TEXT("NULL"), TEXT("MessageBox"), MB_OK);
	}
}

void Animal_Card::Show()
{
	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow);
	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
}

Animal_Card::~Animal_Card()
{

}