#pragma once
#include <windows.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <process.h> // _beginthreadex 쓰기위해서
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
	int Player_Pos;
	char Player_Chat[50];
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

	static Player_Info Player_info;

	~NetWork();
};

