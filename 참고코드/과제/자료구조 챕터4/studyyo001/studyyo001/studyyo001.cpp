#include "BinaryTree.h"

int main()
{
	BinaryTree BT;

	BTreeNode *bt1 = BT.MakeBTreeNode();
	BTreeNode *bt2 = BT.MakeBTreeNode();
	BTreeNode *bt3 = BT.MakeBTreeNode();
	BTreeNode *bt4 = BT.MakeBTreeNode();

	BT.SetData(bt1, 1);
	BT.SetData(bt2, 2);
	BT.SetData(bt3, 3);
	BT.SetData(bt4, 4);

	BT.MakeLeftSubTree(bt1, bt2);
	BT.MakeRightSubTree(bt1, bt3);
	BT.MakeLeftSubTree(bt2, bt4);

	//bt1의 왼쪽 자식 노드의 데이터 출력
	printf("%d \n", BT.GetData(BT.GetLeftSubTree(bt1)));

	//bt1의 왼쪽 자식 노드의 왼쪽 자식 노드의 데이터 출력
	printf("%d \n", BT.GetData(BT.GetLeftSubTree(BT.GetLeftSubTree(bt1))));

	
	cout << "삭제된 데이터 : ";
	BT.DeleteTree(bt2);


	system("pause");
	// 재귀, 함수포인터 더 보기

	return 0;
}
