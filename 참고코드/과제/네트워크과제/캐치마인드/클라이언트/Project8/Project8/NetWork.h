#pragma once
#include <windows.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <process.h> // _beginthreadex 쓰기위해서
#include <iostream>
using namespace std;

#define MAX_PLAYER 8

enum P_LEVELS
{
	Lung = 100,
	Lumi,
};

struct Player_Info
{
	char Player_Name[40];
	int Player_Character;
	int Player_Level;
	int Player_Pos; // 대기실에서 보여지는 위치
	char Player_Chat[50]; // 채팅내용
	int Player_Ingame_Num; // 방에 들어온 순서
	bool Player_Update; // 변경사항 있는지 체크
	bool Player_Connect; // 접속체크용
	int Player_Num; // 접속순서
	int Player_Checking; // 처음 대기실에 왔을때만 정보를 체크하기위한 일회성 변수
};

class NetWork
{
private:
	WSADATA m_WsaData;
	SOCKET m_ServerSock;
	SOCKADDR_IN m_ServerAddr;
	HANDLE m_SendThread;
	HANDLE m_RecvThread;

	HWND m_hWnd;
public:
	NetWork();

	void Init_Network(HWND hWnd);
	static unsigned WINAPI Send(void *arg);
	static unsigned WINAPI Recv(void *arg);
	void Release_Network();

	static bool m_player_connect;
	static Player_Info Player_info;
	static Player_Info Recv_Player_info[MAX_PLAYER]; // 상대편플레이어 정보
	static int m_player_wait_room;
	static bool m_player_first_send;

	~NetWork();
};

