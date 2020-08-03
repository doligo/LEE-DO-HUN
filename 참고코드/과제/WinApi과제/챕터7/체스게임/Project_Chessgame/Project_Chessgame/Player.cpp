#include "Player.h"

Player::Player()
{

}

void Player::Init_Player(HDC hdc, int player_num)
{
	Cp = new chess_pieces;

	Cp->Init_pieces(hdc, player_num);
}

void Player::Player_Pieces_Draw(HDC hdc, int x, int y)
{
	Cp->Pieces_Draw(hdc, x, y);
}

Player::~Player()
{

}