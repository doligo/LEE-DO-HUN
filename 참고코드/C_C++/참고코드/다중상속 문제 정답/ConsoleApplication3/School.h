#pragma once
#include<iostream>
using namespace std;
class School
{
protected:
	int m_iClassNumber;
	int m_iGroupNumber;
	int m_iStudentNumber;
public:
	void SetClass();
	void ShowClass();
	School();
	~School();
};

