#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERPORT 9001
#define BUFSIZE 512
#define MAX_PLAYER 8

//���� ���� ������ ���� ����ü
struct SOCKETINFO
{
	OVERLAPPED overlapped;
	SOCKET sock;
	char buf[BUFSIZE + 1];
	int recvbytes;
	int sendbytes;
	WSABUF wsabuf;
};

struct Player_Info
{
	char Player_Name[40];
	int Player_Character;
	int Player_Level;
	int Player_Pos; // ���ǿ��� �������� ��ġ
	char Player_Chat[50]; // ä�ó���
	int Player_Ingame_Num; // �濡 ���� ����
	bool Player_Update; // ������� �ִ��� üũ
	bool Player_Connect; // ����üũ��
	int Player_Num; // ���Ӽ���
	int Player_Checking; // ó�� ���ǿ� �������� ������ üũ�ϱ����� ��ȸ�� ����
};

SOCKET PlayerS[MAX_PLAYER];
Player_Info PlayerS_Info[MAX_PLAYER];
Player_Info *Tmp_Info;
int connect_num= 1;

//�۾��� Thread �Լ�
DWORD WINAPI WorkerThread(LPVOID arg);

//���� ��� �Լ�
void err_quit(const char* msg);
void err_display(const char* msg);

int main()
{
	int retval;

	//���� �ʱ�ȭ
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	//����� �Ϸ� ��Ʈ ����
	HANDLE hcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	if (hcp == NULL)
		return 1;
	
	//CPU ���� Ȯ��
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	//(CPU ���� * 2)���� �۾��� Thread ����
	HANDLE hThread;

	for (int i = 0; i < (int)si.dwNumberOfProcessors * 2; i++)
	{
		hThread = CreateThread(NULL, 0, WorkerThread, hcp, 0, NULL);

		if (hThread == NULL)
			return 1;

		CloseHandle(hThread);
	}

	//socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (listen_sock == INVALID_SOCKET)
		err_quit("socket()");

	//bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

	if (retval == SOCKET_ERROR)
		err_quit("bind()");

	//listen()
	retval = listen(listen_sock, SOMAXCONN);

	if (retval == SOCKET_ERROR)
		err_quit("listen()");

	//������ ��ſ� ����� ����
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	DWORD recvbytes, flags;

	while (1)
	{
		//accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);

		if (client_sock == INVALID_SOCKET)
		{
			err_display("accept()");
			break;
		}
		else
		{
			for (int i = 0; i < MAX_PLAYER; i++)
			{
				if (PlayerS[i] == NULL)
				{
					PlayerS[i] = client_sock;
					PlayerS_Info[i].Player_Num = connect_num;

					retval = send(PlayerS[i], (char*)&connect_num, sizeof(connect_num), 0);

					connect_num++;
					break;
				}
			}
		}

		printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ� = %s, ��Ʈ��ȣ = %d\n", 
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		//���ϰ� ����� �Ϸ� ��Ʈ ����
		CreateIoCompletionPort((HANDLE)client_sock, hcp, client_sock, 0);

		//���� ���� ����ü �Ҵ�
		SOCKETINFO* ptr = new SOCKETINFO;

		if (ptr == NULL)
			break;

		ZeroMemory(&ptr->overlapped, sizeof(ptr->overlapped));
		ptr->sock = client_sock;
		ptr->recvbytes = ptr->sendbytes = 0;
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = BUFSIZE;

		//�񵿱� ����� ����
		flags = 0;

		retval = WSARecv(client_sock, &ptr->wsabuf, 1, &recvbytes, &flags, &ptr->overlapped, NULL);

		if (retval == SOCKET_ERROR)
		{
			if(WSAGetLastError() != ERROR_IO_PENDING)
			{ 
				err_display("WSARecv()");
			}

			continue;
		}
	}

	//���� ����
	WSACleanup();
	return 0;
}

