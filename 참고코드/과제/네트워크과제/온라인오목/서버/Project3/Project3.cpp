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
struct PLAYER_INFO
{
	int player_color;
	char player_name[BUF_SIZE];
	string player_cursor;
	string player_stone;
	int player_stone_count;
	Point *player_last_stone_pos;

};
#pragma pack(pop)

int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "윈도우 소켓 에러입니다" << endl;
		return -1;
	}

	int value = 0;
	HANDLE hThread[2];
	DWORD dwThreadID[2];

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
	server_addr.sin_port = htons(9000);
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

	SOCKET accept_sock; // 클라의 연결을 받는 소켓
	SOCKADDR_IN client_addr; // 클라의 주소
	int addr_len; // 주소의 길이

	while (true)
	{

	}


	return 0;
}