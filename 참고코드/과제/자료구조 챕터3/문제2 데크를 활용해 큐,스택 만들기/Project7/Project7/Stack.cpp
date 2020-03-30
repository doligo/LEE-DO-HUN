#include "Stack.h"



Stack::Stack()
{
}

void Stack::Stack_Show()
{
	Head_Tail HT;
	DequeInit(&HT);

	cout << "스택으로 정수 1, 2, 3 을 넣겠습니다" << endl;

	DQAddLast(&HT, 1);
	DQAddLast(&HT, 2);
	DQAddLast(&HT, 3);


	cout << "후입선출 : ";
	while (!DQIsEmpty(&HT)) // NULL 체크
		printf("%d ", DQRemoveLast(&HT));

	cout << endl;


	return;
}


Stack::~Stack()
{
}
