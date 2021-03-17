#pragma once
#include <Windows.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stack>
using namespace std;


#define BITMAP_MAX 35
#define BITMAP_SIZE_MAX 35

enum bit_map
{
	Black_BackGround, Button_ChangeChennel, Button_CreateRoom, Button_exit, Button_join, Button_JoinRoom, Button_VisitorInformation, Character_Banana,
	Character_BeanCake, Character_Dong, Character_Egg, Character_EggHalf, Character_Garlic, Character_Grape, Character_Kimchi, 
	Character_Kimchi2, Character_Lettuce, Character_MushRoom, Character_Onion, Character_Orange, Character_Pepper, Character_Radish, 
	Character_RiceRock, Character_Salad, Character_Tomato, Select_Character, Select_Character_temp, Waiting_room, Waiting_room2, 
	Waiting_room_Info, Waiting_room_ingame, Waiting_room_ingame2, Select_Character_Name1, Select_Character_Name2, Select_Character_Name3
};

class BitMap_And_Draw
{
private:
	HDC hdc;
	BITMAP B_Info;
	HDC Entire_DC; // 그리기를위한 전체배경이며, 검은화면으로도 쓴다
	HDC MemDC[BITMAP_MAX]; //// 리소스 저장할곳
	HBITMAP	m_BitMap[BITMAP_MAX];
	HBITMAP	m_Old_BitMap[BITMAP_MAX];
	SIZE m_size[BITMAP_SIZE_MAX];
	LPCSTR m_bitmap[BITMAP_MAX] = { "Black_BackGround.bmp", "Button_ChangeChennel.bmp", "Button_CreateRoom.bmp", "Button_exit.bmp", "Button_join.bmp", "Button_JoinRoom.bmp", "Button_VisitorInformation.bmp", "Character_Banana.bmp", 
	"Character_BeanCake.bmp", "Character_Dong.bmp", "Character_Egg.bmp", "Character_EggHalf.bmp","Character_Garlic.bmp","Character_Grape.bmp", "Character_Kimchi.bmp", "Character_Kimchi2.bmp", "Character_Lettuce.bmp", 
	"Character_MushRoom.bmp", "Character_Onion.bmp", "Character_Orange.bmp", "Character_Pepper.bmp", "Character_Radish.bmp", "Character_RiceRock.bmp", "Character_Salad.bmp", "Character_Tomato.bmp", "Select_Character.bmp", "Select_Character_temp.bmp", 
	"Waiting_room.bmp", "Waiting_room2.bmp", "Waiting_room_Info.bmp", "Waiting_room_ingame.bmp", "Waiting_room_ingame2.bmp", "Select_Character_Name1.bmp", "Select_Character_Name2.bmp", "Select_Character_Name3.bmp" };
	//// 로컬파일명이 중복일 경우 읽어오지못하는것 발생, 그냥 바로 파일이름만 적기
public:
	BitMap_And_Draw();

	void Init_Bitmap(HWND hWnd);
	void Draw(int _x, int _y, int _m_size, int dc_num);
	void Draw_Ready(int _x, int _y, int _m_size, int dc_num);
	void Draw_Detail_Ready(int _x, int _y, int _m_size, int dc_num, int x_size, int y_size);
	void Draw_Go();
	void Draw_Black_BackGround();
	void Draw_Detail_Ready2(int _x, int _y, int _m_size, int dc_num, int x_size, int y_size);

	~BitMap_And_Draw();
};

