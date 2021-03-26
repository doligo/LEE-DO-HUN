#include "NetWork.h"

NetWork::NetWork()
{
	Player_info.Player_Level = Lung;
	Player_info.Player_Pos = 0;
}

void NetWork::Init_Network(HWND hWnd)
{
	//m_hWnd = hWnd;

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

	m_SendThread = (HANDLE)_beginthreadex(NULL, 0, Send, (void*)&m_ServerSock, 0, NULL);
	m_RecvThread = (HANDLE)_beginthreadex(NULL, 0, Recv, (void*)&m_ServerSock, 0, NULL);
}

unsigned WINAPI NetWork::Send(void *arg)
{
	SOCKET sock = *((SOCKET*)arg);
	int value = 0;
	int connect_check = 0;

	while (1)
	{

		//send(sock, Player_info, sizeof(Player_info), NULL);
	}

	return 0;
}

unsigned WINAPI NetWork::Recv(void *arg)
{
	SOCKET sock = *((SOCKET*)arg);
	int value = 0;
	char buf[BUFSIZ];
	int tmp = 0;

	while (1)
	{
		value = recv(sock, buf, sizeof(buf), 0);

		if (value == SOCKET_ERROR)
			break;
		if (value == 0)
			break;

		buf[value] = '\n';  // 끝을 구별하기 위해

	}

	return 0;
}

void NetWork::Release_Network()
{
	//// 따로 분류해줘야 오브젝트를 기다리지않고 계속돌아간다
	//// 대신 종료시에 꼭 이 함수를 사용해서 해제 해줘야 한다
	//WaitForSingleObject(m_SendThread, INFINITE);
	//WaitForSingleObject(m_RecvThread, INFINITE);

	closesocket(m_ServerSock);

	WSACleanup();
}


NetWork::~NetWork()
{

}