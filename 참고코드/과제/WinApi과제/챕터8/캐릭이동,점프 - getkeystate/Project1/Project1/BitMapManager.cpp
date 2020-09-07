#include "BitMapManager.h"

BitMapManager* BitMapManager::m_pThis = NULL;

BitMapManager::BitMapManager()
{
}

void BitMapManager::Init(HWND hWnd, HDC hdc, HINSTANCE hInst)
{
	int num = 0;

	HDC hdc = GetDC(hWnd);
	m_bt = new BitMap;
	m_bt->Init(hWnd, hdc, hInst, num);
}

void BitMapManager::Draw(HDC hdc, int x, int y)
{
	m_bt->Draw(hdc, x, y);
}

void BitMapManager::Release()
{
	delete(m_pThis);
}

BitMapManager::~BitMapManager()
{
	delete(m_bt);
}
