#include "Move_Character.h"

Move_Character::Move_Character()
{

}

void Move_Character::Init(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);
	MemDC = CreateCompatibleDC(hdc);

	m_BitMap = (HBITMAP)LoadImage(NULL, TEXT("image.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_Old_BitMap = (HBITMAP)SelectObject(MemDC, m_BitMap);


	GetObject(m_BitMap, sizeof(B_Info), &B_Info);
	m_size.cx = B_Info.bmWidth;
	m_size.cy = B_Info.bmHeight;

	x = 300;
	y = 500;
	jump_y = 0;
	jump_x = 0;
}

void Move_Character::Draw(HDC hdc)
{
	TransparentBlt(hdc, x + jump_x, y + jump_y, m_size.cx / 4, m_size.cy / 4, MemDC, 0, 0, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
}

void Move_Character::Jump(int degree)
{
	jump_y = sin(degree * 3.14 / 180) * -50;
	jump_x = cos(degree * 3.14 / 180) * -30;
}

Move_Character::~Move_Character()
{
	DeleteObject(m_BitMap);
	DeleteDC(MemDC);
}