#include <iostream>
using namespace std;

class A
{
private:
	int m_ia;
protected:
	int m_ib;
public:
	int m_ic;
	void Test()
	{
		m_ia = 10;
		m_ib = 10;
		m_ic = 10;
	}
};
class B : public A
{
	void Test()
	{
		m_ia = 10;
		m_ib = 10;
		m_ic = 10;
	}
};

class C : public B
{
	void Test()
	{
		m_ia = 10;
		m_ib = 10;
		m_ic = 10;
	}
};

void main()
{
	B b;
	b.m_ia = 10;
	b.m_ib = 10;
	b.m_ic = 10;
}
