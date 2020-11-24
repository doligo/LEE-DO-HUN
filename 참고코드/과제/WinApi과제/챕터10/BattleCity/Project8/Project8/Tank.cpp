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
		m_pre_x = 0;
		m_pre_y = 0;
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
		m_pre_x = 0;
		m_pre_y = 0;
		motion = 0;
		enemy_start_x = 0;
		enemy_start_y = 0;
		move_count = 0;
		direct = DOWN;
		player = FALSE;
		status = DEAD;
		// enemy
	}
}

void Tank::Moveing(int dir)
{
	if (move_count == 0 && player == FALSE)
		direct = dir;
	else if (player == TRUE)
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


	if (player == FALSE)
		move_count++;
	if (move_count == 7)
		move_count = 0;
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

void Tank::Set_Tank_X(int num)
{
	m_ix = num;
}

void Tank::Set_Tank_Y(int num)
{
	m_iy = num;
}

Tank::~Tank()
{

}