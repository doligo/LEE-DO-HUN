#include "NameCard.h"
#include <iostream>
#pragma warning(disable:4996)

NameCard *MakeNameCard(char * name, char * phone)
{
	for (int i = 0; i < NAME_LEN; i++)
	{
		name[i] = { '\0' };
		phone[i] = { '\0' };
	}

	return 0; // �����Ҵ� �� �ʱ�ȭ�� �ּҰ� ��ȯ�ϴ�����?????? name or phone �����ּ� ��ȯ?
}

void ShowNameCardInfo(NameCard *pcard)
{
	char tmp[NAME_LEN] = { "\0" };
	int trigger = FALSE;

	cout << "�˻��� �̸��� �Է��ϼ��� : ";
	cin >> tmp;

	for (int i = 0; i < PEOPLE_MAX; i++)
	{
		if (pcard[i].name == tmp)
		{
			cout << "=============�� ��=============" << endl;
			cout << "�̸� : " << pcard[i].name << endl;
			cout << "��ȣ : " << pcard[i].phone << endl;
			break;
		}
		else
		{
			trigger = TRUE;
		}
	}

	if (trigger == TRUE)
	{
		cout << "������ �������� �ʽ��ϴ�.";
		trigger = FALSE;
	}
}