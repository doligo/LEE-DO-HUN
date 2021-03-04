#pragma once
#include <Windows.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <iostream>
using namespace std;

#define WM_SOCKET (WM_USER + 1) //��Ʈ��ũ �̺�Ʈ�� ������ ����� ���� ������ �޽���

enum PLAYER_COLOR
{
	WHITE,
	BLACK
};

struct CHESS_PIECE
{
	int x;
	int y;
	int piece_name;
	int piece_num;
};

class Network
{
private:
	WSADATA m_WsaData;
	SOCKET m_ServerSock;
	SOCKADDR_IN m_ServerAddr;
	HANDLE m_SendThread;
	HANDLE m_RecvThread;

	HWND m_hWnd;
	static bool m_player_connect;
	static bool m_player_turn;
	static int m_set_player_color;
	static int m_color_set_check;
	static bool m_recv_check;
	//// unsigned WINAPI�� static�� ���ش�
public:
	Network();

	static CHESS_PIECE m_piece;
	static bool m_player_done_check; // �������� ����üũ (���� ���Ҵ���)
	void Init_Network(HWND hWnd);
	static unsigned WINAPI Send(void *arg);
	static unsigned WINAPI Recv(void *arg);
	void Release_Network();

	inline int Get_Player_Turn()
	{
		return m_player_turn;
	}
	inline int Get_Player_Color()

	{
		return m_set_player_color;
	}

	~Network();
};


