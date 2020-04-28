#include "DLinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include <string.h>
#pragma once
using namespace std;

enum { A, B, C, D, E, F, G, H, I, J };

struct ALGraph
{
	int numV; // 정점
	int numE; // 간선
	List *adjList; // 간선정보
	int *visitInfo;
};

class GraphDFS_BFS : virtual public DLinkedList, virtual public Stack, virtual public Queue
{
public:
	// 그래프의 초기화
	void GraphInit(ALGraph * pg, int nv);

	// 그래프의 리소스 해제
	void GraphDestroy(ALGraph * pg);

	// 간선의 추가
	void AddEdge(ALGraph * pg, int fromV, int toV);

	// 유틸리티 함수: 간선의 정보 출력
	void ShowGraphEdgeInfo(ALGraph * pg);

	// Depth First Search: 정점의 정보 출력
	void DFShowGraphVertex(ALGraph * pg, int startV);

	// Breadth First Search: 정점의 정보 출력
	void BFShowGraphVertex(ALGraph * pg, int startV);

	GraphDFS_BFS();
	~GraphDFS_BFS();
};

