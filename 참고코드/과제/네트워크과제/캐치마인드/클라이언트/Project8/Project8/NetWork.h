#pragma once
#include <windows.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <process.h> // _beginthreadex 쓰기위해서
#include <iostream>
using namespace std;

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

	~NetWork();
};

