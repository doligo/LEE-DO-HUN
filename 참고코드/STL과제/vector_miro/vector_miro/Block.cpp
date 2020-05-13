#include "Block.h"


int Block::Init()
{
	b_array.assign(HEIGHT, vector<int>(WIDTH, 0));

	for (vector<int>::size_type i = 0; i < b_array[0].size(); i++)
		b_array[0][i] = 1;
	b_array[1] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,  0,  18,  1,  0,  76,  23,  1,  0,  40,  1 };
	b_array[2] = { 1, 62, 1, 0, 1, 0, 0, 0, 16, 1,  0,  0,  1,  0,  0,  0,  1,  0,  0,  1 };
	b_array[3] = { 1, 0, 1, 0, 1, 0, 1, 1, 1, 1,  0,  0,  1,  0,  0,  0,  1,  21,  73,  1 };
	b_array[4] = { 1, 15, 1, 0, 1, 0, 0, 0, 17, 1,  0,  0,  1,  0,  42,  0,  1,  1,  1,  1 };
	b_array[5] = { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,  0,  1,  1,  1,  1,  1,  1,  78,  77,  1 };
	b_array[6] = { 1, 38, 0, 0, 0, 0, 0, 0, 0, 1,  0,  37,  1,  0,  0,  0,  0,  0,  0,  1 };
	b_array[7] = { 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,  0,  1,  1,  0,  0,  1,  1,  1,  1,  1 };
	b_array[8] = { 1, 30, 0, 0, 0, 0, 0, 0, 0, 1,  0,  0,  1,  0,  0,  68,  67,  66,  0,  999 };
	b_array[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  72,  0,  1,  0,  0,  1,  1,  1,  1,  1 };
	b_array[10] = { 1, 33, 0, 1, 71, 1, 31, 1, 1, 1,  1,  1,  1,  0,  0,  0,  0,  0,  22,  1 };
	b_array[11] = { 1, 0, 0, 1, 60, 1, 0, 1, 0, 12,  1,  74,  1,  0,  1,  1,  0,  0,  0,  1 };
	b_array[12] = { 1, 0, 1, 1, 0, 0, 0, 0, 0, 0,  1,  0,  1,  43,  0,  1,  0,  1,  0,  1 };
	b_array[13] = { 1, 0, 14, 1, 1, 1, 1, 1, 0, 13,  1,  65,  1,  1,  1,  1,  64,  1,  1,  1 };
	b_array[14] = { 1, 70, 1, 1, 0, 61, 10, 1, 1, 1,  1,  0,  0,  0,  0,  0,  0,  0,  75,  1 };
	b_array[15] = { 1, 1, 1, 1, 0, 1, 1, 1, 0, 0,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1 };
	b_array[16] = { 1, 0, 0, 0, 0, 0, 11, 1, 0, 0,  0,  0,  0,  0,  0,  1,  0,  1,  20,  1 };
	b_array[17] = { 1, 0, 1, 0, 0, 0, 0, 1, 0, 0,  1,  1,  1,  1,  0,  1,  63,  1,  0,  1 };
	b_array[18] = { 1, 2, 1, 32, 34, 36, 39, 1, 41, 35,  1,  19,  0,  0,  0,  0,  0,  0,  0,  1 };
	for (vector<int>::size_type i = 0; i < b_array[19].size(); i++)
		b_array[19][i] = 1;

	return 0;
}

void Block::Block_Draw()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (b_array[y][x] == WALL)
				printf("▩");
			else if (b_array[y][x] == CHARACTER)
			{
				RED
					printf("♧");
				ORIGINAL
			}
			else if (b_array[y][x] >= ENTRY_START && b_array[y][x] < ENTRY_START + POTAL_MAX)
			{
				BLUE
					printf("◎");
				ORIGINAL
			}
			else if (b_array[y][x] >= EXIT_START && b_array[y][x] < EXIT_START + POTAL_MAX)
			{
				YELLOW
					printf("●");
				ORIGINAL
			}
			else if (b_array[y][x] >= DOOR && b_array[y][x] < DOOR + LOCKUNLOCK)
			{
				GOLD
					printf("■");
				ORIGINAL
			}
			else if (b_array[y][x] >= SWITCH && b_array[y][x] < SWITCH + LOCKUNLOCK)
			{
				GREEN
					printf("♣");
				ORIGINAL
			}
			else if (b_array[y][x] == NULL)
				printf("  ");
			else if (b_array[y][x] == EXIT)
			{
				PUPPLE
					printf("☞");
				ORIGINAL
			}
		}
		printf("\n");
	}
	BLUE printf("입구 : ◎");
	YELLOW printf(" 출구 : ●");
	GOLD printf(" 문 : ■");
	GREEN printf(" 스위치 : ♣");
	ORIGINAL
		return;
}