#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#pragma once
using namespace std;

typedef int BTData;
typedef void VisitFuncPtr(BTData data);

struct BTreeNode
{
	BTData data;
	struct BTreeNode *left;
	struct BTreeNode *right;
};

class BinaryTree
{
public:
	BinaryTree();

	BTreeNode *MakeBTreeNode();
	BTData GetData(BTreeNode *bt);
	void SetData(BTreeNode *bt, BTData data);

	BTreeNode *GetLeftSubTree(BTreeNode *bt);
	BTreeNode *GetRightSubTree(BTreeNode *bt);

	void MakeLeftSubTree(BTreeNode *main, BTreeNode *sub);
	void MakeRightSubTree(BTreeNode *main, BTreeNode *sub);

	void PreorderTraverse(BTreeNode *bt, VisitFuncPtr action);
	void InorderTraverse(BTreeNode *bt, VisitFuncPtr action);
	void PostorderTraverse(BTreeNode *bt, VisitFuncPtr action);

	// 왼쪽 자식 노드 제거, 제거된 노드의 주소 값이 반환된다.
	BTreeNode * RemoveLeftSubTree(BTreeNode * bt);

	// 오른쪽 자식 노드 제거, 제거된 노드의 주소 값이 반환된다.
	BTreeNode * RemoveRightSubTree(BTreeNode * bt);

	// 메모리 소멸을 수반하지 않고 main의 왼쪽 자식 노드를 변경한다. 
	void ChangeLeftSubTree(BTreeNode * main, BTreeNode * sub);

	// 메모리 소멸을 수반하지 않고 main의 오른쪽 자식 노드를 변경한다. 
	void ChangeRightSubTree(BTreeNode * main, BTreeNode * sub);

	~BinaryTree();
};

