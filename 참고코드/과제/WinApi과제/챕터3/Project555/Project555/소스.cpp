#include<windows.h>
#include <iostream>
using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//�۷ι� �ν��Ͻ��ڵ鰪
LPCTSTR lpszClass = TEXT("����"); //â�̸�


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
		switch (iMessage) // 1������
		{
		case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
			PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
			return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
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

		switch (iMessage) // 2������
		{
		case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
			PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
			return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
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




		switch (iMessage) // 3������
		{
		case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
			PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
			return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
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

	switch (iMessage) // 4������
	{
	case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
		PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
		return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (trigger == FALSE)
			Ellipse(hdc, 150, 200, 500, 500); // left, top, right, bottom
		else
			Rectangle(hdc, 150, 200, 500, 500);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_LBUTTONDOWN:
		if (MessageBox(hWnd, TEXT("������ �ٲߴϴ�"), TEXT("����"), MB_OKCANCEL) == IDOK)
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

	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.

}
