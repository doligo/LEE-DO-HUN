#include <iostream>
#include <stdio.h>
#include "UsefulHeap.h"

int PriComp(int n1, int n2)
{
	return n1 - n2;
	//return n1 - n2;
}

void HeapSort(int arr[], int n, PriorityComp pc)
{
	Heap heap;

	HeapInit(&heap, pc);

	for (int i = 0; i < n; i++)
		HInsert(&heap, arr[i]);

	for (int i = 0; i < n; i++)
		arr[i] = HDelete(&heap);
}

int main()
{
	int arr[4] = {5, 8, 3, 1};

	HeapSort(arr, sizeof(arr) / sizeof(int), PriComp);

	for (int i = 0; i < 4; i++)
		printf("%d ", arr[i]);

	printf("\n");
	return 0;
}