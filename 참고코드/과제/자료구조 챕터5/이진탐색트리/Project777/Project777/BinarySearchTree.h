#include "BinaryTree.h"
#pragma once

typedef BTData BSTData;

class BinarySearchTree : public BinaryTree
{
public:
	BinarySearchTree();

	// BST�� ���� �� �ʱ�ȭ
	void BSTMakeAndInit(BTreeNode **pRoot);

	// ��忡 ����� ������ ��ȯ
	BSTData BSTGetNodeData(BTreeNode *bst);

	// BST�� ������� ������ ����(����� �������� ����)
	int BSTInsert(BTreeNode **pRoot, BSTData data);

	// BST�� ������� ������ Ž��
	BTreeNode *BSTSearch(BTreeNode *bst, BSTData target);

	~BinarySearchTree();
};

