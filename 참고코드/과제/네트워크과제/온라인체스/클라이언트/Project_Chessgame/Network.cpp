#include "Network.h"

Network::Network()
{
	m_player_connect = false;
}

void Network::Init_Network(HWND hWnd)
{
	m_hWnd = hWnd;
	
	if (WSAStartup(MAKEWORD(2, 2), &m_WsaData) != 0)
	{
		cout << "WSAStartup() Error!" << endl;
		system("pause");
	}

	m_ServerSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&m_ServerAddr, 0, sizeof(m_ServerAddr));
	m_ServerAddr.sin_family = AF_INET;
	m_ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	m_ServerAddr.sin_port = htons(9001);

	if (connect(m_ServerSock, (SOCKADDR*)&m_ServerAddr, sizeof(m_ServerAddr)) == SOCKET_ERROR)
	{
		cout << "Connet() Error!" << endl;
		system("pause");
		return;
	}

	m_player_connect = true;

	m_SendThread = (HANDLE)_beginthreadex(NULL, 0, Send, (void*)&m_ServerSock, 0, NULL);
	m_RecvThread = (HANDLE)_beginthreadex(NULL, 0, Recv, (void*)&m_ServerSock, 0, NULL);

	WaitForSingleObject(m_SendThread, INFINITE);
	WaitForSingleObject(m_RecvThread, INFINITE);

	closesocket(m_ServerSock);

	WSACleanup();
}

unsigned WINAPI Network::Send(void *arg)
{
	SOCKET sock = *((SOCKET*)arg);
	int value = 0;


	return 0;
}

unsigned WINAPI Network::Recv(void *arg)
{
	SOCKET sock = *((SOCKET*)arg);
	int value = 0;

	return 0;
}

Network::~Network()
{

}