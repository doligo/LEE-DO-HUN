#include "Player.h"

Player::Player()
{

}

void Player::Init_Player(HDC hdc, int player_num)
{
	Cp = new chess_pieces;

	Cp->Init_pieces(hdc, player_num);
	Cp->Init_pieces_2(hdc, player_num);
}

void Player::Player_Pieces_Draw(HDC hdc)
{
	char buf[30] = {};

	Cp->Pieces_Draw(hdc, Cp->m_King.x, Cp->m_King.y, "king");
	Cp->Pieces_Draw(hdc, Cp->m_Queen.x, Cp->m_Queen.y, "queen");
	Cp->Pieces_Draw(hdc, Cp->m_Rook[0].x, Cp->m_Rook[0].y, "rook1");
	Cp->Pieces_Draw(hdc, Cp->m_Rook[1].x, Cp->m_Rook[1].y, "rook2");
	Cp->Pieces_Draw(hdc, Cp->m_Bishop[0].x, Cp->m_Bishop[0].y, "bishop1");
	Cp->Pieces_Draw(hdc, Cp->m_Bishop[1].x, Cp->m_Bishop[1].y, "bishop2");
	Cp->Pieces_Draw(hdc, Cp->m_Knight[0].x, Cp->m_Knight[0].y, "knight1");
	Cp->Pieces_Draw(hdc, Cp->m_Knight[1].x, Cp->m_Knight[1].y, "knight2");

	for (int i = 0; i < 8; i++)
	{
		sprintf_s(buf, "pawn%d", i + 1);
		Cp->Pieces_Draw(hdc, Cp->m_Pawn[i].x, Cp->m_Pawn[i].y, buf);
	}
}

Player::~Player()
{

}