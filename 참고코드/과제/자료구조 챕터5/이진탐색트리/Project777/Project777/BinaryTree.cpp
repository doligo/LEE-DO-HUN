#include "BinaryTree.h"


BinaryTree::BinaryTree()
{
}

BTreeNode *BinaryTree::MakeBTreeNode()
{
	BTreeNode *nd = new BTreeNode;

	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

BTData BinaryTree::GetData(BTreeNode *bt)
{
	return bt->data;
}
void BinaryTree::SetData(BTreeNode *bt, BTData data)
{
	bt->data = data;
}

BTreeNode *BinaryTree::GetLeftSubTree(BTreeNode *bt)
{
	return bt->left;
}

BTreeNode *BinaryTree::GetRightSubTree(BTreeNode *bt)
{
	return bt->right;
}

void BinaryTree::MakeLeftSubTree(BTreeNode *main, BTreeNode *sub)
{
	if (main->left != NULL)
		free(main->left);

	main->left = sub;
}

void BinaryTree::MakeRightSubTree(BTreeNode *main, BTreeNode *sub)
{
	if (main->right != NULL)
		free(main->right);

	main->right = sub;
}

void BinaryTree::PreorderTraverse(BTreeNode *bt, VisitFuncPtr action)
{
	if (bt == NULL)
		return;

	action(bt->data);
	PreorderTraverse(bt->left, action);
	PreorderTraverse(bt->right, action);
}

void BinaryTree::InorderTraverse(BTreeNode *bt, VisitFuncPtr action)
{
	if (bt == NULL)
		return;

	InorderTraverse(bt->left, action);
	action(bt->data);
	InorderTraverse(bt->right, action);
}

void BinaryTree::PostorderTraverse(BTreeNode *bt, VisitFuncPtr action)
{
	if (bt == NULL)
		return;

	PostorderTraverse(bt->left, action);
	PostorderTraverse(bt->right, action);
	action(bt->data);
}

// 왼쪽 자식 노드 제거, 제거된 노드의 주소 값이 반환된다.
BTreeNode *BinaryTree::RemoveLeftSubTree(BTreeNode * bt)
{
	BTreeNode * delNode;

	if (bt != NULL) {
		delNode = bt->left;
		bt->left = NULL;
	}
	return delNode;
}

// 오른쪽 자식 노드 제거, 제거된 노드의 주소 값이 반환된다.
BTreeNode *BinaryTree::RemoveRightSubTree(BTreeNode * bt)
{
	BTreeNode * delNode;

	if (bt != NULL) {
		delNode = bt->right;
		bt->right = NULL;
	}
	return delNode;
}

// 메모리 소멸을 수반하지 않고 main의 왼쪽 자식 노드를 변경한다. 
void BinaryTree::ChangeLeftSubTree(BTreeNode * main, BTreeNode * sub)
{
	main->left = sub;
}

// 메모리 소멸을 수반하지 않고 main의 오른쪽 자식 노드를 변경한다. 
void BinaryTree::ChangeRightSubTree(BTreeNode * main, BTreeNode * sub)
{
	main->right = sub;
}

BinaryTree::~BinaryTree()
{
}
