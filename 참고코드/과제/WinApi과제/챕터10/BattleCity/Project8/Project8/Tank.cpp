#include "Tank.h"

Tank::Tank()
{
	m_ix = 0;
	m_iy = 0;
	direct = NULL;
	player = NULL;
}

void Tank::Init_Tank(int player_or_enemy)
{
	if (player_or_enemy == 0)
	{
		m_ix = 0;
		m_iy = 0;
		direct = UP;
		player = TRUE;
		// player
	}
	else if (player_or_enemy > 0)
	{
		m_ix = 0;
		m_iy = 0;
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

	}
	else if (direct == DOWN)
	{

	}
	else if (direct == LEFT)
	{

	}
	else if (direct == RIGHT)
	{

	}
}

void Tank::Shot()
{

}

Tank::~Tank()
{

}