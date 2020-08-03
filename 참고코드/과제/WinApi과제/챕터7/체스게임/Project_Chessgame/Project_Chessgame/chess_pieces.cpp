#include "chess_pieces.h"

chess_pieces::chess_pieces()
{

}

void chess_pieces::Init_pieces(HDC hdc, int player_num)
{

	if (player_num == 0) // 백
	{
		m_King.x = 4;
		m_King.y = 7;

		m_Queen.x = 3;
		m_Queen.y = 7;

		m_Rook[0].x = 0;
		m_Rook[0].y = 7;
		m_Rook[1].x = 7;
		m_Rook[1].y = 7;

		m_Bishop[0].x = 2;
		m_Bishop[0].y = 7;
		m_Bishop[1].x = 5;
		m_Bishop[1].y = 7;

		m_Knight[0].x = 1;
		m_Knight[0].y = 7;
		m_Knight[1].x = 6;
		m_Knight[1].y = 7;

		for (int i = 0; i < 8; i++)
		{
			m_Pawn[i].x = i;
			m_Pawn[i].y = 6;
		}
	}

	else // 흑
	{
		m_King.x = 4;
		m_King.y = 0;

		m_Queen.x = 3;
		m_Queen.y = 0;

		m_Rook[0].x = 0;
		m_Rook[0].y = 0;
		m_Rook[1].x = 7;
		m_Rook[1].y = 0;

		m_Bishop[0].x = 2;
		m_Bishop[0].y = 0;
		m_Bishop[1].x = 5;
		m_Bishop[1].y = 0;

		m_Knight[0].x = 1;
		m_Knight[0].y = 0;
		m_Knight[1].x = 6;
		m_Knight[1].y = 0;

		for (int i = 0; i < 8; i++)
		{
			m_Pawn[i].x = i;
			m_Pawn[i].y = 1;
		}
	}

	////////////

	MemDC = CreateCompatibleDC(hdc);

	if (player_num == 0)
		hbtmap = (HBITMAP)LoadImage(NULL, "C:\\Users\\A-12\\Desktop\\LEE-DO-HUN\\참고코드\\과제\\WinApi과제\\챕터7\\체스게임\\block_w_05.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);


	old_hbtmap = (HBITMAP)SelectObject(MemDC, hbtmap);
	GetObject(hbtmap, sizeof(BITMAP), &btmap);
	m_x = btmap.bmWidth;
	m_y = btmap.bmHeight;

}

void chess_pieces::Pieces_Draw(HDC hdc, int x, int y)
{
	TransparentBlt(hdc, x, y, m_x - 50, m_y - 50, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));
}

chess_pieces::~chess_pieces()
{
	SelectObject(MemDC, old_hbtmap);
	DeleteObject(hbtmap);
	DeleteDC(MemDC);
}