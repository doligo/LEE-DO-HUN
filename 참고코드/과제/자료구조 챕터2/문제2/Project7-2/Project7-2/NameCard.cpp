#include "NameCard.h"
#include <iostream>


NameCard *MakeNameCard(char * name, char * phone)
{
	*name = { '\0' }; // �迭�� ù��° ������ �ʱ�ȭ�ȴ� ���� �ʱ�ȭ �����?
	*phone = { '\0' };

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
		if (tmp == pcard[i].name)
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