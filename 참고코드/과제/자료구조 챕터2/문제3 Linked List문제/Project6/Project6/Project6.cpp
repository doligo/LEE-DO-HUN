#pragma once
#include<iostream>
#include<Windows.h>
#include<string>
#include<time.h>
#include<fstream> // ostream ^ istream >> file system
#include<conio.h> // getch()
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct Node
{
	int data;
	struct Node * next;
};

int main(void)
{
	Node * head = NULL;    // NULL 포인터 초기화
	Node * tail = NULL;
	Node * cur = NULL;

	Node * newNode = NULL;
	int readData;
	Node * newhead = NULL; // 5를 맨앞에 위치시키기 위해 필요

	/**** 데이터를 입력 받는 과정 ****/
	while (1)
	{
		printf("자연수 입력(0입력시 데이터추가를 멈춤): ");
		scanf_s("%d", &readData);
		if (readData < 1)
			break;

		/*** 노드의 추가과정 ***/
		newNode = new Node;
		newNode->data = readData;
		newNode->next = NULL;

		if (head == NULL)
			head = newNode;
		else
			tail->next = newNode;

		tail = newNode;
	}
	printf("\n");


	
	newNode = new Node; // 헤드부분에 추가하는거
	newNode->data = 5;
	newNode->next = NULL;

	newhead = newNode;
	newhead->next = head;


	/**** 입력 받은 데이터의 출력과정 ****/
	printf("입력 받은 데이터의 전체출력! \n");
	if (head == NULL)
	{
		printf("저장된 자연수가 존재하지 않습니다. \n");
	}
	else
	{
		cur = newhead;
		printf("%d  ", cur->data);   // 첫 번째 데이터 출력

		while (cur->next != NULL)    // 두 번째 이후의 데이터 출력
		{
			cur = cur->next;
			printf("%d  ", cur->data);
		}
	}
	printf("\n\n");

	/**** 메모리의 해제과정 ****/
	if (newhead == NULL)
	{
		return 0;    // 해제할 노드가 존재하지 않는다.
	}
	else
	{
		Node * delNode = newhead; // 추가된 5부터 메모리 해제
		Node * delNextNode = newhead->next;

		printf("%d을(를) 삭제합니다. \n", newhead->data);
		free(delNode);    // 첫 번째 노드의 삭제

		while (delNextNode != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
		{
			delNode = delNextNode;
			delNextNode = delNextNode->next;

			printf("%d을(를) 삭제합니다. \n", delNode->data);
			free(delNode);    // 두 번째 이후의 노드 삭제
		}
	}

	system("pause");

	return 0;
}