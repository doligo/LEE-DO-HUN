#include <iostream> 
using namespace std; 

class A 
{ 
public: 
	void func() 
	{ 
		cout << "A함수 입니다." << endl; 
	} 
}; 

class B 
{ 
public: 
	void func() 
	{ 
		cout << "B함수 입니다." << endl; 
	} 
}; 

class C : public A, public B 
{ 
public: 
	void func3()
	{ 
		func(); 
		func(); 
	}//에러 
}; 

void main() 
{ 
	C c; 
	c.func3(); 
}