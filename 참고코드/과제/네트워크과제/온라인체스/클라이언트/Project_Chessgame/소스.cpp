#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <process.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Game_System.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//�۷ι� �ν��Ͻ��ڵ鰪
LPCTSTR lpszClass = TEXT("ü������"); //â�̸�

#pragma comment(lib, "msimg32.lib")

void ErrorHandling(const char *msg)
{
	cout << msg << "\n";
	exit(1);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	//WndClass�� �⺻ ������ȯ���� ����� ����ü��. �ɹ������� �ؿ��� ����.
	WndClass.cbClsExtra = 0; //���࿵��
	WndClass.cbWndExtra = 0; //���࿵�� (�Ű�x)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//������ ���
	WndClass.hInstance = hInstance;//(���α׷� �ڵ鰪(��ȣ)���)
	WndClass.lpfnWndProc = WndProc;	//���μ��� �Լ� ȣ��.
	WndClass.lpszClassName = lpszClass;	//Ŭ���� �̸�
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//�������� ������ ������ ���� �� �ٽ� �׸���.
	RegisterClass(&WndClass);  //������� WidClass�� ���

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))//����ڿ��� �޽����� �޾ƿ��� �Լ�(WM_QUIT �޽��� ���� �� ����)
	{
		TranslateMessage(&Message); //  Ű���� �Է� �޽��� ó���Լ�
		DispatchMessage(&Message); //���� �޽����� WndProc�� �����ϴ� �Լ�
	}
	return (int)Message.wParam;

}

HDC hdc;
Game_System gs;
int game_result = 0;
int game_over = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	int mouse_x = 0;
	int mouse_y = 0;
	int value = 0;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);

		gs.Init_System(hdc, g_hInst);

		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_TIMER:
			if (game_result == 10 && game_over == FALSE)
			{
				game_over = TRUE;

				if (MessageBox(hWnd, TEXT("�����¸�!!"), TEXT("Black Win"), MB_OK) == IDOK)
				{
					game_result = 0;
				}
			}
			else if (game_result == 20 && game_over == FALSE)
			{
				game_over = TRUE;

				if (MessageBox(hWnd, TEXT("�����¸�!!"), TEXT("White Win"), MB_OK) == IDOK)
				{
					game_result = 0;
				}
			}
		return 0;
	case WM_LBUTTONDOWN:
		mouse_x = LOWORD(lParam);
		mouse_y = HIWORD(lParam);

		game_result = gs.Click(hdc, mouse_x, mouse_y);

		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		gs.Draw(hdc);

		EndPaint(hWnd, &ps);

		return 0;
	case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
		PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
		KillTimer(hWnd, 1);
		return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.
}