#include <iostream>
#include "CLinkedList.h"

int main()
{
	// 원형 연결 리스트의 생성 및 초기화 ///////
	Clist list;
	CLinkedList Lt;
	int data, i, nodeNum;
	Lt.ListInit(&list);

	// 리스트에 5개의 데이터를 저장 /////// 
	Lt.LInsert(&list, 1);
	Lt.LInsert(&list, 2);
	Lt.LInsert(&list, 3);
	Lt.LInsert(&list, 4);
	Lt.LInsert(&list, 5);

	// 리스트에 저장된 데이터를 연속 3회 출력 ///////
	if (Lt.LFirst(&list, &data))
	{
		printf("%d ", data);

		for (i = 0; i < Lt.LCount(&list) * 3 - 1; i++)
		{
			if (Lt.LNext(&list, &data))
				printf("%d ", data);
		}
	}
	printf("\n");

	// 2의 배수를 찾아서 모두 삭제 ///////
	nodeNum = Lt.LCount(&list);

	if (nodeNum != 0)
	{
		Lt.LFirst(&list, &data);
		if (data % 2 == 0)
			Lt.LRemove(&list);

		for (i = 0; i < nodeNum - 1; i++)
		{
			Lt.LNext(&list, &data);
			if (data % 2 == 0)
				Lt.LRemove(&list);
		}
	}

	// 전체 데이터 1회 출력 ///////
	if (Lt.LFirst(&list, &data))
	{
		printf("%d ", data);

		for (i = 0; i < Lt.LCount(&list) - 1; i++)
		{
			if (Lt.LNext(&list, &data))
				printf("%d ", data);
		}
	}
	system("pause");
	return 0;
}