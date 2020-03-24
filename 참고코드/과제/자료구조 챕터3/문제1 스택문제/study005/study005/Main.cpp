#include <iostream>
#include "CLinkedList.h"

int main()
{
	// 원형 연결 리스트의 생성 및 초기화 ///////
	Clist list;
	CLinkedList Lt;
	int data, i;

	Lt.StackInit(&list);

	// 리스트에 5개의 데이터를 저장 /////// 

	Lt.SPush(&list, 1);
	Lt.SPush(&list, 2);
	Lt.SPush(&list, 3);
	Lt.SPush(&list, 4);
	Lt.SPush(&list, 5);

	cout << "들어간 값의 순서는 1, 2, 3, 4, 5 입니다" << endl;
	cout << "마지막으로 들어간 값은 : " << Lt.SPeek(&list);
	cout << endl << endl;
	cout << "<LIFO>" << endl;

	while (Lt.SIsEmpty(&list) == FALSE)
	{
		cout << Lt.SPop(&list) << " ";
	}
	

	system("pause");
	return 0;
}