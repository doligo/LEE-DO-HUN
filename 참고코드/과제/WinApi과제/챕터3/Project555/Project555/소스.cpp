#include<windows.h>
#include <iostream>
using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//글로벌 인스턴스핸들값
LPCTSTR lpszClass = TEXT("게임"); //창이름


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	//WndClass는 기본 윈도우환경을 만드는 구조체다. 맴버변수는 밑에와 같다.
	WndClass.cbClsExtra = 0; //예약영역
	WndClass.cbWndExtra = 0; //예약영역 (신경x)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//아이콘 모양
	WndClass.hInstance = hInstance;//(프로그램 핸들값(번호)등록)
	WndClass.lpfnWndProc = WndProc;	//프로세스 함수 호출.
	WndClass.lpszClassName = lpszClass;	//클레스 이름
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//윈도우의 수직과 수평이 변경 시 다시 그린다.
	RegisterClass(&WndClass);  //만들어진 WidClass를 등록

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))//사용자에게 메시지를 받아오는 함수(WM_QUIT 메시지 받을 시 종료)
	{
		TranslateMessage(&Message); //  키보드 입력 메시지 처리함수
		DispatchMessage(&Message); //받은 메시지를 WndProc에 전달하는 함수
	}
	return (int)Message.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int trigger = FALSE;
	RECT rt = { 0, 0, 400, 400 };
	RECT rt2;
	static int x = 0;
	static int y = 0;

	/*
		switch (iMessage) // 1번문제
		{
		case WM_DESTROY:// 윈도우가 파괴되었다는 메세지
			PostQuitMessage(0); //GetMessage함수에 WM_QUIT 메시지를 보낸다.
			return 0; //WndProc의 Switch는 break 대신 return 0; 를 쓴다.
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			Ellipse(hdc, 220 + x, 100 + y, 350 + x, 200 + y); // left, top, right, bottom

			EndPaint(hWnd, &ps);
			return 0;
		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_LEFT:
				x -= 10;
				break;
			case VK_RIGHT:
				x += 10;
				break;
			case VK_UP:
				y -= 10;
				break;
			case VK_DOWN:
				y += 10;
				break;
			}

			InvalidateRect(hWnd, NULL, TRUE);

			return 0;
		}


		/////////////////////////////////////////////////////


		GetClientRect(hWnd, &rt2);

		switch (iMessage) // 2번문제
		{
		case WM_DESTROY:// 윈도우가 파괴되었다는 메세지
			PostQuitMessage(0); //GetMessage함수에 WM_QUIT 메시지를 보낸다.
			return 0; //WndProc의 Switch는 break 대신 return 0; 를 쓴다.
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			Ellipse(hdc, x - 30, y - 30, 40 + x, 20 + y); // left, top, right, bottom

			EndPaint(hWnd, &ps);
			return 0;
		case WM_MOUSEMOVE:
			x = LOWORD(lParam);
			y = HIWORD(lParam);

			if (x + 40 >= rt2.right || y + 40 >= rt2.bottom || x <= 40 || y <= 40)
				break;
			InvalidateRect(hWnd, NULL, TRUE);

			return 0;
		}



		////////////////////////////////////////////////////////////




		switch (iMessage) // 3번문제
		{
		case WM_DESTROY:// 윈도우가 파괴되었다는 메세지
			PostQuitMessage(0); //GetMessage함수에 WM_QUIT 메시지를 보낸다.
			return 0; //WndProc의 Switch는 break 대신 return 0; 를 쓴다.
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			Ellipse(hdc, x - 30, y - 30, 40 + x, 20 + y); // left, top, right, bottom

			EndPaint(hWnd, &ps);
			return 0;
		case WM_MOUSEMOVE:
			x = LOWORD(lParam);
			y = HIWORD(lParam);

			if (x + 40 >= rt.right || y + 40 >= rt.bottom || x <= 40 || y <= 40)
				break;

			InvalidateRect(hWnd, &rt, TRUE);

			return 0;
		}


		*/
		/////////////////////////////////////////////

	switch (iMessage) // 4번문제
	{
	case WM_DESTROY:// 윈도우가 파괴되었다는 메세지
		PostQuitMessage(0); //GetMessage함수에 WM_QUIT 메시지를 보낸다.
		return 0; //WndProc의 Switch는 break 대신 return 0; 를 쓴다.
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (trigger == FALSE)
			Ellipse(hdc, 150, 200, 500, 500); // left, top, right, bottom
		else
			Rectangle(hdc, 150, 200, 500, 500);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_LBUTTONDOWN:
		if (MessageBox(hWnd, TEXT("도형을 바꿉니다"), TEXT("선택"), MB_OKCANCEL) == IDOK)
		{
			if (trigger == FALSE)
				trigger = TRUE;
			else
				trigger = FALSE;
		}
		else
			break;

		InvalidateRect(hWnd, NULL, TRUE);

		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case에 있는 메시지를 제외한 나머지 메시지를 처리한다.

}
