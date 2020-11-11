#include "Tank.h"

Tank::Tank()
{
	m_ix = 0;
	m_iy = 0;
	motion = 0;
	direct = NULL;
	player = NULL;
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
		// player
	}
	else if (player_or_enemy > 0)
	{
		m_ix = 0;
		m_iy = 0;
		motion = 0;
		direct = DOWN;
		player = FALSE;
		// enemy
	}
}

void Tank::Moveing(int dir)
{
	direct = dir;

	if (direct == UP)
	{
		m_iy--;
	}
	else if (direct == DOWN)
	{
		m_iy++;
	}
	else if (direct == LEFT)
	{
		m_ix--;
	}
	else if (direct == RIGHT)
	{
		m_ix++;
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

Tank::~Tank()
{

}