#include "DBLinkedList.h"

int main()
{
	// 양방향 연결 리스트의 생성 및 초기화  ///////
	List list;
	DBLinkedList DL;
	int data;
	DL.ListInit(&list);

	// 4개의 데이터 저장  ///////
	DL.LInsert(&list, 20);
	DL.LInsert(&list, 30);
	DL.LInsert(&list, 40);
	DL.LInsert(&list, 50);

	// 저장된 데이터의 조회  ///////
	if (DL.LFirst(&list, &data))
	{
		printf("%d ", data);

		while (DL.LNext(&list, &data))
			printf("%d ", data);

		while (DL.LPrevious(&list, &data))
			printf("%d ", data);

		printf("\n\n");
	}

	return 0;
}

