#include <winsock2.h>
#include <stdlib.h>
#include <process.h>
#include <iostream>
using namespace std;

unsigned int WINAPI Thread_Recv(void *arg)
{
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (listen_sock == INVALID_SOCKET)
	{
		cout << "에러입니다 (listen_sock)" << endl;
		return -1;
	}

	SOCKADDR_IN serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int return_value = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
}

int main()
{
	int return_value;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	HANDLE hThread;
	DWORD dwThreadID;
	hThread = (HANDLE)_beginthreadex(NULL, 0, );

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	WSACleanup();

	return 0;
}