#include <Windows.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <vector>
using namespace std;
#pragma once

#define WIDTH 33
#define HEIGHT 25
#define MAP_MAX 28

class Map
{
private:
	LPCSTR stage[2] = { "stage1.txt", "stage2.txt" }; // stage2는 임시용
	char maps[MAP_MAX][MAP_MAX];
public:
	Map();

	void Init_Map(int select_stage);
	char Get_Map_Info(int height, int width);
	void Set_Map_Info(int height, int width, char value);

	~Map();
};

