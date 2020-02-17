#include "Person.h"



Person::Person()
{
}

void Person::SetPerson()
{
	cout << "나이 입력 : ";
	cin >> m_iAge;
	cout << "이름 입력 : ";
	cin >> m_strName;
	cout << "성별 입력 : ";
	cin >> m_strGender;
}
void Person::ShowPerson()
{
	cout << "나이 : " << m_iAge<< endl;
	cout << "이름 : " << m_strName << endl;
	cout << "성별 : " << m_strGender << endl;
}

Person::~Person()
{
}
