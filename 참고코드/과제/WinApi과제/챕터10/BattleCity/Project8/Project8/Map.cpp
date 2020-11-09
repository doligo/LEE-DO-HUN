#include "Map.h"

Map::Map()
{

}

void Map::Init_Map(int select_stage)
{
	HANDLE hFile = CreateFile(stage[select_stage], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	for (int i = 0; i < MAP_MAX; i++)
	{
		for (int j = 0; j < MAP_MAX; j++)
		{
			DWORD readB;

			ReadFile(hFile, &maps[i][j], sizeof(char), &readB, NULL);
			//// ** sizeof �κ��� ������ �����ؾ��� �ƴϸ� ��������� ���о�´�
		}
	}

	CloseHandle(hFile);
}

char Map::Get_Map_Info(int height, int width)
{
	return maps[height][width];
}

Map::~Map()
{

}