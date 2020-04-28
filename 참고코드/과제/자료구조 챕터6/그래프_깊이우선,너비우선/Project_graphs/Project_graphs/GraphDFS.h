#include "DLinkedList.h"
#include "Stack.h"
#include <string.h>
#pragma once
using namespace std;

enum { A, B, C, D, E, F, G, H, I, J };

struct ALGraph
{
	int numV; // ����
	int numE; // ����
	List *adjList; // ��������
	int *visitInfo;
};

class GraphDFS : virtual public DLinkedList, virtual public Stack
{
public:
	// �׷����� �ʱ�ȭ
	void GraphInit(ALGraph * pg, int nv);

	// �׷����� ���ҽ� ����
	void GraphDestroy(ALGraph * pg);

	// ������ �߰�
	void AddEdge(ALGraph * pg, int fromV, int toV);

	// ��ƿ��Ƽ �Լ�: ������ ���� ���
	void ShowGraphEdgeInfo(ALGraph * pg);

	// Depth First Search: ������ ���� ���
	void DFShowGraphVertex(ALGraph * pg, int startV);
	GraphDFS();
	~GraphDFS();
};

