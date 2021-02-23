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
	BLACK,
	WHITE
};

struct POINT_XY
{
	int x;
	int y;
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
	bool m_player_connect;
public:
	Network();

	void Init_Network(HWND hWnd);
	static unsigned WINAPI Send(void *arg);
	static unsigned WINAPI Recv(void *arg);

	~Network();
};

