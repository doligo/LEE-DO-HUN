#include "Move_Character.h"

Move_Character::Move_Character()
{

}

void Move_Character::Init(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);

	MemDC[0] = CreateCompatibleDC(hdc);
	m_BitMap[0] = CreateCompatibleBitmap(hdc, 1024, 768);
	m_Old_BitMap[0] = (HBITMAP)SelectObject(MemDC[0], m_BitMap[0]);

	MemDC[1] = CreateCompatibleDC(MemDC[0]);
	m_BitMap[1] = (HBITMAP)LoadImage(NULL, TEXT("image.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_BitMap[1] = (HBITMAP)SelectObject(MemDC[1], m_BitMap[1]);

	MemDC[2] = CreateCompatibleDC(MemDC[0]);
	m_BitMap[2] = (HBITMAP)LoadImage(NULL, TEXT("back.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_BitMap[2] = (HBITMAP)SelectObject(MemDC[2], m_BitMap[2]);

	GetObject(m_BitMap[1], sizeof(B_Info), &B_Info);
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
	Jump_Degree = 0;
}

void Move_Character::Draw(HDC hdc)
{
	BitBlt(MemDC[0], 0, 0, 1024, 768, MemDC[2], 0, 0, RGB(255, 0, 255));
	TransparentBlt(MemDC[0], x + jump_x, y + jump_y + jump_y_2, m_size.cx / 4, m_size.cy / 4, MemDC[1], (m_size.cx / 4) * pose, (m_size.cy / 4) * direct, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
	BitBlt(hdc, 0, 0, 1024, 768, MemDC[0], 0, 0, SRCCOPY);
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

void Move_Character::Key_Up()
{
	pre_direct = direct;
	direct = 1;
	if (pre_direct == direct)
		pose++;
	else
		pose = 0;

	if (pose == 4)
		pose = 0;
	Double_Check = TRUE;

	Move_Y(-5);

}

void Move_Character::Key_Down()
{
	pre_direct = direct;
	direct = 0;
	if (pre_direct == direct)
		pose++;
	else
		pose = 0;

	if (pose == 4)
		pose = 0;
	Double_Check = TRUE;

	Move_Y(+5);
}

void Move_Character::Key_Left()
{
	if (Double_Check != TRUE)
	{
		pre_direct = direct;
		direct = 2;
		if (pre_direct == direct)
			pose++;
		else
			pose = 0;

		if (pose == 4)
			pose = 0;
	}
	else
	{
		pre_direct = direct;
		if (pre_direct == direct)
			pose++;
		else
			pose = 0;

		if (pose == 4)
			pose = 0;
	}

	Move_X(-5);
}

void Move_Character::Key_Right()
{
	if (Double_Check != TRUE)
	{
		pre_direct = direct;
		direct = 3;
		if (pre_direct == direct)
			pose++;
		else
			pose = 0;

		if (pose == 4)
			pose = 0;
	}
	else
	{
		pre_direct = direct;
		if (pre_direct == direct)
			pose++;
		else
			pose = 0;

		if (pose == 4)
			pose = 0;
	}

	Move_X(+5);

}

Move_Character::~Move_Character()
{
	for (int i = 0; i < 3; i++)
	{
		DeleteObject(m_BitMap[i]);
		DeleteDC(MemDC[i]);
	}
}