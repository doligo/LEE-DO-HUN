#pragma once
#include"Login.h"

class Computer : public Login
{
private:
	string m_strName;
	string m_strGraphic;
	string m_strCpu;
	int m_iRam;
	bool m_bOnOff;
	void condition();
	void function();
public:	
	void Computerdisplay();
	Computer();
	~Computer();
};

