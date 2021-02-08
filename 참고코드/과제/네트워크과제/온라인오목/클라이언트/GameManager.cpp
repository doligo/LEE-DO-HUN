#include "GameManager.h"



GameManager::GameManager()
{
	m_bPlayState = false;
	m_iTurn = 1;
	m_iHeight = HEIGHT;
	m_iWidth = WIDTH;
}

void GameManager::LobbyDraw()
{
	m_DrawManager.DrawMidText("★ 오 목 ★", m_iWidth, m_iHeight* 0.3f);
	m_DrawManager.DrawMidText("1.게임 시작", m_iWidth, m_iHeight* 0.4f);
	m_DrawManager.DrawMidText("2.옵션 설정", m_iWidth, m_iHeight* 0.5f);
	m_DrawManager.DrawMidText("3.게임 종료", m_iWidth, m_iHeight* 0.6f);
	m_DrawManager.BoxDraw(m_iWidth, m_iHeight* 0.7, m_iWidth / 2, 3);
	m_DrawManager.gotoxy(m_iWidth, m_iHeight* 0.7 + 1);
}


void GameManager::DrawPoint()
{
	m_DrawManager.Erase(m_Player.GetCursor().m_ix, m_Player.GetCursor().m_iy, m_iWidth, m_iHeight);
	m_Player.DrawStone(m_Player.GetCursor().m_ix, m_Player.GetCursor().m_iy);

}

void GameManager::InputInfoDraw()
{
	m_DrawManager.DrawMidText("====조작키====", m_iWidth, m_iHeight);
	m_DrawManager.DrawMidText("이동 : A,S,W,D 돌놓기 : ENTER", m_iWidth, m_iHeight+1);
	m_DrawManager.DrawMidText("무르기 : N 옵션 : P 종료 : ESC", m_iWidth, m_iHeight + 2);
}

void GameManager::CurPlayerInfoDraw()
{
	string Name = m_Player.GetName();
	int UndoCount = m_Player.GetUndo();
	string str = "Player Name : " + Name + " 무르기 : " + to_string(UndoCount) + "  ";
	m_DrawManager.DrawMidText(str, m_iWidth, m_iHeight + 3);
	m_DrawManager.DrawMidText("Turn : " + to_string(m_iTurn) + "  " , m_iWidth, m_iHeight + 4);
}

void GameManager::Input(SOCKET socket)
{
	SOCKET Socket = socket;
	PLAYER_INFO *recv_save_player_packet;
	char buf[BUF_SIZE + 28] = {};
	int value = 0;
	char ch = getch();
	Point Cursor;
	switch(ch)
	{
		case KEY_LEFT:
		case KEY_RIGHT:
		case KEY_UP:
		case KEY_DOWN:
			DrawPoint();
			m_Player.Move(ch, m_iWidth, m_iHeight);
			break;
		case KEY_ESC:
			m_bPlayState = false;
			break;
		case KEY_DROP:
			Cursor = m_Player.GetCursor();
			if(m_Player.CompareStone(Cursor.m_ix, Cursor.m_iy))
				break;
			m_Player.CreateStone();

			save_player_packet.player_stone = Cursor;

			if(m_Player.WinCheck(m_iWidth, m_iHeight))
			{
				m_bPlayState = false;
				m_DrawManager.DrawMidText(m_Player.GetName() + "팀 승리!!", m_iWidth, m_iHeight* 0.5f);
				getch();
				return;
			}
			m_iTurn++;
			CurPlayerInfoDraw();
			break;
		case KEY_UNDO:
			if(m_Player.GetUndo() > 0 && m_iTurn > 1)
			{
				m_Player.EraseCursor(m_iWidth,m_iHeight);
				m_Player.DownUndo();
				m_iTurn--;
				m_Player.Undo(m_iWidth, m_iHeight);
				CurPlayerInfoDraw();
			}
			break;
		case KEY_OPTION:
			Option();
			system("cls");
			m_DrawManager.Draw(m_iWidth, m_iHeight);
			InputInfoDraw();
			CurPlayerInfoDraw();
			m_Player.AllStoneDraw();
			break;
	}
}


