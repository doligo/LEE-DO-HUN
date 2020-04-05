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
	cout << "지금까지 넣은 데이터 중 문자길이가 짧은 것 : ";
	cout << PQE.PDequeue(&pq) << endl;

	PQE.PEnqueue(&pq, "ASSISTER");
	PQE.PEnqueue(&pq, "BANDNEW");
	PQE.PEnqueue(&pq, "CAKE");
	cout << "그다음 지금까지 넣은 데이터 중 문자길이가 짧은 것 : ";
	cout << PQE.PDequeue(&pq) << endl;

	cout << "남은 데이터 짧은길이 순서대로 차례대로 출력" << endl;
	while (!PQE.PQIsEmpty(&pq))
		cout << PQE.PDequeue(&pq) << endl;

	return 0;
}
