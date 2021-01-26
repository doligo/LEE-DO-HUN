#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdlib.h>
#include <process.h>
#include <iostream>
using namespace std;

#define BUFSIZE 512
#define NAME_SIZE 20

unsigned WINAPI SendMsg(void *arg); //전방선언
unsigned WINAPI RecvMsg(void *arg);
void ErrorHandling(const char *msg);

char name[NAME_SIZE] = "[사용자]";
char msg[BUFSIZE];

struct Packet_Chat
{
	char size;
	char type;
	int id;
	char data[BUFSIZE];
};

int main()
{
	WSADATA wsaData;
	SOCKET hSock;
	SOCKADDR_IN servAdr;
	HANDLE hSndThread, hRcvThread;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!");
	}

	hSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAdr.sin_port = htons(9001);

	if (connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
		ErrorHandling("connect() error");
	}

	hSndThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSock, 0, NULL);
	hRcvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hSock, 0, NULL);

	WaitForSingleObject(hSndThread, INFINITE);
	WaitForSingleObject(hRcvThread, INFINITE);
	closesocket(hSock);
	WSACleanup();

	return 0;
}

unsigned WINAPI SendMsg(void *arg)
{
	SOCKET hSock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUFSIZE];

	while (true)
	{
		cin >> msg;

		if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
		{
			closesocket(hSock);
			exit(0);
		}

		sprintf(nameMsg, "%s %s", name, msg);
		send(hSock, nameMsg, strlen(nameMsg), 0);
	}

	return 0;
}

unsigned WINAPI RecvMsg(void *arg)
{
	int hSock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUFSIZE];
	int strLen;

	while (1)
	{
		strLen = recv(hSock, nameMsg, NAME_SIZE + BUFSIZE - 1, 0); // -1 이유는 원래 글자수를 따오기위해

		if (strLen == -1)
			return -1;

		nameMsg[strLen] = '\0'; // 문자열 끝을 알리기 위해서

		cout << nameMsg << "\n";
	}

	return 0;
}

void ErrorHandling(const char *msg)
{
	cout << msg << "\n";
	exit(1);
}