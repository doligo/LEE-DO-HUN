#include<iostream>
#include<string>
#define max_len 100
using namespace std;

template <typename T> // ÅÛÇÃ¸´Àû¿ë
class Student
{
private:
	T name;
	T kor, eng, math, sum;
	T avg;
	T num;
	T Class;
public:
	Student() { num = 0; }
	~Student() {}

	T SetStudent(T _num);
	T showStudent();
	T getnum()
	{
		return num;
	}
	T getname()
	{
		return name;
	}
	T getClass()
	{
		return Class;
	}
};

