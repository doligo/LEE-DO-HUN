#include <iostream>
#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree BST;
	BTreeNode *BTN;
	int num = 0;
	int trigger = NULL;

	BST.BSTMakeAndInit(&BTN);

	for (int i = 0; i < 4; i++)
	{
		cout << "추가 할 데이터를 입력하세요 : ";
		cin >> num;
		trigger = BST.BSTInsert(&BTN, num);
		if (trigger == 1)
		{
			cout << "데이터가 중복됩니다" << endl;
			i--;
		}
	}

	cout << "찾을 데이터를 입력하세요 : ";
	cin >> num;
	BTN = BST.BSTSearch(BTN, num);

	if (BTN != NULL)
	{
		cout << "검색한 데이터 : " << BTN->data << endl;
	}

	else
		cout << "데이터가 없습니다" << endl;


	system("pause");

	return 0;

}
