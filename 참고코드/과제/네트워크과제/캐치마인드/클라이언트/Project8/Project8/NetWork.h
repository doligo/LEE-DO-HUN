#pragma once
#include <windows.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <process.h> // _beginthreadex �������ؼ�
#include <iostream>
using namespace std;

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
	static Player_Info Recv_Player_info; // ������÷��̾� ���� (�ϴ� 1:1 ��Ȳ��)
	static int m_player_wait_room;
	static bool m_player_first_send;
	static bool m_player_first_recv;

	~NetWork();
};