void GameManager::SetName(string str,PLAYERTYPE type, int x, int y)
{
	m_Player.SetName(save_player_packet.player_name);
	m_Player.PlayerSet(m_iWidth, m_iHeight);
}

void GameManager::GameStart(SOCKET socket)
{
	SOCKET Socket = socket;
	PACKET_HEADER send_packet;
	PACKET_HEADER *recv_packet = NULL;
	PLAYER_INFO *recv_save_player_packet;
	int value = 0;
	char buf[BUF_SIZE + 20] = {};
	int tmp_player_color = 0;

	tmp_player_color = save_player_packet.player_color;
	send_packet.index = PLAYER_READY;
	send_packet.size = sizeof(send_packet);

	value = send(Socket, (char*)&send_packet, sizeof(send_packet), NULL);
	value = recv(Socket, buf, sizeof(buf), NULL);
	recv_save_player_packet = (PLAYER_INFO*)buf;

	save_player_packet.player_ready = recv_save_player_packet->player_ready;
	save_player_packet.player_stone.m_ix = 0;
	save_player_packet.player_stone.m_iy = 0;

	value = send(Socket, (char*)&save_player_packet, sizeof(save_player_packet), NULL);

	save_packet_header.index = PLAYER_READY;
	save_packet_header.size = sizeof(save_packet_header);

	while (save_packet_header.index != PLAYER_START)
	{
		value = recv(Socket, buf, sizeof(buf), NULL);
		recv_packet = (PACKET_HEADER*)buf;
		save_packet_header.index = recv_packet->index;

		send_packet.index = PLAYER_READY;
		send_packet.size = sizeof(send_packet);
		value = send(Socket, (char*)&send_packet, sizeof(send_packet), NULL);
	}

	if (save_packet_header.index == PLAYER_START)
	{
		system("cls");
		m_DrawManager.BoxDraw(0, 0, m_iWidth, m_iHeight);
		SetName("플레이어 이름", (PLAYERTYPE)tmp_player_color, m_iWidth, m_iHeight * 0.3f);
		system("cls");
		m_DrawManager.Draw(m_iWidth, m_iHeight);
		InputInfoDraw();
		CurPlayerInfoDraw();

		while (m_bPlayState)
		{
			if (save_player_packet.player_color == 0 && save_player_packet.turn_count % 2 == 1 || save_player_packet.player_color == 1 && save_player_packet.turn_count % 2 == 0)
			{
				m_Player.DrawCursor();
				Input(Socket);
			}
		}
	}
}

void GameManager::SetUndo()
{
	while(1)
	{
		system("cls");
		int Height, Width;
		if(m_bPlayState == false)
		{
			int Select;
			system("cls");
			m_DrawManager.BoxDraw(0, 0, m_iWidth, m_iHeight);
			m_DrawManager.DrawMidText("= Set Undo  =", m_iWidth, m_iHeight* 0.2f);
			m_DrawManager.DrawMidText("1.Set Undo Count", m_iWidth, m_iHeight* 0.3f);
			m_DrawManager.DrawMidText("2.Undo Off", m_iWidth, m_iHeight* 0.4f);
			m_DrawManager.DrawMidText("3.Return", m_iWidth, m_iHeight* 0.5f);
			m_DrawManager.DrawMidText("입력 : ", m_iWidth, m_iHeight* 0.6f);
			cin >> Select;
			switch(Select)
			{
				case 1:
					while(1)
					{
						system("cls");
						m_DrawManager.BoxDraw(0, 0, m_iWidth, m_iHeight);
						m_DrawManager.DrawMidText("무르기 횟수 입력(최대 10회) : ", m_iWidth, m_iHeight* 0.5f);
						cin >> Select;
						if(Select <= 10 && Select >= 0)
						{
							m_Player.SetUndo(Select);
							break;
						}
						m_DrawManager.DrawMidText("범위가 맞지 않습니다 ( 0 ~ 10 )", m_iWidth, m_iHeight* 0.6f);
						getch();
					}
					break;
				case 2:
					system("cls");
					m_DrawManager.BoxDraw(0, 0, m_iWidth, m_iHeight);
					m_DrawManager.DrawMidText("무르기 Off", m_iWidth, m_iHeight* 0.5f);
					m_Player.SetUndo(0);
					getch();
					break;
				case 3:
					return;
			}
		}
		else
		{
			system("cls");
			m_DrawManager.DrawMidText("접근 불가능", m_iWidth, m_iHeight* 0.4f);
			m_DrawManager.DrawMidText("(Game Play중)", m_iWidth, m_iHeight* 0.5f);
			m_DrawManager.gotoxy(0, m_iHeight);
			system("pause");
			return;
		}
	}
}

