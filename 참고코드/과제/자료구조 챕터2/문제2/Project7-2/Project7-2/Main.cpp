#include "NameCard.h"
#include <iostream>
#pragma warning(disable:4996)

#define MAX 30

int Register()
{
	int n;

	system("cls");
	cout << "등록할 사람의 숫자 입력 : ";
	cin >> n;

	return n;
}

void Insert(NameCard **n, int n2)
{
	char name[NAME_LEN] = { "\0" };
	char phone[PHONE_LEN] = { "\0" };

	for (int i = 0; i < n2; i++)
	{
		system("cls");
		cout << i + 1 << "번 사람 이름입력 : ";
		cin >> name;
		cout << i + 1 << "번 사람 핸드폰입력 : ";
		cin >> phone;
		n[i] = MakeNameCard(name, phone);
	}
}

void No_Data(int num)
{
	if (num == 0)
	{
		cout << "존재하지않습니다" << endl;
		system("pause");
	}
	num = 0;
}

void main()
{
	int select = 0;
	int num = 0;
	int num2 = 0;
	int people_max = 0;

	char name[MAX] = { "\0" };
	char tmp_phone[MAX] = { "\0" };


	NameCard **nc;
	nc = NULL;

	while (1)
	{
		system("cls");
		cout << "1.등록하기" << endl;
		cout << "2.정보찾기" << endl;
		cout << "3.번호변경" << endl;
		cout << "4.정보삭제" << endl;
		cout << "5.모든정보" << endl;
		cout << "입력 : ";
		cin >> select;

		switch (select)
		{
		case 1:
			num = Register();
			nc = new NameCard*[num];
			people_max = num;
			Insert(nc, num);
			break;
		case 2:
			system("cls");
			cout << "이름을 입력하세요 : ";
			cin >> name;
			for (int i = 0; i < num; i++)
			{
				if (nc[i] != NULL)
				num2 = NameCompare(nc[i], name);
				if (num2 == 1 && nc[i] != NULL)
				{
					ShowNameCardInfo(nc[i]);
					system("pause");
					break;
				}
			}
			No_Data(num2);
			break;
		case 3:
			system("cls");
			cout << "이름을 입력하세요 : ";
			cin >> name;
			for (int i = 0; i < num; i++)
			{
				if (nc[i] != NULL)
				num2 = NameCompare(nc[i], name);
				if (num2 == 1 && nc[i] != NULL)
				{
					cout << "변경하고싶은 번호 입력 : ";
					cin >> tmp_phone;
					ChangePhoneNum(nc[i], tmp_phone);
					break;
				}
			}
			No_Data(num2);
			break;
		case 4:
			system("cls");
			cout << "삭제할 사람의 이름을 입력하세요 : ";
			cin >> name;
			for (int i = 0; i < num; i++)
			{
				if (nc[i] != NULL)
				num2 = NameCompare(nc[i], name);
				if (num2 == 1 && nc[i] != NULL)
				{
					Delete(nc[i]); // 더블포인트로 이렇게 쓰던가 or 그냥 main에서 delete함수를 쓰던가
					nc[i] = {};
					break;
				}
			}
			No_Data(num2);
			break;
		case 5:
			system("cls");
			for (int i = 0; i < people_max; i++) 
			{
				if (nc[i] == NULL)
				{
					cout << "=====정 보=====" << endl;
					cout << "데이터없음" << "   " << "데이터없음" << endl;
				}
				else
				{
					ShowNameCardInfo(nc[i]);
				}
			}
			system("pause");
			break;
		}
	}
	system("pause");
}