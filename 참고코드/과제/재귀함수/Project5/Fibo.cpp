#include "Fibo.h"



Fibo::Fibo()
{
}

int Fibo::fibo(int n)
{
	// 피보나치수열 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 ....
	if (n == 1)
	{
		return 0;
	}
	else if (n == 2)
	{
		return 1;
	}
	else
	{
		return fibo(n - 1) + fibo(n - 2);
	}

}


Fibo::~Fibo()
{
}