void GameManager::SetMapSize()
{
	while(1)
	{
		system("cls");
		int Height, Width;
		if(m_bPlayState == false)
		{
			m_DrawManager.BoxDraw(0, 0, m_iWidth, m_iHeight);
			m_DrawManager.DrawMidText("Width :", m_iWidth, m_iHeight* 0.4f);
			cin >> Width;
			m_DrawManager.DrawMidText("Height : ", m_iWidth, m_iHeight* 0.6f);
			cin >> Height;
			if(Width >= 20 && Width <= 90 && Height >= 20 && Height <= 45)
			{
				m_iWidth = Width;
				m_iHeight = Height;
				char buf[256];
				sprintf(buf, "mode con: lines=%d cols=%d", m_iHeight + 5, (m_iWidth * 2) + 1);
				system(buf);
				return;
			}
			else
			{
				system("cls");
				m_DrawManager.BoxDraw(0, 0, m_iWidth, m_iHeight);
				m_DrawManager.DrawMidText("변경 불가능", m_iWidth, m_iHeight* 0.4f);
				m_DrawManager.DrawMidText("(가로 : 20 ~ 90 , 세로 : 20 ~ 45)", m_iWidth, m_iHeight* 0.5f);
				m_DrawManager.gotoxy(0, m_iHeight);
				getch();
			}
		}
		else
		{
			system("cls");
			m_DrawManager.DrawMidText("접근 불가능", m_iWidth, m_iHeight* 0.4f);
			m_DrawManager.DrawMidText("(Game Play중)", m_iWidth, m_iHeight* 0.5f);
			m_DrawManager.gotoxy(0, m_iHeight);
			system("pause");
			return;
		}
	}
}


void GameManager::SetCursor()
{
	int Select;
	system("cls");
	m_DrawManager.BoxDraw(0, 0, m_iWidth, m_iHeight);
	m_DrawManager.DrawMidText("= Set Cursor =", m_iWidth, m_iHeight* 0.2f);
	m_DrawManager.DrawMidText("1.○,●", m_iWidth, m_iHeight* 0.3f);
	m_DrawManager.DrawMidText("2.♡,♥", m_iWidth, m_iHeight* 0.4f);
	m_DrawManager.DrawMidText("3.☞,☜", m_iWidth, m_iHeight* 0.5f);
	m_DrawManager.DrawMidText("4.①,②", m_iWidth, m_iHeight* 0.6f);
	m_DrawManager.DrawMidText("5.Return", m_iWidth, m_iHeight* 0.7f);
	m_DrawManager.DrawMidText("입력 : ", m_iWidth, m_iHeight* 0.8f);
	cin >> Select;
	switch(Select)
	{
		case 1:
			if (save_player_packet.player_color == 0)
				m_Player.SetCursorIcon("●");
			else if (save_player_packet.player_color == 1)
				m_Player.SetCursorIcon("○");
			system("pause");
			break;
		case 2:
			if (save_player_packet.player_color == 0)
				m_Player.SetCursorIcon("♥");
			else if (save_player_packet.player_color == 1)
				m_Player.SetCursorIcon("♡");
			system("pause");
			break;
		case 3:
			if (save_player_packet.player_color == 0)
				m_Player.SetCursorIcon("☜");
			else if (save_player_packet.player_color == 1)
				m_Player.SetCursorIcon("☞");
			system("pause");
			break;
		case 4:
			if (save_player_packet.player_color == 0)
				m_Player.SetCursorIcon("②");
			else if (save_player_packet.player_color == 1)
				m_Player.SetCursorIcon("①");
			system("pause");
			break;
		case 5:
			return;
	}
}


