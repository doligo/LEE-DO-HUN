#include "Stack.h"



Stack::Stack()
{
}

void Stack::Stack_Show()
{
	Head_Tail HT;
	DequeInit(&HT);

	cout << "�������� ���� 1, 2, 3 �� �ְڽ��ϴ�" << endl;

	DQAddLast(&HT, 1);
	DQAddLast(&HT, 2);
	DQAddLast(&HT, 3);


	cout << "���Լ��� : ";
	while (!DQIsEmpty(&HT)) // NULL üũ
		printf("%d ", DQRemoveLast(&HT));

	cout << endl;


	return;
}


Stack::~Stack()
{
}
