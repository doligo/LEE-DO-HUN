#include "Bsearch.h"



Bsearch::Bsearch()
{
}

int Bsearch::search(int arr[], int first, int last, int target)
{

	int mid;

	while (first <= last)
	{
		mid = (first + last) / 2;

		if (target == arr[mid])
		{
			return mid;
		}
		else
		{
			if (target < arr[mid])
				return search(arr, first, last - 1, target);
			else
				return search(arr, first + 1, last, target);
		}
	}

	return -1;
}

Bsearch::~Bsearch()
{
}
