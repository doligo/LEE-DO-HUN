#include <iostream>
#include <Windows.h>
#include <string.h>
#pragma once

class BitMap
{
private:
	HDC g_playerDC, g_backDC;
	HBITMAP g_btPlayer, g_btBack;
	HBITMAP g_btOldPlayer, g_btOldBack;
	BITMAP g_mapInfo;
	SIZE g_size;
public:
	BitMap();

	void Init(HWND hWnd, HDC hdc, HINSTANCE hInst, int id);
	void Draw(HDC hdc, int x, int y);
	~BitMap();
};

