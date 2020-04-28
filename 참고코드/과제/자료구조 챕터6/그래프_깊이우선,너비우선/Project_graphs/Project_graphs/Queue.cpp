#include "Queue.h"

Queue::Queue()
{
}

void Queue::QueueInit(Queues * pq)
{
	pq->front = 0;
	pq->rear = 0;
}

int Queue::QIsEmpty(Queues * pq)
{
	if (pq->front == pq->rear)
		return TRUE;
	else
		return FALSE;
}

int NextPosIdx(int pos)
{
	if (pos == QUE_LEN - 1)
		return 0;
	else
		return pos + 1;
}

void Queue::Enqueue(Queues * pq, Data data)
{
	if (NextPosIdx(pq->rear) == pq->front)
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	pq->rear = NextPosIdx(pq->rear);
	pq->queArr[pq->rear] = data;
}

Data Queue::Dequeue(Queues * pq)
{
	if (QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	pq->front = NextPosIdx(pq->front);
	return pq->queArr[pq->front];
}

Data Queue::QPeek(Queues * pq)
{
	if (QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	return pq->queArr[NextPosIdx(pq->front)];
}

Queue::~Queue()
{
}