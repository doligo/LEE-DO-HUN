#include <iostream>
#include "GraphDFS.h"

#define LEN_MAX 50

int main()
{
	GraphDFS GP;

	ALGraph graph;
	int tmp_V1 = 0;
	int tmp_V2 = 0;
	int num = 0;

	cout << "만들 정점의 수를 입력하세요 : ";
	cin >> num;
	GP.GraphInit(&graph, num);

	for (int i = 0; i < num; i++)
	{
		cout << "서로 이을 정점을 한자리 정수로 각각 입력하세요 (ex :0 1) : ";
		cin >> tmp_V1 >> tmp_V2;
		GP.AddEdge(&graph, tmp_V1, tmp_V2);
	}


	GP.ShowGraphEdgeInfo(&graph);

	GP.DFShowGraphVertex(&graph, A); printf("\n");
	GP.DFShowGraphVertex(&graph, C); printf("\n");
	GP.DFShowGraphVertex(&graph, E); printf("\n");
	GP.DFShowGraphVertex(&graph, G); printf("\n");

	GP.GraphDestroy(&graph);
	return 0;
}
