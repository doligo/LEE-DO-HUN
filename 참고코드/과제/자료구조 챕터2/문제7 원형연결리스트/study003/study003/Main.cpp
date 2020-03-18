#include <stdio.h>
#include "CLinkedList.h"

void Set_People(Employee *p)
{
	p[0].name = "이도헌";
	p[0].num = 11;

	p[1].name = "민혜정";
	p[1].num = 22;

	p[2].name = "이윤";
	p[2].num = 33;

	p[3].name = "김지혜";
	p[3].num = 44;
}

void Show_Person(Employee *p, int num)
{
	for (int i = 0; i < PEOPLE_MAX; i++)
	{
		if (p[i].num == num)
		{
			cout << p[i].name << "의 당직후 ";
			break;
		}
	}
}

int main(void)
{
	// 원형 연결 리스트의 생성 및 초기화 ///////

	Clist list;
	CLinkedList CL;
	Employee *people;
	int pos_value;

	int data, i, p_num, num, value;

	CL.ListInit(&list);
	people = new Employee[PEOPLE_MAX];

	Set_People(people);

	// 리스트에 5개의 데이터를 저장 ///////
	pos_value = POSITION_NEXT;
	CL.LInsert(&list, people[0].num, pos_value);
	CL.LInsert(&list, people[1].num, pos_value);
	CL.LInsert(&list, people[2].num, pos_value);
	CL.LInsert(&list, people[3].num, pos_value);


	// 리스트에 저장된 데이터를 연속 3회 출력 /////// 당직순서출력
	if (CL.LFirst(&list, &data) == TRUE)
	{
		cout << "당직의 순서 : ";
		for (int i = 0; i < PEOPLE_MAX; i++)
		{
			if (people[i].num == data)
			{
				cout << people[i].name;
			}
		}

		for (i = 0; i < CL.LCount(&list) * 3 - 1; i++)
		{
			if (CL.LNext(&list, &data) == TRUE)
			for (int i = 0; i < PEOPLE_MAX; i++)
			{
				if (people[i].num == data)
				{
					cout << " -> ";
					cout << people[i].name;
				}
			}
		}
	}
	printf("\n");

	cout << "사원번호 입력(사원번호는 11,22,33,44가 있다) : ";
	cin >> p_num;
	cout << "원하는 정수입력 : ";
	cin >> num;

	Show_Person(people, p_num);

	value = CL.Find_Person(&list, p_num, num);

	for (int i = 0; i < PEOPLE_MAX; i++)
	{
		if (value == people[i].num)
		{
			cout << num << "일 뒤의 당직은 " << people[i].name << "입니다" << endl;
			break;
		}
	}

	system("pause");

	if (people != NULL)
	{
		delete[] people;
		people = NULL;
	}

	return 0;
}