#include <iostream>
#include <time.h>
#include <Windows.h>
#include <string>
#include<conio.h> // getch()
using namespace std;

template<typename Type>
void Add(Type num)
{
	cout << "���� �� : " << num << endl;
	num++;
	cout << "���� �� : " << num << endl;
}

template<typename Type>
Type Big(Type num, Type num2)
{
	if (num > num2)
		return num2;
	else
		return num;
}

template<typename Test>
Test Max(Test num, Test num2, Test num3)
{
	if (num > num2)
	{
		if (num > num3)
			return num;
		else
			return num3;
	}

	else if (num2 > num)
	{
		if (num2 > num3)
			return num2;
		else
			return num3;
	}
}

void main()
{
	int num, num2, num3;

	cout << "���ڸ� �Է��ϼ��� : ";
	cin >> num;
	Add(num);

	cout << "�� ���ڸ� �Է��ϼ��� : ";
	cin >> num >> num2;
	cout << "���߿� �������� : " << Big(num, num2) << endl;

	cout << "���� ������ �Է��ϼ���";
	cin >> num >> num2 >> num3;
	cout << "���߿� ���� ū ���� : " << Max(num, num2, num3) << endl;


	system("pause");
}