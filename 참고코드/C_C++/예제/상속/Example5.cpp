#include <iostream>
using namespace std;

class Mammal
{
public:
	void speak(int cnt)
	{
		cout << cnt << "¹ø Â¢´Ù" << endl;
	}
	void speak()
	{
		cout << " Â¢´Ù" << endl;
	}
};
class Dog : public Mammal
{
public:
	void speak()
	{
		cout << "¸Û¸Û" << endl;
	}
};

void main()
{
	Mammal* ptr;
	Dog jindo;
	ptr = &jindo;
	ptr->speak();
	ptr->speak(5);
}