#include "BinaryTree.h"
#pragma once

typedef BTData BSTData;

class BinarySearchTree : public BinaryTree
{
public:
	BinarySearchTree();

	// BST의 생성 및 초기화
	void BSTMakeAndInit(BTreeNode **pRoot);

	// 노드에 저장된 데이터 반환
	BSTData BSTGetNodeData(BTreeNode *bst);

	// BST를 대상으로 데이터 저장(노드의 생성과정 포함)
	int BSTInsert(BTreeNode **pRoot, BSTData data);

	// BST를 대상으로 데이터 탐색
	BTreeNode *BSTSearch(BTreeNode *bst, BSTData target);

	void Show_All(BTreeNode *bst); // 현재 노드값 다보여준다
	// 트리에서 노드를 제거하고 제거된 노드의 주소 값을 반환한다. 
	BTreeNode *BSTRemove(BTreeNode **pRoot, BSTData target);

	~BinarySearchTree();
};

