#include "Mecro.h"
#pragma once

#define WORD_SPEED_UP 5
#define WORD_SPEED_DOWN 6
#define WORD_PAUSE 7
#define WORD_BLIND 8
#define SCREEN_CLEAR 9

struct _Ward
{
	string name;
	int x;
	int y;
	int status; // 단어가 죽었는지 살았는지 구별하기위해 필요
	int item_word; // 아이템능력치가 있는 워드변수
	int on_screen; // 화면에 출력유무
};

class Ward
{
private:
public:
	Ward();


	~Ward();
};

