#include "Tank.h"

Tank::Tank()
{
	m_ix = 0;
	m_iy = 0;
	motion = 0;
	direct = NULL;
	player = NULL;
	status = DEAD;
}

void Tank::Init_Tank(int player_or_enemy)
{
	if (player_or_enemy == 0)
	{
		m_ix = 0;
		m_iy = 0;
		motion = 0;
		direct = UP;
		player = TRUE;
		status = DEAD;
		player_start_x = 400;
		player_start_y = 600;
		// player
	}
	else if (player_or_enemy > 0)
	{
		m_ix = 0;
		m_iy = 0;
		motion = 0;
		direct = DOWN;
		player = FALSE;
		status = DEAD;
		// enemy
	}
}

void Tank::Moveing(int dir)
{
	direct = dir;

	m_pre_x = m_ix;
	m_pre_y = m_iy;

	if (direct == UP)
	{
		m_iy -= 2;
	}
	else if (direct == DOWN)
	{
		m_iy += 2;
	}
	else if (direct == LEFT)
	{
		m_ix -= 2;
	}
	else if (direct == RIGHT)
	{
		m_ix += 2;
	}

	if (motion == 0)
		motion = 1;
	else if (motion == 1)
		motion = 0;
}

void Tank::Shot()
{

}

int Tank::Get_Tank_X()
{
	return m_ix;
}

int Tank::Get_Tank_Y()
{
	return m_iy;
}

int Tank::Get_Tank_Direct()
{
	return direct;
}

int Tank::Get_Tank_Motion()
{
	return motion;
}

int Tank::Get_Player_Check()
{
	return player;
}

int Tank::Get_Status()
{
	return status;
}

void Tank::Set_Status(int value)
{
	status = value;
}

void Tank::RollBack_pos()
{
	m_ix = m_pre_x;
	m_iy = m_pre_y;
}

Tank::~Tank()
{

}