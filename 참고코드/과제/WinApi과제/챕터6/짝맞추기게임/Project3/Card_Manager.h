#include "Card.h"
#include<time.h>
#pragma once

#define CLEAR 50

class Card_Manager
{
private:
	static Card_Manager* m_pThis;
	Card* m_cd;
	int m_score;
protected:
public:
	Card_Manager();

	static Card_Manager* GetInstance()
	{
		if (m_pThis == NULL)
		{
			m_pThis = new Card_Manager;
		}
		return m_pThis;
	}

	int count;

	void Init(HDC hdc, HINSTANCE hInst, int SpX = 1, int SpY = 1);
	void Draw(HWND hWnd, HDC hdc);
	void Click(HWND hWnd, HDC hdc, int x, int y);
	int Check_Card(HWND hWnd, HDC hdc);
	void BacktoCard(HWND hWnd);
	void Clear_And_Re(HINSTANCE hinst, HWND hWnd);
	
	~Card_Manager();
};

