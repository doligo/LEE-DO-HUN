#include "Network.h"

POINT_XY Network::m_point;
bool Network::m_player_connect = false;
bool Network::m_player_turn = false;
bool Network::m_player_done_check = false;
int Network::m_set_player_color;
//// LINK 오류방지

Network::Network()
{

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
	int connect_check = 0;

	while (1)
	{
		if (connect_check == false)
		{
			send(sock, (char*)&m_player_connect, sizeof(m_player_connect), 0);
			connect_check = true;
		}
		else if (m_player_done_check == true)
		{
			send(sock, (char*)&m_point, sizeof(m_point), 0);
			m_player_done_check = false;
			m_player_turn = false;
		}
	}

	return 0;
}

unsigned WINAPI Network::Recv(void *arg)
{
	SOCKET sock = *((SOCKET*)arg);
	int value = 0;
	char buf[BUFSIZ];

	while (1)
	{
		value = recv(sock, buf, sizeof(buf), 0);

		if (value == SOCKET_ERROR)
			break;
		if (value == 0)
			break;
	}

	return 0;
}

Network::~Network()
{

}