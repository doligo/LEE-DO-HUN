#include <iostream>
#include <string>
#include <windows.h>
#include "resource.h"
#pragma once

using namespace std;

#define CARD_MAX 20

class Card
{
private:
	HDC MemDC; // 뒤집은상태
	HDC MemDC_Black; // 검은카드 상태

	HBITMAP m_MyCard; // 뒤집은상태
	HBITMAP m_OldCard; // 뒤집은상태

	HBITMAP m_MyCard_Black; // 검은카드 상태
	HBITMAP m_OldCard_Black; // 검은카드 상태

	SIZE m_size;
protected:
public:
	RECT rt;
	int m_posx;
	int m_posy;
	int card_number;
	int flip_over;
	Card();

	void Init(HDC hdc, HINSTANCE hinst, int x, int y, int SpX = 1, int SpY= 1);
	void Draw(HDC hdc, int SpX = 1, int SpY = 1);
	int Click(Card _card, int x, int y);

	~Card();
};