void GameManager::SetStone()
{
	int Select;
	system("cls");
	m_DrawManager.BoxDraw(0, 0, m_iWidth, m_iHeight);
	m_DrawManager.DrawMidText("= Set Cursor =", m_iWidth, m_iHeight* 0.2f);
	m_DrawManager.DrawMidText("1.○,●", m_iWidth, m_iHeight* 0.3f);
	m_DrawManager.DrawMidText("2.♡,♥", m_iWidth, m_iHeight* 0.4f);
	m_DrawManager.DrawMidText("3.☏,☎", m_iWidth, m_iHeight* 0.5f);
	m_DrawManager.DrawMidText("4.①,②", m_iWidth, m_iHeight* 0.6f);
	m_DrawManager.DrawMidText("5.Return", m_iWidth, m_iHeight* 0.7f);
	m_DrawManager.DrawMidText("입력 : ", m_iWidth, m_iHeight* 0.8f);
	cin >> Select;
	switch(Select)
	{
		case 1:
			if (save_player_packet.player_color == 0)
				m_Player.SetStoneIcon("●");
			else if (save_player_packet.player_color == 1)
				m_Player.SetStoneIcon("○");
			system("pause");
			break;
		case 2:
			if (save_player_packet.player_color == 0)
				m_Player.SetStoneIcon("♥");
			else if (save_player_packet.player_color == 1)
				m_Player.SetStoneIcon("♡");
			system("pause");
			break;
		case 3:
			if (save_player_packet.player_color == 0)
				m_Player.SetStoneIcon("☎");
			else if (save_player_packet.player_color == 1)
				m_Player.SetStoneIcon("☏");
			system("pause");
			break;
		case 4:
			if (save_player_packet.player_color == 0)
				m_Player.SetStoneIcon("②");
			else if (save_player_packet.player_color == 1)
				m_Player.SetStoneIcon("①");
			system("pause");
			break;
		case 5:
			return;
	}
}

void GameManager::Option()
{
	int Select;
	while(1)
	{
		m_DrawManager.BoxDraw(0, 0, m_iWidth, m_iHeight);
		m_DrawManager.DrawMidText("= Option =", m_iWidth, m_iHeight* 0.2f);
		m_DrawManager.DrawMidText("1.Map Size Set", m_iWidth, m_iHeight* 0.3f);
		m_DrawManager.DrawMidText("2.Cursor Custom", m_iWidth, m_iHeight* 0.4f);
		m_DrawManager.DrawMidText("3.Stone Custom", m_iWidth, m_iHeight* 0.5f);
		m_DrawManager.DrawMidText("4.Undo Count Set", m_iWidth, m_iHeight* 0.6f);
		m_DrawManager.DrawMidText("5.Return", m_iWidth, m_iHeight* 0.7f);
		m_DrawManager.DrawMidText("입력 : ", m_iWidth, m_iHeight* 0.8f);
		cin >> Select;
		switch(Select)
		{
			case OPTIONMENU_MAPSIZE:
				SetMapSize();
				break;
			case OPTIONMENU_CURSOR:
				SetCursor();
				break;
			case OPTIONMENU_STONE:
				SetStone();
				break;
			case OPTIONMENU_UNDO:
				SetUndo();
				break;
			case OPTIONMENU_RETURN:
				return;
		}

	}
}

void GameManager::GameMain()
{
	NetWork_Main(); // 실행시 소켓생성하고 스레드 할당해준다
}

