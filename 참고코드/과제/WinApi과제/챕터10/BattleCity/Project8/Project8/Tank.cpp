#include "Tank.h"

Tank::Tank()
{
	m_ix = 0;
	m_iy = 0;
}

void Tank::Init_Tank(int player_or_enemy)
{
	if (player_or_enemy == 0)
	{
		// player
	}
	else if (player_or_enemy > 0)
	{
		// enemy
	}
}

Tank::~Tank()
{

}