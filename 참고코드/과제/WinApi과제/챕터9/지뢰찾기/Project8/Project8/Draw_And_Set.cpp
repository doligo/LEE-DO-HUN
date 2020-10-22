#include "Draw_And_Set.h"

Draw_And_Set::Draw_And_Set()
{
	playing = FALSE;
	difficulty = BEGINNER;
	m_p_width = 0;
	m_p_height = 0;
	m_p_mine = 0;
}

void Draw_And_Set::Init_BitMap(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	char buffer[256] = {};
	int num = 0;

	MemDC[0] = CreateCompatibleDC(hdc); // 검은배경
	m_BitMap[0] = CreateCompatibleBitmap(hdc, 1200, 700);
	m_Old_BitMap[0] = (HBITMAP)SelectObject(MemDC[0], m_BitMap[0]);

	/////////////////////////////
	MemDC[1] = CreateCompatibleDC(MemDC[0]);
	m_BitMap[1] = (HBITMAP)LoadImage(NULL, TEXT("back.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_BitMap[1] = (HBITMAP)SelectObject(MemDC[1], m_BitMap[1]);

	GetObject(m_BitMap[1], sizeof(B_Info), &B_Info);
	m_size[0].cx = B_Info.bmWidth;
	m_size[0].cy = B_Info.bmHeight;
	//////////////////////////////
	MemDC[2] = CreateCompatibleDC(MemDC[0]);
	m_BitMap[2] = (HBITMAP)LoadImage(NULL, TEXT("block.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_BitMap[2] = (HBITMAP)SelectObject(MemDC[2], m_BitMap[2]);

	GetObject(m_BitMap[2], sizeof(B_Info), &B_Info);
	m_size[1].cx = B_Info.bmWidth;
	m_size[1].cy = B_Info.bmHeight;
	//////////////////////////////
	for (int i = 3; i < 12; i++)
	{
		sprintf_s(buffer, "block_%d.bmp", num);

		MemDC[i] = CreateCompatibleDC(MemDC[0]);
		m_BitMap[i] = (HBITMAP)LoadImage(NULL, buffer,
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		m_Old_BitMap[i] = (HBITMAP)SelectObject(MemDC[i], m_BitMap[i]);

		GetObject(m_BitMap[i], sizeof(B_Info), &B_Info);
		m_size[i - 1].cx = B_Info.bmWidth;
		m_size[i - 1].cy = B_Info.bmHeight;

		num++;
	}
	//////////////////////////////
	MemDC[12] = CreateCompatibleDC(MemDC[0]);
	m_BitMap[12] = (HBITMAP)LoadImage(NULL, TEXT("flag.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_BitMap[12] = (HBITMAP)SelectObject(MemDC[12], m_BitMap[12]);

	GetObject(m_BitMap[12], sizeof(B_Info), &B_Info);
	m_size[11].cx = B_Info.bmWidth;
	m_size[11].cy = B_Info.bmHeight;
	//////////////////////////////
	MemDC[13] = CreateCompatibleDC(MemDC[0]);
	m_BitMap[13] = (HBITMAP)LoadImage(NULL, TEXT("mine.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_BitMap[13] = (HBITMAP)SelectObject(MemDC[13], m_BitMap[13]);

	GetObject(m_BitMap[13], sizeof(B_Info), &B_Info);
	m_size[12].cx = B_Info.bmWidth;
	m_size[12].cy = B_Info.bmHeight;

}

void Draw_And_Set::Init_Game()
{
	int num = 0;
	int value = 0;

	while (num != BLOCK_MAX)
	{
		map_block[num].block_pos = { 0, 0, 0, 0 };
		map_block[num].click = FALSE;
		map_block[num].mine = FALSE;
		map_block[num].flag = FALSE;
		num++;
	}

	if (difficulty == BEGINNER)
	{
		int _x = 15;
		int _y = 32;

		m_p_width = 9;
		m_p_height = 9;
		m_p_mine = 10;

		for (int i = 0; i < m_p_height; i++)
		{
			for (int j = 0; j < m_p_width; j++)
			{
				map_block[value].block_pos = { _x, _y, _x + 26, _y + 26 };
				_x += 35;
				value++;
			}
			_x = 15;
			_y += 35;
		}
	}
	else if (difficulty == INTERMEDIATE)
	{
		int _x = 30;
		int _y = 58;

		m_p_width = 16;
		m_p_height = 16;
		m_p_mine = 40;

		for (int i = 0; i < m_p_height; i++)
		{
			for (int j = 0; j < m_p_width; j++)
			{
				map_block[value].block_pos = { _x, _y, _x + 26, _y + 26 };
				_x += 35;
				value++;
			}
			_x = 30;
			_y += 35;
		}

	}
	else if (difficulty == ADVANCE)
	{
		int _x = 55;
		int _y = 58;

		m_p_width = 30;
		m_p_height = 16;
		m_p_mine = 99;

		for (int i = 0; i < m_p_height; i++)
		{
			for (int j = 0; j < m_p_width; j++)
			{
				map_block[value].block_pos = { _x, _y, _x + 26, _y + 26 };
				_x += 35;
				value++;
			}
			_x = 55;
			_y += 35;
		}
	}
}

void Draw_And_Set::Draw_Game_Screen(HDC hdc)
{
	int num = 0;

	if (playing == FALSE)
	BitBlt(hdc, 0, 0, 1160, 680, MemDC[0], 0, 0, RGB(255, 255, 255)); // 화면 덮어씌워지는것 방지

	playing = TRUE;

	if (difficulty == BEGINNER)
	{
		int _x = 15;
		int _y = 32;

		TransparentBlt(MemDC[0], 0, 0, m_size[0].cx - 520, m_size[0].cy - 130, MemDC[1], 0, 0, m_size[0].cx, m_size[0].cy, SRCCOPY);

		for (int i = 0; i < m_p_height; i++)
		{
			for (int j = 0; j < m_p_width; j++)
			{
				if (map_block[num].click == FALSE && map_block[num].flag == FALSE)
					TransparentBlt(MemDC[0], _x, _y, m_size[1].cx + 10, m_size[1].cy + 10, MemDC[2], 0, 0, m_size[1].cx, m_size[1].cy, SRCCOPY);
				else if (map_block[num].click == TRUE)
					TransparentBlt(MemDC[0], _x, _y, m_size[2].cx + 10, m_size[2].cy + 10, MemDC[3], 0, 0, m_size[2].cx, m_size[2].cy, SRCCOPY);
				else if (map_block[num].click == FALSE && map_block[num].flag == TRUE)
					TransparentBlt(MemDC[0], _x, _y, m_size[11].cx + 10, m_size[11].cy + 10, MemDC[12], 0, 0, m_size[11].cx, m_size[11].cy, SRCCOPY);
				_x += 35;
				num++;
			}
			_x = 15;
			_y += 35;
		}
		BitBlt(hdc, 0, 0, 350, 380, MemDC[0], 0, 0, SRCCOPY);
	}
	else if (difficulty == INTERMEDIATE)
	{
		int _x = 30;
		int _y = 58;

		TransparentBlt(MemDC[0], 0, 0, m_size[0].cx - 246, m_size[0].cy + 170, MemDC[1], 0, 0, m_size[0].cx, m_size[0].cy, SRCCOPY);

		for (int i = 0; i < m_p_height; i++)
		{
			for (int j = 0; j < m_p_width; j++)
			{
				if (map_block[num].click == FALSE && map_block[num].flag == FALSE)
					TransparentBlt(MemDC[0], _x, _y, m_size[1].cx + 10, m_size[1].cy + 10, MemDC[2], 0, 0, m_size[1].cx, m_size[1].cy, SRCCOPY);
				else if (map_block[num].click == TRUE)
					TransparentBlt(MemDC[0], _x, _y, m_size[2].cx + 10, m_size[2].cy + 10, MemDC[3], 0, 0, m_size[2].cx, m_size[2].cy, SRCCOPY);
				else if (map_block[num].click == FALSE && map_block[num].flag == TRUE)
					TransparentBlt(MemDC[0], _x, _y, m_size[11].cx + 10, m_size[11].cy + 10, MemDC[12], 0, 0, m_size[11].cx, m_size[11].cy, SRCCOPY);
				_x += 35;
				num++;
			}
			_x = 30;
			_y += 35;
		}

		BitBlt(hdc, 0, 0, 620, 680, MemDC[0], 0, 0, SRCCOPY);
	}
	else if (difficulty == ADVANCE)
	{
		int _x = 55;
		int _y = 58;

		TransparentBlt(MemDC[0], 0, 0, m_size[0].cx + 295, m_size[0].cy + 170, MemDC[1], 0, 0, m_size[0].cx, m_size[0].cy, SRCCOPY);

		for (int i = 0; i < m_p_height; i++)
		{
			for (int j = 0; j < m_p_width; j++)
			{
				if (map_block[num].click == FALSE && map_block[num].flag == FALSE)
					TransparentBlt(MemDC[0], _x, _y, m_size[1].cx + 10, m_size[1].cy + 10, MemDC[2], 0, 0, m_size[1].cx, m_size[1].cy, SRCCOPY);
				else if (map_block[num].click == TRUE)
					TransparentBlt(MemDC[0], _x, _y, m_size[2].cx + 10, m_size[2].cy + 10, MemDC[3], 0, 0, m_size[2].cx, m_size[2].cy, SRCCOPY);
				else if (map_block[num].click == FALSE && map_block[num].flag == TRUE)
					TransparentBlt(MemDC[0], _x, _y, m_size[11].cx + 10, m_size[11].cy + 10, MemDC[12], 0, 0, m_size[11].cx, m_size[11].cy, SRCCOPY);
				_x += 35;
				num++;
			}
			_x = 55;
			_y += 35;
		}

		BitBlt(hdc, 0, 0, 1160, 680, MemDC[0], 0, 0, SRCCOPY);
	}
}

void Draw_And_Set::Left_Click(int x, int y)
{
	///////////// 중단점, 카운트, 마인심기 **
	int num = 0;

	while (map_block[num].block_pos.left != 0)
	{
		if (map_block[num].block_pos.left <= x && map_block[num].block_pos.right >= x &&
			map_block[num].block_pos.top <= y && map_block[num].block_pos.bottom >= y && map_block[num].click == FALSE && map_block[num].flag == FALSE)
		{
			map_block[num].click = TRUE;
			break;
		}
		else
			num++;
	}

	Left_Click(x + 35, y);
	Left_Click(x - 35, y);
	Left_Click(x, y + 35);
	Left_Click(x, y - 35);

	Left_Click(x + 35, y + 35);
	Left_Click(x + 35, y - 35);
	Left_Click(x - 35, y - 35);
	Left_Click(x - 35, y + 35);
}

void Draw_And_Set::Right_Click(int x, int y)
{
	int num = 0;

	while (map_block[num].block_pos.left != 0)
	{
		if (map_block[num].block_pos.left <= x && map_block[num].block_pos.right >= x &&
			map_block[num].block_pos.top <= y && map_block[num].block_pos.bottom >= y && map_block[num].click == FALSE)
		{
			if (map_block[num].flag == FALSE)
			{
				m_p_mine--;
				map_block[num].flag = TRUE;
			}
			else if (map_block[num].flag == TRUE)
			{
				m_p_mine++;
				map_block[num].flag = FALSE;
			}
			break;
		}
		else
			num++;
	}
}

Draw_And_Set::~Draw_And_Set()
{
	for (int i = 0; i < BITMAP_MAX; i++)
	{
		DeleteObject(m_BitMap[i]);
		DeleteObject(m_Old_BitMap[i]);
		DeleteDC(MemDC[i]);
	}
}