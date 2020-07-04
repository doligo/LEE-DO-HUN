#include<windows.h>
#include<time.h>
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BallMove");
void DrawCircle(HDC hdc, int x, int y);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimeProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
using namespace std;
#define RIGHT_UP 10
#define RIGHT_DOWN 11
#define LEFT_UP 12
#define LEFT_DOWN 13

#define STOP 50

int x = 0;
int y = 0;
RECT rect;
int my_direct = NULL;
int status = 0;

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

	srand((unsigned)time(NULL));
	x = (rand() % 800);
	y = (rand() % 500);

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
	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;
	static TCHAR sTime[128];

	GetClientRect(hWnd, &rect);

	switch (iMessage)
	{
	case WM_CREATE:
		if (my_direct == NULL)
		{
			my_direct = rand() % 4 + 10;
		}
		SetTimer(hWnd, 1, 100, TimeProc);
		//SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Ellipse(hdc, x, y, x + 50, y + 50);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void CALLBACK TimeProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{

	if (x + 50 >= rect.right || y - 50 <= rect.top || x - 50 <= rect.left || y + 50 >= rect.bottom)
	{
		status = STOP;
	}

	if (status == STOP)
	{
		my_direct = rand() % 4 + 10;
		status = 0;
		if (x + 50 >= rect.right)
			x -= 10;
		if (y + 50 >= rect.bottom)
			y -= 10;
		if (x - 50 <= rect.left)
			x += 10;
		if (y - 50 <= rect.top)
			y += 10;
	}

	if (my_direct == RIGHT_UP)
	{
		x += 10;
		y -= 10;
	}
	else if (my_direct == RIGHT_DOWN)
	{
		x += 10;
		y += 10;
	}
	else if (my_direct == LEFT_UP)
	{
		x -= 10;
		y -= 10;
	}
	else if (my_direct == LEFT_DOWN)
	{
		x -= 10;
		y += 10;
	}

	InvalidateRect(hWnd, NULL, TRUE);
}