void GameManager::Game_Menu_Main(SOCKET socket)
{
	SOCKET Socket = socket;

	if (save_player_packet.player_color == 0)
	{
		m_Player.SetCursorIcon(WHITETEAMICON);
		m_Player.SetStoneIcon(WHITETEAMICON);
	}
	else if (save_player_packet.player_color == 1)
	{
		m_Player.SetCursorIcon(BLACKTEAMICON);
		m_Player.SetStoneIcon(BLACKTEAMICON);
	}

	char buf_[256];
	sprintf(buf_, "mode con: lines=%d cols=%d", m_iHeight + 5, (m_iWidth * 2) + 1);
	system(buf_);
	while (1)
	{
		system("cls");
		m_DrawManager.Draw(m_iWidth, m_iHeight);
		LobbyDraw();
		int Select;
		cin >> Select;
		switch (Select)
		{
		case LOBBYMENU_START:
			m_bPlayState = true;
			m_iTurn = 1;
			GameStart(Socket);
			break;
		case LOBBYMENU_OPTION:
			Option();
			break;
		case LOBBYMENU_EXIT:
			return;
		}
	}
}

int GameManager::NetWork_Main() // 클라쪽 소켓메인
{
	int value = 0;
	char buf[BUF_SIZE] = {};

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		cout << "윈도우 소켓에러입니다" << endl;

	SOCKET hSock;
	hSock = socket(PF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serveradr;
	memset(&serveradr, 0, sizeof(serveradr));
	serveradr.sin_family = AF_INET;
	serveradr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveradr.sin_port = htons(9001);

	if (connect(hSock, (SOCKADDR*)&serveradr, sizeof(serveradr)) == SOCKET_ERROR)
		cout << "연결 오류입니다 (connect 오류)" << endl;

	HANDLE hThread;
	DWORD dwThreadID;

	value = recv(hSock, buf, sizeof(buf), NULL); // 인원이 가득찼는지 체크하는 리시브함수

	if (value == -1)
		return 0;
	else if (value == 20)
	{
		cout << "인원이 가득 찼습니다" << endl;
		system("pause");
		return 0;
	}
	else if (value == 8)
		hThread = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)Control_Thread(&hSock), (void*)&hSock, 0, (unsigned int*)&dwThreadID);

	closesocket(hSock);

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	WSACleanup();
	return 0;
}

unsigned WINAPI GameManager::Control_Thread(void *arg)
{
	SOCKET Socket = *((SOCKET*)arg);
	int value = 0;
	PACKET_HEADER send_packet;
	PACKET_HEADER *recv_packet;
	PLAYER_INFO send_player_packet;
	PLAYER_INFO *recv_player_packet;
	int len = 0;
	char buf[BUF_SIZE] = {};
	int trigger = false;
	// 클라쪽은 getpeername 할필요없다

	send_packet.index = PLAYER_WAIT;
	len = sizeof(send_packet);
	send_packet.size = len;

	len = sizeof(PLAYER_INFO);

	value = send(Socket, (char*)&send_player_packet, sizeof(send_player_packet), NULL);
	value = recv(Socket, buf, sizeof(buf), NULL);
	recv_player_packet = (PLAYER_INFO*)buf;

	save_player_packet.player_color = recv_player_packet->player_color;
	strcpy(save_player_packet.player_name, recv_player_packet->player_name);

	while (1)
	{
		value = send(Socket, (char*)&send_packet, sizeof(send_packet), 0);
		if (value == SOCKET_ERROR)
		{
			cout << "샌드 에러입니다" << endl;
			return 0;
		}
		else if (value == 0)
			break;

		value = recv(Socket, buf, sizeof(buf), NULL);
		recv_packet = (PACKET_HEADER*)buf;
		if (value == SOCKET_ERROR)
		{
			cout << "리시브 에러입니다" << endl;
			return 0;
		}
		else if (value == 0)
			break;
		else if (value == 4 && recv_packet->index == PLAYER_WAIT2)
		{
			send_packet.index = PLAYER_WAIT2;
			len = sizeof(send_packet);
			send_packet.size = len;
			if (trigger == false)
			{
				cout << "유저를 기다리는 중..." << endl;
				trigger = true;
			}
		}
		else if (value == 4 && recv_packet->index == PLAYER_WAIT3)
			Game_Menu_Main(Socket);

	}

	closesocket(Socket);

	return 0;
}

GameManager::~GameManager()
{
}
