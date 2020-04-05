#include "PriorityQueue.h"
#include "UsefulHeap.h"

void PriorityQueue::PQueueInit(PQueue * ppq, PriorityComp pc)
{
	HeapInit(ppq, pc);
}

int PriorityQueue::PQIsEmpty(PQueue * ppq)
{
	return HIsEmpty(ppq);
}

void PriorityQueue::PEnqueue(PQueue * ppq, PQData data)
{
	HInsert(ppq, data);
}

PQData PriorityQueue::PDequeue(PQueue * ppq)
{
	return HDelete(ppq);
}