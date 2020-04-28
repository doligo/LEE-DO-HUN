#include <iostream>
#include "GraphDFS_BFS.h"

#define LEN_MAX 50

int main()
{
	GraphDFS_BFS GP;

	ALGraph graph;
	int tmp_V1 = 0;
	int tmp_V2 = 0;
	int num = 0;

	cout << "만들 정점의 수를 입력하세요 : ";
	cin >> num;
	GP.GraphInit(&graph, num);

	cout << "<" << num - 1 << "이하의 숫자만 입력>" << endl;
	for (int i = 0; i < num; i++)
	{
		cout << "서로 이을 정점을 한자리 정수로 각각 입력하세요 (ex :0 1) : ";
		cin >> tmp_V1 >> tmp_V2;
		GP.AddEdge(&graph, tmp_V1, tmp_V2);
	}


	GP.ShowGraphEdgeInfo(&graph);

	cout << endl;

	cout << "<깊이우선탐색>" << endl;
	GP.DFShowGraphVertex(&graph, A); printf("\n");
	GP.DFShowGraphVertex(&graph, C); printf("\n");

	cout << "<너비우선탐색>" << endl;
	GP.BFShowGraphVertex(&graph, A); printf("\n");
	GP.BFShowGraphVertex(&graph, C); printf("\n");

	GP.GraphDestroy(&graph);
	return 0;
}
