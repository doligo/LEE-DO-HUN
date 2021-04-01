#pragma once
#include <windows.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <process.h> // _beginthreadex �������ؼ�
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
	int Player_Pos; // ���ǿ��� �������� ��ġ
	char Player_Chat[50]; // ä�ó���
	int Player_Ingame_Num; // �濡 ���� ����
	bool Player_Update; // ������� �ִ��� üũ
	bool Player_Connect; // ����üũ��
	int Player_Num; // ���Ӽ���
	int Player_Checking; // ó�� ���ǿ� �������� ������ üũ�ϱ����� ��ȸ�� ����
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
	static Player_Info Recv_Player_info[MAX_PLAYER]; // ������÷��̾� ����
	static int m_player_wait_room;
	static bool m_player_first_send;

	~NetWork();
};

