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
	int status; // �ܾ �׾����� ��Ҵ��� �����ϱ����� �ʿ�
	int item_word; // �����۴ɷ�ġ�� �ִ� ���庯��
	int on_screen; // ȭ�鿡 �������
};

class Ward
{
private:
public:
	Ward();


	~Ward();
};

