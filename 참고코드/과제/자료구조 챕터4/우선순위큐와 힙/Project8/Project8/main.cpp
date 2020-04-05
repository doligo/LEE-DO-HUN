#include <stdio.h>
#include <iostream>
#include "PriorityQueue.h"

int DataPriorityComp(string ch1, string ch2)
{
	if (ch1.length() > ch2.length())
	{
		return -1;
	}
	else
		return 1;
}

int main(void)
{
	PriorityQueue PQE;

	PQueue pq;
	PQE.PQueueInit(&pq, DataPriorityComp);

	PQE.PEnqueue(&pq, "CAT");
	PQE.PEnqueue(&pq, "FLOWER");
	PQE.PEnqueue(&pq, "DARKS");
	cout << "���ݱ��� ���� ������ �� ���ڱ��̰� ª�� �� : ";
	cout << PQE.PDequeue(&pq) << endl;

	PQE.PEnqueue(&pq, "ASSISTER");
	PQE.PEnqueue(&pq, "BANDNEW");
	PQE.PEnqueue(&pq, "CAKE");
	cout << "�״��� ���ݱ��� ���� ������ �� ���ڱ��̰� ª�� �� : ";
	cout << PQE.PDequeue(&pq) << endl;

	cout << "���� ������ ª������ ������� ���ʴ�� ���" << endl;
	while (!PQE.PQIsEmpty(&pq))
		cout << PQE.PDequeue(&pq) << endl;

	return 0;
}
