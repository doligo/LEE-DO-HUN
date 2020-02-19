#include "Bsearch.h"



Bsearch::Bsearch()
{
}

int Bsearch::search(int arr[], int len, int target)
{
	int first = 0;
	int last = len - 1;
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
				return search(arr, len - 1, target);
			else
				return search(arr, len + 1, target);
		}

	}

	return -1;
}

Bsearch::~Bsearch()
{
}
