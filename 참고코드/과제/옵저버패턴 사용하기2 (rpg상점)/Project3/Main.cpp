#pragma once
#include "GameSystem.h"

void main()
{
	srand(time(NULL)); //// 딱 한번만
	GameSystem Excute;
	Excute.Game_Screen();
	//// 무기가 리스폰되려면 상점에서 6초간 기다려야한다
}