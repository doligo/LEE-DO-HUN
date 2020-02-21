#pragma once
#include<iostream>
#include<Windows.h>
#include<string>
#include<time.h>
#include<fstream> // ostream ^ istream >> file system
#include<conio.h> // getch()
using namespace std;

void Input(int arr[])
{
	for (int i = 0; i < 10; i++)
	{
		cout << i << "번째를 입력하세요 : ";
		cin >> arr[i];
	}
}

void Output(int sum, int big, int arr[])
{
	for (int i = 0; i < 10; i++)
	{
		sum += arr[i];

		if (big <= arr[i])
		{
			big = arr[i];
		}
	}

	cout << "가장 큰 수는 : " << big << "입니다" << endl;
	cout << "배열들의 합은 : " << sum << "입니다" << endl;
}

void Reverse(string name)
{
	char tmp[] = {'\0'};
	int num = 0;
	int j = 0;
	string result = { "\0" };

	cout << endl;
	cout << "거꾸로 출력 전 : " << name << endl;
	
	num = name.length();

	for (int i = num; i > 0; i--, j++)
	{
		tmp[j] = name[i - 1];
		result += tmp[j];
	}

	cout << "거꾸로 출력 후 : " << result;
}

int main()
{
	int arr[10] = { '\0' };
	int big = 0;
	int sum = 0;
	string st = { "You are not ready yet" };

	Input(arr);
	Output(sum, big, arr);
	Reverse(st);

	system("pause");
}
