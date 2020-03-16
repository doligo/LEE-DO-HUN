#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"
#include "Point.h"


int WhoIsPrecede(Node *d1, Node *d2) // 오름차순 1 2 3 4 ...
{
	if (d1 == NULL)
		return 0;
	else if (d1->data->xpos < d2->data->xpos)
		return 1; // d1 이 정렬 순서상 앞선다
	else if (d1->data->xpos == d2->data->xpos) // x값이 같을경우 y값 비교
	{
		if (d1->data->ypos < d2->data->ypos)
			return 1;
		else
			return 0;
	}
	else
		return 0; // d2 가 정렬 순서상 앞서거나 같다
}

int main(void)

{
	// List의 생성 및 초기화
	List list;
	Point *pp;
	Point *compare;
	ListInit(&list);

	SetSortRule(&list, WhoIsPrecede); // 주소값을 넘겨줬으므로 계속 주소값을 들고있다

	// 비교 (x가 2거나 y가 2면 삭제할 예정)
	compare = new Point;
	compare->xpos = 2;
	compare->ypos = 2;

	// 5개의 데이터 저장


	for (int i = 0, j = 1; i < 5; i++)
	{
		pp = new Point;
		SetPointPos(pp, j, i);
		Insert(&list, pp);
		j++;
	}


	// 저장된 데이터의 전체 출력 /////////////////////////
	printf("현재 데이터의 수: %d \n", LCount(&list));

	if (LFirst(&list, &pp))    // 첫 번째 데이터 조회
	{
		printf("%d %d\n", pp->xpos, pp->ypos);

		while (LNext(&list, &pp))    // 두 번째 이후의 데이터 조회
			printf("%d %d\n", pp->xpos, pp->ypos);
	}
	printf("\n\n");

	// 숫자 2를 검색하여 모두 삭제 //////////////////////////

	if (LFirst(&list, &pp)) // TRUE가 반환되면
	{
		if (PointComp(pp, compare) == 1 || PointComp(pp, compare) == 2)
			LRemove(&list);

		while (LNext(&list, &pp))
		{
			if (PointComp(pp, compare) == 1 || PointComp(pp, compare) == 2)
				LRemove(&list);
		}
	}

	// 삭제 후 남아있는 데이터 전체 출력 ////////////////////////
	printf("현재 데이터의 수: %d \n", LCount(&list));

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