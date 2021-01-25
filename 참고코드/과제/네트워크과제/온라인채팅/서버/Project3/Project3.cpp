#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdlib.h>
#include <process.h>
#include <iostream>
using namespace std;

#define SERVERPORT 9001
#define BUFSIZE 512
#define MAX_PEOPLE 2
SOCKADDR_IN serveraddr[MAX_PEOPLE];

enum PACKET_INDEX
{
	PACKET_INDEX_CHAT,
};

//가장작은 바이트 단위로 차례로 정렬을 해주겠다는 의미
#pragma pack(push, 1)
struct Packet_Chat
{
	char size;
	char type;
	int id;
	char data[BUFSIZE];
};
#pragma pack(pop)

void Recive(SOCKET sock)
{
	char buf[BUFSIZE + 1];
	SOCKADDR_IN client_addr;
	int addrlen;
	int return_value;

	addrlen = sizeof(client_addr);

	getpeername(sock, (SOCKADDR*)&client_addr, &addrlen); // client_addr에 정보를 넣기위해 필요함

	while (1)
	{
		for (int i = 0; i < BUFSIZE; i++)
		{
			buf[i] = '\0';
		}

		return_value = recv(sock, buf, BUFSIZE, NULL);

		if (return_value == SOCKET_ERROR)
		{
			cout << "에러입니다 (recv)" << endl;
			break;
		}
		else if (return_value == 0) // 입력이 아무것도 없을시 break;
			break;

		buf[return_value] = '\0'; // 문자열의 끝을 알리기위해 넣음
		cout << "[TCP " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << "]" << &buf[sizeof(Packet_Chat)];

		return_value = send(sock, buf, return_value, 0);

		if (return_value == SOCKET_ERROR)
		{
			cout << "에러입니다 (send)" << endl;
			break;
		}
	}

	closesocket(sock);
	cout << "[TCP 서버] 클라이언트 종료 ip = " << inet_ntoa(client_addr.sin_addr) << ",포트 = " << ntohs(client_addr.sin_port) << endl;
}

unsigned int WINAPI Thread_Recv(void *arg)
{
	// 임계구역 추가?
	int num = 0;
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (listen_sock == INVALID_SOCKET)
	{
		cout << "에러입니다 (listen_sock)" << endl;
		return -1;
	}
	else
	{
		cout << "good" << endl;
	}

	if (serveraddr[num].sin_family != 0)
		num++;
	serveraddr[num].sin_family = AF_INET;
	serveraddr[num].sin_port = htons(SERVERPORT);
	serveraddr[num].sin_addr.s_addr = htonl(INADDR_ANY);

	int return_value = bind(listen_sock, (SOCKADDR*)&serveraddr[num], sizeof(serveraddr[num]));

	if (return_value == SOCKET_ERROR)
	{
		cout << "에러입니다 (bind)" << endl;
		return -1;
	}
	else
	{
		cout << "good" << endl;
	}

	return_value = listen(listen_sock, SOMAXCONN);
	
	if (return_value == SOCKET_ERROR)
	{
		cout << "에러입니다 (listen)" << endl;
		return -1;
	}

	SOCKET accept_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;
	DWORD Thread_id;

	while (1)
	{
		addrlen = sizeof(clientaddr);
		accept_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (accept_sock == INVALID_SOCKET)
		{
			cout << "에러입니다 (accept)";
			continue;
		}

		cout << "[TCP 서버] 클라이언트 접속 ip = " << inet_ntoa(clientaddr.sin_addr) << ",포트 = " << ntohs(clientaddr.sin_port) << endl;

		Recive(accept_sock);
	}
	closesocket(listen_sock);
}

int main()
{
	int return_value;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	HANDLE hThread[MAX_PEOPLE];
	DWORD dwThreadID[MAX_PEOPLE];

	for (int i = 0; i < 2; i ++)
		memset(&serveraddr[i], 0, sizeof(serveraddr[i]));

	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, Thread_Recv, NULL, 0, (unsigned*)&dwThreadID[0]);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, Thread_Recv, NULL, 0, (unsigned*)&dwThreadID[1]);

	WaitForSingleObject(hThread[0], INFINITE); // 종료하기를 기다림
	WaitForSingleObject(hThread[1], INFINITE);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	WSACleanup();

	return 0;
}