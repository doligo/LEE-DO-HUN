#include "All_pieces_pos.h"

All_pieces_pos::All_pieces_pos()
{

}

void All_pieces_pos::Set_All_Pawn_Pos()
{
	int num_x = 0;

	for (int i = 0; i < 16; i++)
	{
		m_All_Pawn[i].status = ALIVE;
		if (i < 8)
			m_All_Pawn[i].player_num = 0;
		else
			m_All_Pawn[i].player_num = 1;

		if (i == 0)
		{
			m_All_Pawn[i].x = 0;
			m_All_Pawn[i].y = 450;
			m_All_Pawn[i].rt = { 0, 450, 75, 525 };
		}
		else if (i < 8)
		{
			num_x += 75;
			m_All_Pawn[i].x += num_x;
			m_All_Pawn[i].y = 450;
			m_All_Pawn[i].rt = { num_x, 450, num_x + 75, 525 };
		}
		else if (i == 8)
		{
			num_x = 0;
			m_All_Pawn[i].x = 0;
			m_All_Pawn[i].y = 75;
			m_All_Pawn[i].rt = { 0, 75, 75, 150 };
		}
		else if (i < 16)
		{
			num_x += 75;
			m_All_Pawn[i].x += num_x;
			m_All_Pawn[i].y = 75;
			m_All_Pawn[i].rt = { num_x, 75, num_x + 75, 150 };
		}

	}
}

All_pieces_pos::~All_pieces_pos()
{

}