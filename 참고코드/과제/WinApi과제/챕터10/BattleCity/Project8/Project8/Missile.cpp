#include "Missile.h"

Missile::Missile()
{
	m_ix = 0;
	m_iy = 0;
	m_direct = 0;
	m_check_player = 0;
	m_status = FALSE;
}

void Missile::Init_Missile(int num)
{
	if (num == 0)
	{
		m_ix = 0;
		m_iy = 0;
		m_direct = 0;
		m_check_player = TRUE;
		m_status = FALSE;
	}
	else if (num > 0)
	{
		m_ix = 0;
		m_iy = 0;
		m_direct = 0;
		m_check_player = FALSE;
		m_status = FALSE;
	}
}

int Missile::Move_Missile(int dir)
{
	if (m_status == FALSE)
	{
		m_direct = dir;
		m_status = TRUE;
	}

	if (m_direct == UP)
	{
		m_iy -= 2;
	}
	else if (m_direct == DOWN)
	{
		m_iy += 2;
	}
	else if (m_direct == LEFT)
	{
		m_ix -= 2;
	}
	else if (m_direct == RIGHT)
	{
		m_ix += 2;
	}

	return 0;
}

int Missile::Get_Missile_X()
{
	return m_ix;
}

int Missile::Get_Missile_Y()
{
	return m_iy;
}

int Missile::Get_Missile_Status()
{
	return m_status;
}

int Missile::Get_Missile_Player()
{
	return m_check_player;
}

int Missile::Get_Missile_Direct()
{
	return m_direct;
}

Missile::~Missile()
{

}