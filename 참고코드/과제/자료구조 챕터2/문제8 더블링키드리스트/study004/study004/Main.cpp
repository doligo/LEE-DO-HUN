#include "DBLinkedList.h"

int main()
{
	// 양방향 연결 리스트의 생성 및 초기화  ///////
	List list;
	DBLinkedList DL;
	int data;
	Node *delNode, *delNode2;
	DL.ListInit(&list);

	// 4개의 데이터 저장  ///////
	DL.LInsert(&list, 20);
	DL.LInsert(&list, 30);
	DL.LInsert(&list, 40);
	DL.LInsert(&list, 50);

	// 저장된 데이터의 조회  ///////

	cout << "<데이터출력>" << endl;
	if (DL.LFirst(&list, &data))
	{
		printf("%d ", data);

		while (DL.LNext(&list, &data))
			printf("%d ", data);

		while (DL.LPrevious(&list, &data))
			printf("%d ", data);

		printf("\n\n");
	}

	cout << "<정수30 삭제 후 출력>" << endl;

	if (DL.LFirst(&list, &data) == TRUE)
	{
		if (data == 30)
		{
			DL.LRemove(&list);
		}
		while (DL.LNext(&list, &data) == TRUE)
		{
			if (data == 30)
			{
				DL.LRemove(&list);
			}
		}
	}
	if (DL.LFirst(&list, &data))
	{
		printf("%d ", data);

		while (DL.LNext(&list, &data))
			printf("%d ", data);
	}
	cout << endl;

	delNode = list.head->next;

	free(list.head);
	free(list.tail);

	while (delNode != NULL)
	{
		delNode2 = delNode;
		delNode = delNode->next;
		free(delNode2);
	}

	return 0;
}

