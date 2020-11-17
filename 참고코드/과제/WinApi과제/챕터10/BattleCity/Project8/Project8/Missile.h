#include <Windows.h>
#include <iostream>
#include <string.h>
#pragma once

class Missile
{
private:
	int m_ix;
	int m_iy;
	int m_direct;
public:
	Missile();

	void Init_Missile();

	~Missile();
};

