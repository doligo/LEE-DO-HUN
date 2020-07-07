#pragma once
#include<windows.h>
#include <string>
#include <iostream>
#include "resource.h"
using namespace std;

#define MAX_RT 11

class Animal_Card
{
private:
public:
	Animal_Card();

	void Show();
	void Draw(HDC hdc, HDC mhdc, HBITMAP my, HBITMAP old, HINSTANCE hin, int card_num);
	void Animal_Name(HWND hWnd, int num);

	~Animal_Card();
};

