#include "DLinkedList.h"
#include "Stack.h"
#include "Queue.h"
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

class GraphDFS_BFS : virtual public DLinkedList, virtual public Stack, virtual public Queue
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

	// Breadth First Search: ������ ���� ���
	void BFShowGraphVertex(ALGraph * pg, int startV);

	GraphDFS_BFS();
	~GraphDFS_BFS();
};

