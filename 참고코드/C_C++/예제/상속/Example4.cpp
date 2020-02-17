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
		cout << "Â¢´Ù" << endl;
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
	Mammal dongmul;
	Dog jindo;
	dongmul.speak();
	dongmul.speak(3);
	jindo.speak();
	//jindo.speak(5);
}
