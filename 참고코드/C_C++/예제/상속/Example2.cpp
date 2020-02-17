#include <iostream>
using namespace std;

class A
{
public:
	A()
	{
		cout << "A의 생성자" << endl;
	}
	~A()
	{
		cout << "A의 소멸자" << endl;
	}
};

class B : public A
{
public:
	B()
	{
		cout << "B의 생성자" << endl;
	}
	~B()
	{
		cout << "B의 소멸자" << endl;
	}
};

void main()
{
	B b;
}
