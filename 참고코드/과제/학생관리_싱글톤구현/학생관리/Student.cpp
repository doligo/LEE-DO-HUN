#include "Student.h"

template <typename T>
T Student<T>::SetStudent(T _num)
{
	cout << "�̸��� �Է� �Ͻÿ� : ";
	cin >> name;
	cout << "3������ ������ �Է��Ͻÿ�" << endl;
	cout << "���� : ";
	cin >> kor;
	cout << "���� : ";
	cin >> eng;
	cout << "���� : ";
	cin >> math;
	sum = kor + eng + math;
	avg = (float)sum / 3;
	num = _num;
	if (avg >= 90)
		Class = 'A';
	else if (avg >= 80)
		Class = 'B';
	else if (avg >= 70)
		Class = 'C';
	else if (avg >= 60)
		Class = 'D';
	else
		Class = 'F';
	return;
}

template <typename T>
T Student<T>::showStudent()
{
	cout << "----------------------" << endl;
	cout << num << "�� �л�" << endl;
	cout << "�̸� : " << name << endl;
	cout << "���� ���� : " << kor << endl << "���� ���� : " << math << endl << "���� ���� : " << eng << endl;
	cout << "�հ� ���� : " << sum << "\t ������� : " << avg << endl;
	cout << "��� : [ " << Class << "]" << endl << endl;
	return;
}
