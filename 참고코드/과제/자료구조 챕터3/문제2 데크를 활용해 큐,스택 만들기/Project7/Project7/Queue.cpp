#include "Queue.h"



Queue::Queue()
{
}

void Queue::Queue_Show()
{
	Head_Tail QU;
	DequeInit(&QU);

	cout << "ť�� ���� 1, 2, 3 �� �ְڽ��ϴ�" << endl;

	DQAddLast(&QU, 1);
	DQAddLast(&QU, 2);
	DQAddLast(&QU, 3);

	cout << "���Լ��� : ";
	while (!DQIsEmpty(&QU)) // NULL üũ
		printf("%d ", DQRemoveFirst(&QU));

	cout << endl;

	return;
}

Queue::~Queue()
{
}
