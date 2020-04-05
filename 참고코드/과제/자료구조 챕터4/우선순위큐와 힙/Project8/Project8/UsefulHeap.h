#include <iostream>
#include <stdio.h>
#include <string>
#pragma once
using namespace std;

#define TRUE 1
#define FALSE 0
#define HEAP_LEN 100

typedef string HData;
typedef int PriorityComp(HData d1, HData d2);


struct Heap
{
	PriorityComp *comp;
	int numOfData;
	HData heapArr[HEAP_LEN];
};

class UsefulHeap
{
public:
	void HeapInit(Heap *ph, PriorityComp pc);
	int HIsEmpty(Heap *ph);
	void HInsert(Heap *ph, HData data);
	HData HDelete(Heap *ph);

	int GetParentIDX(int idx);
	int GetLChildIDX(int idx);
	int GetRChildIDX(int idx);
	int GetHiPriChildIDX(Heap *ph, int idx);
};

