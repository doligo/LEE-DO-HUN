#include "School.h"



School::School()
{
}

void School::SetClass()
{
	cout << "학년 입력 : ";
	cin >> m_iClassNumber;
	cout << "반 입력 : ";
	cin >> m_iGroupNumber;
	cout << "학생 번호 입력 : ";
	cin >> m_iStudentNumber;
}
void School::ShowClass()
{
	cout << m_iClassNumber << " 학년 " << m_iGroupNumber<< " 반 " << m_iStudentNumber << " 번 학생" << endl;
}

School::~School()
{
}
