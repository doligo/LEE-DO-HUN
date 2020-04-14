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

	void Show_All(BTreeNode *bst); // ���� ��尪 �ٺ����ش�
	// Ʈ������ ��带 �����ϰ� ���ŵ� ����� �ּ� ���� ��ȯ�Ѵ�. 
	BTreeNode *BSTRemove(BTreeNode **pRoot, BSTData target);

	~BinarySearchTree();
};

