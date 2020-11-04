#include <Windows.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <vector>
using namespace std;
#pragma once

#define BITMAP_MAX 47
#define BITMAP_SIZE_MAX 47

class BitMap_And_Draw
{
private:
	BITMAP B_Info;
	HDC Entire_DC; // 그리기를위한 전체배경이며, 검은화면으로도 쓴다
	HDC MemDC[BITMAP_MAX]; //// 리소스 저장할곳
	HBITMAP	m_BitMap[BITMAP_MAX];
	HBITMAP	m_Old_BitMap[BITMAP_MAX];
	SIZE m_size[BITMAP_SIZE_MAX];
	LPCSTR m_bitmap[BITMAP_MAX] = { "Project8\\blank.bmp", "Project8\\block00.bmp", "Project8\\block01.bmp", "Project8\\block02.bmp", "Project8\\block03.bmp", "Project8\\block04.bmp", "Project8\\block05.bmp", 
	"Project8\\block06.bmp", "Project8\\block07.bmp", "Project8\\block08.bmp", "Project8\\block09.bmp","Project8\\block10.bmp","Project8\\block11.bmp", "Project8\\block12.bmp", "Project8\\block13.bmp", "Project8\\block14.bmp", 
	"Project8\\e_down_00.bmp", "Project8\\e_down_01.bmp", "Project8\\e_down_02.bmp", "Project8\\e_left_00.bmp", "Project8\\e_left_01.bmp", "Project8\\e_left_02.bmp", "Project8\\e_right_00.bmp", "Project8\\e_right_01.bmp", "Project8\\e_right_02.bmp", "Project8\\e_up_00.bmp", 
	"Project8\\e_up_01.bmp", "Project8\\e_up_02.bmp", "Project8\\enemy_icon.bmp", "Project8\\explosion_00.bmp", "Project8\\explosion_01.bmp", "Project8\\explosion_02.bmp", "Project8\\explosion_03.bmp", "Project8\\explosion_04.bmp", "Project8\\missile_00.bmp", 
	"Project8\\player_icon.bmp", "Project8\\shield_00.bmp", "Project8\\shield_01.bmp", "Project8\\stage_icon.bmp", "Project8\\tank_down_00.bmp", "Project8\\tank_down_01.bmp", "Project8\\tank_left_00.bmp", "Project8\\tank_left_01.bmp", "Project8\\tank_right_00.bmp", "Project8\\tank_right_01.bmp", 
	"Project8\\tank_up_00.bmp", "Project8\\tank_up_01.bmp" };
public:
	BitMap_And_Draw();

	void Init_Bitmap(HWND hWnd);

	~BitMap_And_Draw();
};

