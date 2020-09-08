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
	jump_y_2 = 0;
	jump_x = 0;
	direct = 0;
	pre_direct = 0;
	pose = 0;
}

void Move_Character::Draw(HDC hdc)
{
	TransparentBlt(hdc, x + jump_x, y + jump_y + jump_y_2, m_size.cx / 4, m_size.cy / 4, MemDC, (m_size.cx / 4) * pose, (m_size.cy / 4) * direct, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
}

void Move_Character::Jump(int degree)
{
	jump_y = sin(degree * 3.14 / 180) * -50;

	if (direct == 2)
		jump_x -= 2;
	else if (direct == 3)
		jump_x += 2;
	else if (direct == 1)
		jump_y_2 -= 2;
	else if (direct == 0)
		jump_y_2 += 2;
}

void Move_Character::Move_X(int x)
{
	this->x += x;
}

void Move_Character::Move_Y(int y)
{
	this->y += y;
}

Move_Character::~Move_Character()
{
	DeleteObject(m_BitMap);
	DeleteDC(MemDC);
}