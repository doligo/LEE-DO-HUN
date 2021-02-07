#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdlib.h>
#include <process.h>
#include <iostream>
using namespace std;

#define SERVERPORT 9001
#define BUF_SIZE 512
#define PLAYER_MAX 2

enum Color
{
	BLACK,
	WHITE
};

enum GAME_STATUS
{
	PLAYER_WAIT,
	PLAYER_WAIT2,
	PLAYER_WAIT3,
	PLAYER_READY,
	PLAYER_START
};

enum PLAYER_COLOR
{
	PLAYERTYPE_WHITE,
	PLAYERTYPE_BLACK
};

struct Point // 오목알 좌표
{
	int x;
	int y;
};

//가장작은 바이트 단위로 차례로 정렬을 해주겠다는 의미
#pragma pack(push, 1)
struct PACKET_HEADER
{
	WORD index;
	WORD size;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct SAMEPLE_PLAYER_INFO
{
	int player_color;
	char player_name[BUF_SIZE];
	string player_cursor;
	string player_stone;
	int player_stone_count;
	Point *player_last_stone_pos;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PLAYER_INFO
{
	int player_color = 0;
	char player_name[BUF_SIZE];
};
#pragma pack(pop)

HANDLE hMutex;
int player_count = 0;
int player_wait = 0;
SOCKET client_socket[PLAYER_MAX] = {};
PLAYER_INFO send_player_packet;

unsigned WINAPI Control_Thread(void* arg)
{
	SOCKET hClient_Socket = *((SOCKET*)arg);
	SOCKADDR_IN client_addr;
	int client_addr_len = 0;
	int value = 0;
	char buf[BUF_SIZE + 1] = {};
	PACKET_HEADER *recv_packet;
	PACKET_HEADER send_packet;
	int len = 0;

	if (player_wait == 1)
		send_player_packet.player_color = 0;
	else if (player_wait == 2)
		send_player_packet.player_color = 1;

	client_addr_len = sizeof(client_addr);
	getpeername(hClient_Socket, (SOCKADDR*)&client_addr, &client_addr_len);

	value = recv(hClient_Socket, buf, sizeof(buf), NULL); // buf 양만큼 받는다
	if (value == 513)
	{
		value = send(hClient_Socket, (char*)&send_player_packet, sizeof(send_player_packet), NULL);
	}

	while (1)
	{
		value = recv(hClient_Socket, buf, sizeof(buf), NULL);
		recv_packet = (PACKET_HEADER*)buf;

		if (value == -1)
		{
			cout << "에러입니다 (리시브 에러)" << endl;
			break;
		}
		else if (value == 0)
			break;
		else if (value == 4 && recv_packet->size == 4 && recv_packet->index == PLAYER_WAIT)
		{
			send_packet.index = PLAYER_WAIT2;
			len = sizeof(send_packet);
			send_packet.size = len;
		}
		else if (player_wait == 2 && value == 4 && recv_packet->size == 4 && recv_packet->index == PLAYER_WAIT2)
		{
			send_packet.index = PLAYER_WAIT3;
			len = sizeof(send_packet);
			send_packet.size = len;
		}

		value = send(hClient_Socket, (char*)&send_packet, sizeof(send_packet), NULL);
		if (value == SOCKET_ERROR)
		{
			cout << "에러입니다 (샌드 에러)" << endl;
			break;
		}
		else if (value == 0)
			break;
	}

	cout << "유저가 접속 종료를 하였습니다 (IP : " << inet_ntoa(client_addr.sin_addr) << ")" << endl;
	closesocket(hClient_Socket);
	player_count--;
	player_wait--;
	return 0;
}

int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "윈도우 소켓 에러입니다" << endl;
		return -1;
	}
	
	hMutex = CreateMutex(NULL, FALSE, NULL);

	HANDLE hThread;
	DWORD dwThreadID;
	int value = 0;

	SOCKET listen_sock;
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);// AF_INET 주소체계 PF_INET 프로토콜 체계
	if (listen_sock == INVALID_SOCKET)
	{
		cout << "에러입니다 (listen_sock)" << endl;
		return -1;
	}

	SOCKADDR_IN server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVERPORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);// htons, htonl은 빅엔디안으로 바꿔줌

	value = bind(listen_sock, (SOCKADDR*)&server_addr, sizeof(server_addr));
	if (value == SOCKET_ERROR)
	{
		cout << "에러입니다 (bind)" << endl;
		return -1;
	}

	value = listen(listen_sock, SOMAXCONN);	// SOMAXCONN은 무한임 대기열을 무한으로 받아준다는 의미
	if (value == SOCKET_ERROR)
	{
		cout << "에러입니다 (listen)" << endl;
		return -1;
	}

	SOCKET accept_sock; // 인원초과시 사용하는 소켓
	SOCKADDR_IN client_addr; // 클라의 주소
	int addr_len; // 주소의 길이
	int str_len;
	char buf[BUF_SIZE + 1] = {};

	while (1)
	{
		if (player_count < PLAYER_MAX)
		{
			WaitForSingleObject(hMutex, INFINITE);
			addr_len = sizeof(client_addr);
			client_socket[player_count] = accept(listen_sock, (SOCKADDR*)&client_addr, &addr_len);
			str_len = strlen("접속허가");
			send(client_socket[player_count], "접속허가", str_len, 0);
			player_wait++;

			sprintf(buf, "player_%d", player_wait);
			strcpy(send_player_packet.player_name, buf);

			hThread = (HANDLE)_beginthreadex(NULL, 0, Control_Thread, (LPVOID)&client_socket[player_count], 0, (unsigned int*)&dwThreadID);
			cout << "유저가 접속을 하였습니다 (IP : " << inet_ntoa(client_addr.sin_addr) << ")" << endl;
			player_count++;
			ReleaseMutex(hMutex);
		}
		else
		{
			addr_len = sizeof(client_addr);
			accept_sock = accept(listen_sock, (SOCKADDR*)&client_addr, &addr_len);
			str_len = strlen("인원이 가득 찼습니다");
			send(accept_sock, "인원이 가득 찼습니다", str_len, 0);
			cout << "인원 초과입니다!" << endl;
			closesocket(accept_sock);
		}
	}

	closesocket(listen_sock);

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	WSACleanup();

	return 0;
}