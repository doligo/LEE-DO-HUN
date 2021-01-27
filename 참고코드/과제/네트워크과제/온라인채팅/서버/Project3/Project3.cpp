#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdlib.h>
#include <process.h>
#include <iostream>
using namespace std;

#define SERVERPORT 9001
#define BUFSIZE 512
#define MAX 2

enum PACKET_INDEX
{
	PACKET_INDEX_CHAT,
};

//가장작은 바이트 단위로 차례로 정렬을 해주겠다는 의미
#pragma pack(push, 1)
struct Packet_Chat
{
	int type;
	int size;
	char data[BUFSIZE];
};
#pragma pack(pop)

char buf[BUFSIZE + 1];
int save_value;

unsigned int WINAPI Thread_Recv(void *arg)
{
	SOCKET client_sock = (SOCKET)arg;
	SOCKADDR_IN client_addr;
	int addrlen;
	int return_value = 0;

	addrlen = sizeof(client_addr);

	getpeername(client_sock, (SOCKADDR*)&client_addr, &addrlen); // client_addr에 정보를 넣기위해 필요함

	while (1)
	{
		return_value = recv(client_sock, buf, BUFSIZE, NULL);

		if (return_value == SOCKET_ERROR)
		{
			cout << "에러입니다 (recv)" << endl;
			break;
		}
		else if (return_value == 0) // 입력이 아무것도 없을시 break;
			break;
		else
			save_value = return_value;

		buf[return_value] = '\0'; // 문자열의 끝을 알리기위해 넣음

		cout << "[TCP " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << "][" << &buf[sizeof(char)] << endl;

		return_value = 0;
	}

	closesocket(client_sock);
	cout << "[TCP 서버] 클라이언트 종료 ip = " << inet_ntoa(client_addr.sin_addr) << ",포트 = " << ntohs(client_addr.sin_port) << endl;

	return 0;
}

unsigned int WINAPI Thread_Send(void *arg)
{
	SOCKET client_sock = (SOCKET)arg;
	SOCKADDR_IN client_addr;
	int addrlen;
	int return_value = 0;

	addrlen = sizeof(client_addr);

	getpeername(client_sock, (SOCKADDR*)&client_addr, &addrlen); // client_addr에 정보를 넣기위해 필요함

	while (1)
	{
		if (save_value != 0)
		{
			return_value = send(client_sock, buf, save_value, 0);
			save_value = 0;
		}

		if (return_value == SOCKET_ERROR)
		{
			cout << "에러입니다 (send)" << endl;
			break;
		}

	}
	closesocket(client_sock);
	return 0;
}

int main()
{
	int return_value;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	HANDLE hThread[MAX];
	DWORD dwThreadID[MAX];

	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0); // 받을준비하는 소켓생성한다

	if (listen_sock == INVALID_SOCKET)
	{
		cout << "에러입니다 (listen_sock)" << endl;
		return -1;
	}

	SOCKADDR_IN serveraddr; // 바인드 전에 서버주소가 필요하니까 서버주소 설정해준다
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVERPORT);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	return_value = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr)); // 묶어주고 오류체크한다

	if (return_value == SOCKET_ERROR)
	{
		cout << "에러입니다 (bind)" << endl;
		return -1;
	}

	return_value = listen(listen_sock, SOMAXCONN); // 클라 요청을 기다린다

	if (return_value == SOCKET_ERROR)
	{
		cout << "에러입니다 (listen)" << endl;
		return -1;
	}

	SOCKET accept_sock; // 클라연결소켓
	SOCKADDR_IN clientaddr; //클라 주소
	int addrlen;

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

		hThread[0] = (HANDLE)_beginthreadex(NULL, 0, Thread_Recv, (LPVOID)accept_sock, 0, (unsigned*)&dwThreadID[0]);
		hThread[1] = (HANDLE)_beginthreadex(NULL, 0, Thread_Send, (LPVOID)accept_sock, 0, (unsigned*)&dwThreadID[1]);
		// hThread[1]는 Thread_Send 함수를 만들어서 클라한테 채팅을 보여주는걸 구현하도록 한다
		// 리시브, 샌드 따로설정

	}
	closesocket(listen_sock);


	WaitForSingleObject(hThread[0], INFINITE); // 종료하기를 기다림
	WaitForSingleObject(hThread[1], INFINITE);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	WSACleanup();
	return 0;
}

void ErrorHandling(const char *message)
{
	cout << "Error" << message << "\n";
	exit(1);
}
