#include "NameCard.h"
#include <iostream>


NameCard *MakeNameCard(char * name, char * phone)
{
	*name = { '\0' }; // 배열의 첫번째 공간만 초기화된다 전부 초기화 방법은?
	*phone = { '\0' };

	return 0; // 동적할당 및 초기화후 주소값 반환하는이유?????? name or phone 시작주소 반환?
}

void ShowNameCardInfo(NameCard *pcard)
{
	char tmp[NAME_LEN] = { "\0" };
	int trigger = FALSE;

	cout << "검색할 이름을 입력하세요 : ";
	cin >> tmp;

	for (int i = 0; i < PEOPLE_MAX; i++)
	{
		if (tmp == pcard[i].name)
		{
			cout << "=============정 보=============" << endl;
			cout << "이름 : " << pcard[i].name << endl;
			cout << "번호 : " << pcard[i].phone << endl;
			break;
		}
		else
		{
			trigger = TRUE;
		}
	}

	if (trigger == TRUE)
	{
		cout << "정보가 존재하지 않습니다.";
		trigger = FALSE;
	}
}