//�۾��� Thread
DWORD WINAPI WorkerThread(LPVOID arg)
{
	int retval;
	HANDLE hcp = (HANDLE)arg;

	while (1)
	{
		//�񵿱� ����� �Ϸ� ��ٸ���
		DWORD cbTransferred;
		SOCKET client_sock;
		SOCKETINFO* ptr;

		retval = GetQueuedCompletionStatus(hcp, &cbTransferred, (LPDWORD)&client_sock, (LPOVERLAPPED*)&ptr, INFINITE);

		//Ŭ���̾�Ʈ ���� ���
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);

		//�񵿱� ����� ��� Ȯ��
		if (retval == 0 || cbTransferred == 0)
		{
			if (retval == 0)
			{
				DWORD temp1, temp2;
				WSAGetOverlappedResult(ptr->sock, &ptr->overlapped, &temp1, FALSE, &temp2);
				err_display("WSAGetOverlappedResult()");
			}

			for (int i = 0; i < MAX_PLAYER; i++)
			{
				if (PlayerS[i] == ptr->sock)
				{
					PlayerS[i] = NULL;
					break;
				}
			}

			closesocket(ptr->sock);

			printf("[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ ��ȣ = %d\n", 
				inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

			delete ptr;
			continue;
		}

		//������ ���۸� ����
		if (ptr->recvbytes == 0)
		{
			ptr->recvbytes = cbTransferred;
			ptr->sendbytes = 0;

			Tmp_Info = (Player_Info*)ptr->buf;

			for (int i = 0; i < MAX_PLAYER; i++)
			{
				if (PlayerS[i] == ptr->sock)
				{
					PlayerS_Info[i].Player_Character = Tmp_Info->Player_Character;
					if (strlen(Tmp_Info->Player_Chat) <= 50)
						strcpy_s(PlayerS_Info[i].Player_Chat, Tmp_Info->Player_Chat);
					PlayerS_Info[i].Player_Ingame_Num = Tmp_Info->Player_Ingame_Num;
					PlayerS_Info[i].Player_Level = Tmp_Info->Player_Level;
					if (strlen(Tmp_Info->Player_Name) <= 40)
						strcpy_s(PlayerS_Info[i].Player_Name, Tmp_Info->Player_Name);
					PlayerS_Info[i].Player_Pos = Tmp_Info->Player_Pos;
					PlayerS_Info[i].Player_Update = Tmp_Info->Player_Update;
					PlayerS_Info[i].Player_Connect = Tmp_Info->Player_Connect;
					break;
				}
			}

			//���� ������ ���
			//ptr->buf[ptr->recvbytes] = '\0';
			if (cbTransferred != 1)
			{
				Tmp_Info->Player_Chat[strlen(Tmp_Info->Player_Chat) + 1] = '\0';

				printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), Tmp_Info->Player_Chat); // �ǳ����� ���� ptr->buf
			}

		}
		else
		{
			ptr->sendbytes += cbTransferred;
		}

		if (ptr->recvbytes > ptr->sendbytes)
		{
			//������ ������
			ZeroMemory(&ptr->overlapped, sizeof(ptr->overlapped));
			ptr->wsabuf.buf = ptr->buf + ptr->sendbytes;
			ptr->wsabuf.len = ptr->recvbytes - ptr->sendbytes;

			DWORD sendbytes;
			retval = WSASend(ptr->sock, &ptr->wsabuf, 1, &sendbytes, 0, &ptr->overlapped, NULL);

			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				err_display("WSASend()");
			}

			for (int i = 0; i < MAX_PLAYER; i++)
			{
				if (PlayerS_Info[i].Player_Connect == true && PlayerS[i] != NULL)
				{
					for (int j = 0; j < MAX_PLAYER; j++)
					{
						if (PlayerS_Info[j].Player_Update == true && PlayerS[j] != NULL)
						{
							retval = send(PlayerS[i], (char*)&PlayerS_Info[j], sizeof(Player_Info), 0);

							if (retval == SOCKET_ERROR)
							{
								err_display("���������۽���()");
								break;
							}
						}
					}
				}
			}

			continue;
		}
		else
		{
			ptr->recvbytes = 0;

			//������ �ޱ�
			ZeroMemory(&ptr->overlapped, sizeof(ptr->overlapped));
			ptr->wsabuf.buf = ptr->buf;
			ptr->wsabuf.len = BUFSIZE;

			DWORD recvbytes;
			DWORD flags = 0;

			retval = WSARecv(ptr->sock, &ptr->wsabuf, 1, &recvbytes, &flags, &ptr->overlapped, NULL);

			if (retval == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
				{
					err_display("WSARecv()");
				}

				continue;
			}
		}
	}

	return 0;
}

//���� �Լ� ���� ��� �� ����
void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

//���� �Լ� ���� ���
void err_display(const char* msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	//ȭ�鿡 ����ؾ� ������ ���� ������� ������ ������� ������ Window�� ǥ�õǴ� �Լ��� �����غ���!!
	printf("[%s] %s", msg, (const char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}