#include "Student.h"



Student::Student()
{
}

void Student::Input()
{
	cout << "�г� �Է� : ";
	cin >> m_igrade;
	cout << "�� �Է� : ";
	cin >> m_iclass;
	cout << "�л� ��ȣ �Է� : ";
	cin >> m_inum;

	cout << "���� �Է� : ";
	cin >> m_iage;
	cout << "�̸� �Է� : ";
	cin >> m_iname;
	cout << "���� �Է� : ";
	cin >> m_isex;
}

void Student::Show()
{
	system("cls");
	cout << m_igrade << "�г� " << m_iclass << "�� " << m_inum << "�� �л�" << endl;
	cout << "���� : " << m_iage << "��" << endl;
	cout << "�̸� : " << m_iname << endl;
	cout << "���� : " << m_isex << endl;
}

Student::~Student()
{
}
