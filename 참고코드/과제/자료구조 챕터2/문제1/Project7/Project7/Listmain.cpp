#include "ArrayList.h"
#include <iostream>
using namespace std;


void Plus(ArrayList *name, int n, int s)
{
	for (int i = 1; i < 10; i++)
	{
		Linsert(name, i);
	}

	if (LFirst(name, &n) == TRUE)
	{
		s += n;
	}

	while (1)
	{
		if (LNext(name, &n) == TRUE)
		{
			s += n;
		}
		else
		{
			break;
		}
	}

	cout << "리스트의 합 : " << s << endl;
}

int Multiple(ArrayList *name)
{
	int i = 0;
	int num = 0;

	cout << "삭제된 값 : ";

	while (i != name->numOfData)
	{
		if (name->arr[i] % 2 == 0 || name->arr[i] % 3 == 0)
		{
			name->curPosition = i;
			num = LRemove(name);
			cout << num << " ";
		}
		else
		{
			i++;
		}
	}

	cout << endl;

	return 0;
}

void Result(ArrayList *name, int n)
{
	cout << "리스트의 결과값 : ";
	if (LFirst(name, &n) == TRUE)
	{
		cout << n << " ";
	}

	while (1)
	{
		if (LNext(name, &n) == TRUE)
		{
			cout << n << " ";
		}
		else
		{
			break;
		}
	}
}

void main()
{
	ArrayList Array;
	int num = 0;
	int sum = 0;

	ListInit(&Array);
	Plus(&Array, num, sum);
	Multiple(&Array);
	Result(&Array, num);

	system("pause");
}