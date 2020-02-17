#pragma once
#include<iostream>
#include<string>
using namespace std;
class Person
{
protected:
	int m_iAge;
	string m_strName;
	string m_strGender;
public:
	void SetPerson();
	void ShowPerson();
	Person();
	~Person();
};

