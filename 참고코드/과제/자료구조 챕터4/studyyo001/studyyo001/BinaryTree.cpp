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
	if (bt == NULL)
	{
		printf("데이터가 없습니다\n");
		return 1;
	}

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
	{
		free(main->left);
	}

	main->left = sub;
}

void BinaryTree::MakeRightSubTree(BTreeNode *main, BTreeNode *sub)
{
	if (main->right != NULL)
	{
		free(main->right);
	}

	main->right = sub;
}

void BinaryTree::DeleteTree(BTreeNode *bt)
{
	if (bt->data != NULL)
	{
		free(bt);
		bt->data = NULL;
		bt->left = NULL;
		bt->right = NULL;
	}
}

BinaryTree::~BinaryTree()
{
}
