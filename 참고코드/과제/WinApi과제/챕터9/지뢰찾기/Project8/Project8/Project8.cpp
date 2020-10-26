#include <windows.h>
#include <iostream>
#include <vector>
#include "resource.h"
#include "GameSystem.h"
#include <ctime>
#include <cstdlib>
using namespace std;

INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam); // 다이얼로그
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // 윈프록
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("지뢰찾기"); //창이름
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
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); // 리소스-메뉴
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);


	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		1175, 740, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	srand((unsigned int)time(NULL)); // 시간설정 (시간초)
	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

GameSystem *GS; // 전역

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	POINT mouse_pt;

	switch (iMessage)
	{
	case WM_CREATE:
		GS = new GameSystem();
		GS->Init(hWnd);
		SetTimer(hWnd, 1, 1000, NULL);
		return 0;
	case WM_TIMER:
		if (GS->check_game_start == TRUE && GS->game_over == FALSE && GS->game_clear == FALSE)
			GS->Show_Time(hWnd);
		return 0;
	case WM_LBUTTONDOWN:
		mouse_pt.x = LOWORD(lParam);
		mouse_pt.y = HIWORD(lParam);

		GS->Left_Click_Check(mouse_pt.x, mouse_pt.y);
		if (GS->game_over == TRUE)
		{
			InvalidateRect(hWnd, NULL, FALSE);
			if (MessageBox(hWnd, TEXT("재도전 하시겠습니까?"), TEXT("*게임 오바*"), MB_YESNO) == IDYES)
			{
				GS->Init(hWnd);
				GS->game_time = 0;
			}
		}
		else if (GS->game_clear == TRUE)
		{
			InvalidateRect(hWnd, NULL, FALSE);
			if (MessageBox(hWnd, TEXT("축하합니다! 다시 하시겠습니까?"), TEXT("*게임 클리어*"), MB_YESNO) == IDYES)
			{
				GS->Init(hWnd);
				GS->game_time = 0;
			}
		}

		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	case WM_RBUTTONDOWN:
		mouse_pt.x = LOWORD(lParam);
		mouse_pt.y = HIWORD(lParam);

		GS->Right_Click_Check(mouse_pt.x, mouse_pt.y);

		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_40001:
			if (MessageBox(hWnd, TEXT("새 게임을 시작합니다"), TEXT("새로하기"), MB_OKCANCEL) == IDOK)
			{
				GS->Init(hWnd);
				GS->game_time = 0;
				InvalidateRect(hWnd, NULL, FALSE);
			}
			else
				break;
			return 0;
		case ID_40002:
			if (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, AboutDlgProc) == TRUE)
			{
				GS->Init(hWnd);
				GS->game_time = 0;
				InvalidateRect(hWnd, NULL, FALSE);
			}
			return 0;
		case ID_40003:
			KillTimer(hWnd, 1);
			PostQuitMessage(0);
			return 0;
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GS->Game_Flow(hdc, hWnd);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_KEYDOWN:
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	switch (iMessage)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
		GS->now_difficulty = 0;
		return TRUE; // 윈도우에 알려준다
	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_RADIO1:
			GS->now_difficulty = 0;
			break;
		case IDC_RADIO2:
			GS->now_difficulty = 1;
			break;
		case IDC_RADIO3:
			GS->now_difficulty = 2;
			break;
		case IDOK:
			EndDialog(hDlg, 1);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
		break;
	}

	return FALSE;
}