#include <stdio.h>
#include <stdlib.h>
#pragma once

#define TRUE 1
#define FALSE 0
#define QUE_LEN 100

typedef int Data;

struct CQueue
{
	int front;
	int rear;
	Data queArr[QUE_LEN];
};

typedef CQueue Queues;

class Queue
{
public:
	void QueueInit(Queues *pq);
	int QIsEmpty(Queues *pq);

	void Enqueue(Queues *pq, Data data);
	Data Dequeue(Queues *pq);
	Data QPeek(Queues *pq);
	Queue();
	~Queue();
};

