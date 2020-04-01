#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#pragma once
using namespace std;

typedef int BTData;

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

	BTreeNode *MakeBTreeNode(void);
	BTData GetData(BTreeNode *bt);
	void SetData(BTreeNode *bt, BTData data);

	BTreeNode *GetLeftSubTree(BTreeNode *bt);
	BTreeNode *GetRightSubTree(BTreeNode *bt);

	void MakeLeftSubTree(BTreeNode *main, BTreeNode *sub);
	void MakeRightSubTree(BTreeNode *main, BTreeNode *sub);

	void DeleteTree(BTreeNode *bt);

	~BinaryTree();
};

