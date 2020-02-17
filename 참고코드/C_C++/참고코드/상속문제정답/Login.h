#pragma once
#include<iostream>
#include<string>
#include<Windows.h>
using namespace std;
#define IDLEN 3
#define PASSWORDLEN 8
#define IDMAX 10

struct Id
{
	string m_strID;
	string m_strPassword;
	string m_strName;
	int m_iAge;
	string m_strPhonNumber;
	int m_iMileage;
};

class Login
{
private:
	int m_iIdCount;
	int m_iCurIdIndex;
	Id m_Id_List[IDMAX];
	void Setint(int* num, string tmp);
	void Setstring(string* str, string tmp);
	void Join();
protected:
	void SimpleShowID();
	void ShowID();
	void SetID();
public:
	bool LoginDisplay();
	Login();
	~Login();
};

