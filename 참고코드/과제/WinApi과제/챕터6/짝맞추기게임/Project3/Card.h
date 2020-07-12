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
	HDC MemDC; // ����������
	HDC MemDC_Black; // ����ī�� ����

	HBITMAP m_MyCard; // ����������
	HBITMAP m_OldCard; // ����������

	HBITMAP m_MyCard_Black; // ����ī�� ����
	HBITMAP m_OldCard_Black; // ����ī�� ����

	SIZE m_size;
protected:
public:
	RECT rt;
	int m_posx;
	int m_posy;
	int card_number;
	int flip_over;
	Card();

	void Init(HDC hdc, HINSTANCE hinst, int id, int x, int y, int SpX = 1, int SpY = 1);
	void Draw(HDC hdc, HINSTANCE hinst, int SpX = 1, int SpY = 1);

	~Card();
};

