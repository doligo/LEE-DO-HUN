#include "Player.h"

Player::Player()
{
	m_pStoneList = NULL;
	m_iStoneCount = 0;
	m_bMyWindState = false;
	m_iUndo = DEFAULT_UNDO;
}


bool Player::CompareStone(int x, int y)
{
	for(int i = 0; i < m_iStoneCount; i++)
	{
		if(m_pStoneList[i].m_ix == x &&m_pStoneList[i].m_iy == y)
			return true;
	}
	return false;
}

void Player::AllStoneDraw()
{

	for(int i = 0; i < m_iStoneCount; i++)
		m_DrawManager.DrawPoint(m_strStoneIcon, m_pStoneList[i].m_ix, m_pStoneList[i].m_iy);
}

void Player::DrawStone(int x, int y)
{
	if(CompareStone(x, y))
		m_DrawManager.DrawPoint(m_strStoneIcon, x, y);
}


void Player::Undo(int Width, int Height)
{
	m_iStoneCount--;
	m_DrawManager.Erase(m_pStoneList[m_iStoneCount].m_ix, m_pStoneList[m_iStoneCount].m_iy, Width, Height);
}

void Player::CreateStone()
{
	if(CompareStone(m_Cursor.m_ix, m_Cursor.m_iy) == false)
	{
		m_pStoneList[m_iStoneCount].m_ix = m_Cursor.m_ix;
		m_pStoneList[m_iStoneCount++].m_iy = m_Cursor.m_iy;
		DrawStone(m_Cursor.m_ix, m_Cursor.m_iy);
	}
}

void Player::Move(char ch, int Width, int Height)
{
	switch(ch)
	{
		case KEY_LEFT:
			if(m_Cursor.m_ix - 1 >= 0)
				m_Cursor.m_ix--;
			break;
		case KEY_RIGHT:
			if(m_Cursor.m_ix + 1 < Width)
				m_Cursor.m_ix++;
			break;
		case KEY_UP:
			if(m_Cursor.m_iy - 1 >= 0)
				m_Cursor.m_iy--;
			break;
		case KEY_DOWN:
			if(m_Cursor.m_iy + 1 < Height)
				m_Cursor.m_iy++;
			break;
	}
}


void Player::EraseCursor(int Width, int Height)
{

	m_DrawManager.Erase(m_Cursor.m_ix, m_Cursor.m_iy,Width,Height);
}

void Player::DrawCursor()
{
	m_DrawManager.DrawPoint(m_strCursorIcon, m_Cursor.m_ix, m_Cursor.m_iy);
}

void Player::DeleteStone()
{
	if(m_pStoneList != NULL)
	{
		delete[] m_pStoneList;
		m_pStoneList = NULL;
	}
}

void Player::PlayerSet(int Width,int Height)
{
	DeleteStone();
	m_pStoneList = new Point[(Width*Height) / 2];
	m_iStoneCount = 0;
	m_Cursor.m_ix = Width * 0.5f;
	m_Cursor.m_iy = Height* 0.5f;
	m_bMyWindState = false;
}



int Player::NextStoneCheck(int x, int y, int addx, int addy,int Width, int Height)
{
	int count = 0;
	for(; (x >= 0 && x < Width) && (y >= 0 && y < Height); x += addx, y += addy)
	{
		if(CompareStone(x, y))
			count++;
		else
			break;
	}
	return count;
}

bool Player::WinCheck(int Width, int Height)
{
	int Count = 0;
	Count += NextStoneCheck(m_Cursor.m_ix - 1, m_Cursor.m_iy, -1, 0, Width, Height);
	Count += NextStoneCheck(m_Cursor.m_ix + 1, m_Cursor.m_iy, 1, 0, Width, Height);
	if(Count + 1 == 5) //가로 검사
		return true;
	Count = 0;	
	Count += NextStoneCheck(m_Cursor.m_ix, m_Cursor.m_iy -1, 0, -1, Width, Height);
	Count += NextStoneCheck(m_Cursor.m_ix, m_Cursor.m_iy+1, 0, 1, Width, Height);
	if(Count + 1 == 5)//세로검사
		return true;
	Count = 0;
	Count += NextStoneCheck(m_Cursor.m_ix - 1, m_Cursor.m_iy-1, -1, -1, Width, Height);
	Count += NextStoneCheck(m_Cursor.m_ix + 1, m_Cursor.m_iy+1, 1, 1, Width, Height);
	if(Count + 1 == 5)//왼쪽대각선
		return true;
	Count = 0;
	Count += NextStoneCheck(m_Cursor.m_ix + 1, m_Cursor.m_iy-1, 1, -1, Width, Height);
	Count += NextStoneCheck(m_Cursor.m_ix - 1, m_Cursor.m_iy+1, -1, 1, Width, Height);
	if(Count + 1 == 5)//오른쪽대각선
		return true;

	return false;
}

Player::~Player()
{
	if(m_pStoneList != NULL)
		delete[] m_pStoneList;
}
