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
char buf[BUFSIZE + 1];

enum PACKET_INDEX
{
	PACKET_INDEX_CHAT,
};

#pragma pack(push, 1)
struct Packet_Chat
{
	int type;
	int size;
};
#pragma pack(pop)

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
	Packet_Chat packet;
	int return_value = 0;

	while (true)
	{
		packet.type = PACKET_INDEX_CHAT;
		cin >> msg;
		sprintf(nameMsg, "%s %s", name, msg);
		packet.size = sizeof(nameMsg);

		if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
		{
			closesocket(hSock);
			exit(0);
		}

		return_value = send(hSock, (char*)&packet, sizeof(packet), 0); // 타입과 길이를 먼저보낸다
		if (return_value == 8)
		{
			send(hSock, (char*)&nameMsg, sizeof(nameMsg), 0); // 그 후 데이터를 보낸다
			return_value = 0;
		}
		else if (return_value == -1) // 에러시 종료
			break;
	}

	return 0;
}

unsigned WINAPI RecvMsg(void *arg)
{
	int hSock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUFSIZE];
	Packet_Chat *packet = NULL;
	int return_value;

	while (1)
	{
		return_value = recv(hSock, buf, sizeof(buf), 0);
		packet = (Packet_Chat*)buf;

		if (return_value == 8 && packet->type == PACKET_INDEX_CHAT)
		{
			return_value = recv(hSock, buf, sizeof(buf), NULL);
			if (return_value == SOCKET_ERROR)
			{
				cout << "에러입니다 (recv)" << endl;
				break;
			}
			else if (return_value == 0) // 입력이 아무것도 없을시 break;
				break;
			else
				cout << buf << "\n";
		}

		if (return_value == -1)
			return -1;

	}

	return 0;
}

void ErrorHandling(const char *msg)
{
	cout << msg << "\n";
	exit(1);
}