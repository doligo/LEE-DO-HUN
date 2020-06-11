#include <iostream>
using namespace std;

void Big(int n, int n2)
{
	if (n < n2)
	{
		if (n2 % 2 == 0)
		{
			cout << "두 정수중 큰숫자이며 짝수는 " << n2 << "입니다";
		}
		else
		{
			cout << "조건에 부합하는 숫자가 없습니다";
		}

	}
	else if (n > n2)
	{
		if (n % 2 == 0)
			cout << "두 정수중 큰숫자이며 짝수는 " << n << "입니다";
		else
		{
			cout << "조건에 부합하는 숫자가 없습니다";
		}
	}
	else
	{
		cout << "조건에 부합하는 숫자가 없습니다";
	}

}

void SungJJuck(int kor, int eng, int math)
{
	int sum = 0;

	sum = kor + eng + math;

	cout << "평균점수는 " << (sum / 3) << "입니다" << endl;
	if (sum / 3 >= 90)
		cout << "A등급" << endl;
	else if (sum / 3 >= 80)
		cout << "B등급" << endl;
	else if (sum / 3 >= 70)
		cout << "C등급" << endl;
	else if (sum / 3 >= 60)
		cout << "D등급" << endl;
	else
		cout << "F등급" << endl;
}

void Sum()
{
	int num = 0;

	for (int i = 0; i < 1001; i++)
	{
		if (i % 3 != 0)
			num += i;
		else if (i % 3 == 0 && i % 5 == 0)
			num += i;
	}
	cout << "1 ~ 1000의 합 (3의배수 제외, 3,5의 배수는 포함) : " << num << endl;
}

void Input()
{
	int num = 0;
	int sum = 0;

	while (true)
	{
		cout << "원하는 숫자를 입력하세요(0입력시 종료)";
		cin >> num;
		if (num == 0)
			break;
		else
		sum += num;
	}

	cout << "결과 : " << sum << endl;
}

void Updown()
{
	int rd = rand() % 100 + 1;
	int num = 0;
	int count = 0;

	while (1)
	{
		cout << "숫자를 맞춰보세요 : ";
		cin >> num;
		if (num > rd)
		{
			printf("%d 보다 낮다.\n", num);
			count++;
		}
		else if (num < rd)
		{
			printf("%d 보다 높다.\n", num);
			count++;
		}
		else if (num == rd)
		{
			printf("* CLEAR * %d번 만에 찾으셨습니다.\n", count);
			break;
		}
	}
}

int main()
{
	int num1, num2 = 0;
	int result = 0;
	int kor, eng, math = 0;
	
	cout << "두 정수를 입력하세요";
	cin >> num1 >> num2;
	Big(num1, num2);

	cout << endl;
	cout << "국어, 영어, 수학 점수를 입력해주세요";
	cin >> kor >> eng >> math;
	SungJJuck(kor, eng, math);
	Sum();
	Input();
	Updown();

	return 0;
}
