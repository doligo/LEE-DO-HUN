#include "Fibo.h"
#include "Bsearch.h"

int main()
{
	Fibo ff;
	Bsearch bb;

	int num = 0;
	int result = 0;

	int arr[] = { 1, 3, 5, 7, 9 };
	int idx = 0;

	cout << "정수를 입력하세요 : ";
	cin >> num;

	result = ff.fibo(num);

	cout << result << "입니다" << endl;

	////////////////////////////

	cout << "찾을 숫자를 입력하세요 : ";
	cin >> num;

	idx = bb.search(arr, 0, (sizeof(arr) / sizeof(int)) - 1, num); // int 안쓰면 5 * 자료형크기 되버림

	if (idx == -1)
		cout << "탐색 실패" << endl;
	else
		cout << "타겟 저장 인덱스 : " << idx << endl;

	system("pause");
}
