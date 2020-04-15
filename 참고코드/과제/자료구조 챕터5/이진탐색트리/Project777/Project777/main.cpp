#include <iostream>
#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree BST;
	BTreeNode *BTN;
	BTreeNode *tempBTN;
	int num = 0;
	int data[7] = {};
	int trigger = NULL;

	BST.BSTMakeAndInit(&BTN);

	for (int i = 0; i < 7; i++)
	{
		cout << "추가 할 데이터를 입력하세요 : ";
		cin >> num;
		trigger = BST.BSTInsert(&BTN, num);
		if (trigger == 1)
		{
			cout << "데이터가 중복됩니다" << endl;
			i--;
		}
		else
		{
			data[i] = num;
		}
	}

	cout << "찾을 데이터를 입력하세요 : ";
	cin >> num;
	tempBTN = BST.BSTSearch(BTN, num);

	if (tempBTN != NULL)
	{
		cout << "검색한 데이터 : " << tempBTN->data << endl;
	}

	else
		cout << "데이터가 없습니다" << endl;


	cout << "전체 데이터 : ";
	BST.Show_All(BTN);

	cout << endl;
	cout << "네번째로 넣은 데이터를 삭제하겠습니다" << endl;
	tempBTN = BST.BSTRemove(&BTN, data[3]);
	free(tempBTN);
	cout << "삭제후 : ";
	BST.Show_All(BTN);

	system("pause");

	return 0;

}
