#include "UsefulHeap.h"
#pragma once

typedef Heap PQueue;
typedef HData PQData;

class PriorityQueue : virtual public UsefulHeap
{
public:
	void PQueueInit(PQueue *ppq, PriorityComp pc);
	int PQIsEmpty(PQueue *ppq);

	void PEnqueue(PQueue *ppq, PQData data);
	PQData PDequeue(PQueue *ppq);
};

