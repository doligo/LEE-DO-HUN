#include "NameCard.h"
#include <iostream>
#pragma warning(disable:4996)

#define MAX 30

int Register()
{
	int n;

	system("cls");
	cout << "����� ����� ���� �Է� : ";
	cin >> n;

	return n;
}

void Insert(NameCard *n, int n2)
{
	char name[NAME_LEN] = { "\0" };
	char phone[PHONE_LEN] = { "\0" };

	for (int i = 0; i < n2; i++)
	{
		system("cls");
		cout << i + 1 << "�� ��� �̸��Է� : ";
		cin >> name;
		cout << i + 1 << "�� ��� �ڵ����Է� : ";
		cin >> phone;
		n[i] = *MakeNameCard(name, phone);
	}
}

void No_Data(int num)
{
	if (num == 0)
	{
		cout << "���������ʽ��ϴ�" << endl;
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


	NameCard *nc;
	nc = NULL;

	while (1)
	{
		system("cls");
		cout << "1.����ϱ�" << endl;
		cout << "2.����ã��" << endl;
		cout << "3.��ȣ����" << endl;
		cout << "4.��������" << endl;
		cout << "�Է� : ";
		cin >> select;

		switch (select)
		{
		case 1:
			num = Register();
			nc = new NameCard[num];
			people_max = num;
			Insert(nc, num);
			break;
		case 2:
			system("cls");
			cout << "�̸��� �Է��ϼ��� : ";
			cin >> name;
			for (int i = 0; i < num; i++)
			{
				num2 = NameCompare(&nc[i], name);
				if (num2 == 1)
				{
					ShowNameCardInfo(&nc[i]);
					break;
				}
			}
			No_Data(num2);
			break;
		case 3:
			system("cls");
			cout << "�̸��� �Է��ϼ��� : ";
			cin >> name;
			for (int i = 0; i < num; i++)
			{
				num2 = NameCompare(&nc[i], name);
				if (num2 == 1)
				{
					cout << "�����ϰ���� ��ȣ �Է� : ";
					cin >> tmp_phone;
					ChangePhoneNum(&nc[i], tmp_phone);
					break;
				}
			}
			No_Data(num2);
			break;
		case 4:
			system("cls");
			cout << "������ ����� �̸��� �Է��ϼ��� : ";
			cin >> name;
			for (int i = 0; i < num; i++)
			{
				num2 = NameCompare(&nc[i], name);
				if (num2 == 1)
				{
					Delete(&nc[i]); // ������ ������ ����
					nc[i] = {};
					break;
				}
			}
			No_Data(num2);
			break;
		}
	}
	system("pause");
}