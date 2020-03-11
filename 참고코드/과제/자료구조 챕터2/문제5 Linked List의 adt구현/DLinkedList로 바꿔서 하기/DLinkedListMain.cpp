#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"
#include "Point.h"

int main(void)
{
	// List�� ���� �� �ʱ�ȭ
	List list;
	Point *pp;
	Point *compare;
	ListInit(&list);

	// �� (x�� 2�ų� y�� 2�� ������ ����)
	compare = new Point;
	compare->xpos = 2;
	compare->ypos = 2;

	// 5���� ������ ����

	for (int i = 0, j = 1; i < 5; i++)
	{
		pp = new Point;
		SetPointPos(pp, j, i);
		Insert(&list, pp);
		j++;
	}


	// ����� �������� ��ü ��� /////////////////////////
	printf("���� �������� ��: %d \n", LCount(&list));

	if (LFirst(&list, &pp))    // ù ��° ������ ��ȸ
	{
		printf("%d %d\n", pp->xpos, pp->ypos);

		while (LNext(&list, &pp))    // �� ��° ������ ������ ��ȸ
			printf("%d %d\n", pp->xpos, pp->ypos);
	}
	printf("\n\n");

	// ���� 2�� �˻��Ͽ� ��� ���� //////////////////////////

	if (LFirst(&list, &pp)) // TRUE�� ��ȯ�Ǹ�
	{
		if (PointComp(pp, compare) == 1 || PointComp(pp, compare) == 2)
			LRemove(&list);

		while (LNext(&list, &pp))
		{
			if (PointComp(pp, compare) == 1 || PointComp(pp, compare) == 2)
				LRemove(&list);
		}
	}

	// ���� �� �����ִ� ������ ��ü ��� ////////////////////////
	printf("���� �������� ��: %d \n", LCount(&list));

	if (LFirst(&list, &pp))
	{
		printf("%d %d\n", pp->xpos, pp->ypos);

		while (LNext(&list, &pp))
			printf("%d %d\n", pp->xpos, pp->ypos);
	}
	printf("\n\n");

	system("pause");

	return 0;
}