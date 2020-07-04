#include<windows.h>
#include <math.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("아날로그 시계");

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;
	static TCHAR sTime[128];
	int num = 0;
	HPEN MyPen, OldPen;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_TIMER:
		GetLocalTime(&st);
		wsprintf(sTime, TEXT("=현재 시각 %d:%d:%d="), st.wHour, st.wMinute, st.wSecond);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 230, 100, sTime, lstrlen(sTime));

		Ellipse(hdc, 200, 200, 400, 400);

		GetLocalTime(&st);

		for (num = 1; num < 13; num++)
		{
			wsprintf(sTime, "%d", num);
			TextOut(hdc, 300 + 100 * cos((270 + 30 * num) * 3.141592 / 180), 300 + 100 * sin((270 + 30 * num) * 3.141592 / 180), sTime, lstrlen(sTime));
		}

		///////////// 초, 분, 시

		MoveToEx(hdc, 300, 300, NULL);
		LineTo(hdc, 300 + 100 * cos((270 + 6 * st.wSecond) * 3.141592 / 180), 300 + 100 * sin((270 + 6 * st.wSecond) * 3.141592 / 180));

		MoveToEx(hdc, 300, 300, NULL);
		LineTo(hdc, 300 + 80 * cos((270 + 6 * st.wMinute + st.wSecond / 10) * 3.141592 / 180), 300 + 80 * sin((270 + 6 * st.wMinute + st.wSecond / 10) * 3.141592 / 180));

		MoveToEx(hdc, 300, 300, NULL);
		LineTo(hdc, 300 + 60 * cos((270 + 30 * st.wHour + st.wMinute / 2) * 3.141592 / 180), 300 + 60 * sin((270 + 30 * st.wHour + st.wMinute / 2) * 3.141592 / 180));

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
