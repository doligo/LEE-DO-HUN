#include "Queue.h"



Queue::Queue()
{
}

void Queue::Queue_Show()
{
	Head_Tail QU;
	DequeInit(&QU);

	cout << "큐로 정수 1, 2, 3 을 넣겠습니다" << endl;

	DQAddLast(&QU, 1);
	DQAddLast(&QU, 2);
	DQAddLast(&QU, 3);

	cout << "선입선출 : ";
	while (!DQIsEmpty(&QU)) // NULL 체크
		printf("%d ", DQRemoveFirst(&QU));

	cout << endl;

	return;
}

Queue::~Queue()
{
}
