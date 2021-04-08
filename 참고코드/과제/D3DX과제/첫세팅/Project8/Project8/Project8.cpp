#include <Windows.h>
#include <iostream>
#include <d3d9.h>
#include <d3d9types.h>
#include <vector>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT InitD3D(HWND hWnd);
void Render();

HINSTANCE g_hInst;
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;

char g_szClassName[256] = "D3D Init";
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

	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, g_szClassName, NULL };

	RegisterClassEx(&wc); // 레지스터에 등록하기

	hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		1200, 738, NULL, (HMENU)NULL, hInstance, NULL);

	if (SUCCEEDED(InitD3D(hWnd))) // 초기화 성공시
	{
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		MSG msg;

		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	else
	{
		//등록된 레지스트 winclass 릴리즈
		UnregisterClass("D3D Init", wc.hInstance);
		return 0;
	}

	/*
	ShowWindow(hWnd, nCmdShow);

	while (1)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
		}

	}

	return (int)Message.wParam;
	*/
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = NULL;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		return 0;
	case WM_KEYDOWN:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_TIMER:
		return 0;
	case WM_DESTROY:

		PostQuitMessage(0);

		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

HRESULT InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	// 디바이스를 설정해서 생성
	// 디폴트 비디오카드를 사용하고, HAL 디바이스를 생성한다.
	// 정점 처리는 모든 카드에서 지원하는 SW처리로 생성한다.
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
		return E_FAIL;

	return S_OK;
}

void Render()
{
	if (NULL == g_pD3DDevice)
		return;

	// 후면 버퍼를 파란색(0, 0, 255)으로 지운다.
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//실제 렌더링 명령들이 나열될 곳


		//렌더링 종료
		g_pD3DDevice->EndScene();
	}

	// 후면 버퍼를 보이는 화면으로 전환.
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}