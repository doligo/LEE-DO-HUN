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

	~BinaryTree();
};

