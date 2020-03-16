#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"
#include "Point.h"


int WhoIsPrecede(Node *d1, Node *d2) // �������� 1 2 3 4 ...
{
	if (d1 == NULL)
		return 0;
	else if (d1->data->xpos < d2->data->xpos)
		return 1; // d1 �� ���� ������ �ռ���
	else if (d1->data->xpos == d2->data->xpos) // x���� ������� y�� ��
	{
		if (d1->data->ypos < d2->data->ypos)
			return 1;
		else
			return 0;
	}
	else
		return 0; // d2 �� ���� ������ �ռ��ų� ����
}

int main(void)

{
	// List�� ���� �� �ʱ�ȭ
	List list;
	Point *pp;
	Point *compare;
	ListInit(&list);

	SetSortRule(&list, WhoIsPrecede); // �ּҰ��� �Ѱ������Ƿ� ��� �ּҰ��� ����ִ�

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

	if (compare != NULL)
	{
		delete compare;
		compare = NULL;
	}

	system("pause");

	return 0;
}