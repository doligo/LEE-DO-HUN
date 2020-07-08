#include <iostream>
#include <string>
#include <windows.h>
#pragma once

using namespace std;

class Card
{
private:
	HDC MemDC;
	HBITMAP m_MyCard;
	HBITMAP m_OldCard;
	SIZE m_size;
public:
	Card();

	void Init(HDC hdc, HINSTANCE hinst, int id);
	void Draw(HDC hdc, int x, int y, int SpX = 1, int SpY = 1);

	~Card();
};

