#include "GameManager.h"



GameManager::GameManager()
{
	m_bPlayState = false;
	m_iTurn = 1;
	m_iHeight = HEIGHT;
	m_iWidth = WIDTH;
	game_exit = false;
}

void GameManager::LobbyDraw()
{
	m_DrawManager.DrawMidText("�� �� �� ��", m_iWidth, m_iHeight* 0.3f);
	m_DrawManager.DrawMidText("1.���� ����", m_iWidth, m_iHeight* 0.4f);
	m_DrawManager.DrawMidText("2.�ɼ� ����", m_iWidth, m_iHeight* 0.5f);
	m_DrawManager.DrawMidText("3.���� ����", m_iWidth, m_iHeight* 0.6f);
	m_DrawManager.BoxDraw(m_iWidth, m_iHeight* 0.7, m_iWidth / 2, 3);
	m_DrawManager.gotoxy(m_iWidth, m_iHeight* 0.7 + 1);
}


void GameManager::DrawPoint()
{
	m_DrawManager.Erase(m_Player.GetCursor().m_ix, m_Player.GetCursor().m_iy, m_iWidth, m_iHeight);
	m_Player.DrawStone(m_Player.GetCursor().m_ix, m_Player.GetCursor().m_iy);
	m_Player.AllStoneDraw();
}

void GameManager::InputInfoDraw()
{
	m_DrawManager.DrawMidText("====����Ű====", m_iWidth, m_iHeight);
	m_DrawManager.DrawMidText("�̵� : A,S,W,D ������ : ENTER", m_iWidth, m_iHeight+1);
}

void GameManager::CurPlayerInfoDraw()
{
	string Name = m_Player.GetName();
	int UndoCount = m_Player.GetUndo();
	string str = "Player Name : " + Name;
	m_DrawManager.DrawMidText(str, m_iWidth, m_iHeight + 3);
	m_DrawManager.DrawMidText("Turn : " + to_string(m_iTurn) + "  " , m_iWidth, m_iHeight + 4);
}

void GameManager::Input(SOCKET socket)
{
	SOCKET Socket = socket;
	PLAYER_INFO *recv_save_player_packet = NULL;
	PACKET_HEADER *recv_packet = NULL;
	char buf[BUF_SIZE + 20] = {};
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
		case KEY_DROP:
			Cursor = m_Player.GetCursor();
			if (m_Player.CompareStone(2, Cursor.m_ix, Cursor.m_iy))
				break;
			m_Player.CreateStone();

			save_player_packet.player_stone = Cursor;

			if (m_Player.WinCheck(m_iWidth, m_iHeight))
			{
				m_bPlayState = false;
				m_DrawManager.DrawMidText("�¸��Ͽ����ϴ�!!", m_iWidth, m_iHeight* 0.5f);

				save_packet_header.index = PLAYER_GAME_OVER;
				value = send(Socket, (char*)&save_packet_header, sizeof(save_packet_header), NULL);
				value = send(Socket, (char*)&save_player_packet, sizeof(save_player_packet), NULL);
				m_Player.PlayerSet(m_iWidth, m_iHeight);
				getch();
				return;
			}

			m_iTurn++;
			CurPlayerInfoDraw();

			value = send(Socket, (char*)&save_packet_header, sizeof(save_packet_header), NULL);
			value = recv(Socket, buf, sizeof(buf), NULL);
			recv_packet = (PACKET_HEADER*)buf;
			save_packet_header.index = recv_packet->index;

			save_player_packet.player_stone.m_ix = Cursor.m_ix;
			save_player_packet.player_stone.m_iy = Cursor.m_iy;

			value = send(Socket, (char*)&save_player_packet, sizeof(save_player_packet), NULL);

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
	save_packet_header.index = PLAYER_READY;
	save_packet_header.size = sizeof(save_packet_header);

	value = sizeof(PLAYER_INFO);

	value = send(Socket, (char*)&save_packet_header, sizeof(save_packet_header), NULL);
	value = recv(Socket, buf, sizeof(buf), NULL);
	recv_save_player_packet = (PLAYER_INFO*)buf;

	save_player_packet.player_ready = recv_save_player_packet->player_ready;
	save_player_packet.player_stone.m_ix = 0;
	save_player_packet.player_stone.m_iy = 0;
	save_player_packet.turn_count = 1;

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
		SetName("�÷��̾� �̸�", (PLAYERTYPE)tmp_player_color, m_iWidth, m_iHeight * 0.3f);
		system("cls");
		m_DrawManager.Draw(m_iWidth, m_iHeight);
		InputInfoDraw();
		CurPlayerInfoDraw();

		if (save_player_packet.player_color == 1)
			save_packet_header.index = PLAYER_TURN;

		while (m_bPlayState)
		{
			if (save_packet_header.index == PLAYER_TURN)
			{
				m_Player.DrawCursor();
				Input(Socket);
			}
			else if (save_packet_header.index == PLAYER_START)
			{
				value = send(Socket, (char*)&save_packet_header, sizeof(save_packet_header), NULL);
				value = recv(Socket, buf, sizeof(buf), NULL);
				recv_packet = (PACKET_HEADER*)buf;
				save_packet_header.index = recv_packet->index;

				if (save_packet_header.index == PLAYER_TURN)
				{
					value = send(Socket, (char*)&save_player_packet, sizeof(save_player_packet), NULL);
					value = recv(Socket, buf, sizeof(buf), NULL);
					recv_save_player_packet = (PLAYER_INFO*)buf;
					tmp_save_player_packet.player_stone = recv_save_player_packet->player_stone;

					m_Player.SetCurosr_Enemy(tmp_save_player_packet.player_stone.m_ix, tmp_save_player_packet.player_stone.m_iy);
					m_Player.CreateStone_Enemy();
				}
				else if (save_packet_header.index == PLAYER_GAME_OVER)
				{
					value = send(Socket, (char*)&save_player_packet, sizeof(save_player_packet), NULL);
					value = recv(Socket, buf, sizeof(buf), NULL);
					recv_save_player_packet = (PLAYER_INFO*)buf;
					tmp_save_player_packet.player_stone = recv_save_player_packet->player_stone;

					m_Player.SetCurosr_Enemy(tmp_save_player_packet.player_stone.m_ix, tmp_save_player_packet.player_stone.m_iy);
					m_Player.CreateStone_Enemy();

					m_bPlayState = false;
					m_DrawManager.DrawMidText("�й� �Ͽ����ϴ٤Ф�", m_iWidth, m_iHeight* 0.5f);
					m_Player.PlayerSet(m_iWidth, m_iHeight);
					getch();
				}
			}
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
				m_DrawManager.DrawMidText("���� �Ұ���", m_iWidth, m_iHeight* 0.4f);
				m_DrawManager.DrawMidText("(���� : 20 ~ 90 , ���� : 20 ~ 45)", m_iWidth, m_iHeight* 0.5f);
				m_DrawManager.gotoxy(0, m_iHeight);
				getch();
			}
		}
		else
		{
			system("cls");
			m_DrawManager.DrawMidText("���� �Ұ���", m_iWidth, m_iHeight* 0.4f);
			m_DrawManager.DrawMidText("(Game Play��)", m_iWidth, m_iHeight* 0.5f);
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
	m_DrawManager.DrawMidText("1.��,��", m_iWidth, m_iHeight* 0.3f);
	m_DrawManager.DrawMidText("2.��,��", m_iWidth, m_iHeight* 0.4f);
	m_DrawManager.DrawMidText("3.��,��", m_iWidth, m_iHeight* 0.5f);
	m_DrawManager.DrawMidText("4.��,��", m_iWidth, m_iHeight* 0.6f);
	m_DrawManager.DrawMidText("5.Return", m_iWidth, m_iHeight* 0.7f);
	m_DrawManager.DrawMidText("�Է� : ", m_iWidth, m_iHeight* 0.8f);
	cin >> Select;
	switch(Select)
	{
		case 1:
			if (save_player_packet.player_color == 0)
				m_Player.SetCursorIcon("��");
			else if (save_player_packet.player_color == 1)
				m_Player.SetCursorIcon("��");
			system("pause");
			break;
		case 2:
			if (save_player_packet.player_color == 0)
				m_Player.SetCursorIcon("��");
			else if (save_player_packet.player_color == 1)
				m_Player.SetCursorIcon("��");
			system("pause");
			break;
		case 3:
			if (save_player_packet.player_color == 0)
				m_Player.SetCursorIcon("��");
			else if (save_player_packet.player_color == 1)
				m_Player.SetCursorIcon("��");
			system("pause");
			break;
		case 4:
			if (save_player_packet.player_color == 0)
				m_Player.SetCursorIcon("��");
			else if (save_player_packet.player_color == 1)
				m_Player.SetCursorIcon("��");
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
		m_DrawManager.DrawMidText("3.Return", m_iWidth, m_iHeight* 0.5f);
		m_DrawManager.DrawMidText("�Է� : ", m_iWidth, m_iHeight* 0.6f);
		cin >> Select;
		switch(Select)
		{
			case OPTIONMENU_MAPSIZE:
				SetMapSize();
				break;
			case OPTIONMENU_CURSOR:
				SetCursor();
				break;
			case OPTIONMENU_RETURN:
				return;
		}

	}
}

void GameManager::GameMain()
{
	NetWork_Main(); // ����� ���ϻ����ϰ� ������ �Ҵ����ش�
}

void GameManager::Game_Menu_Main(SOCKET socket)
{
	SOCKET Socket = socket;
	int value = 0;
	char buf2[BUF_SIZE + 20] = {};
	PACKET_HEADER *recv_packet;

	if (save_player_packet.player_color == 0)
	{
		m_Player.SetCursorIcon(WHITETEAMICON);
		m_Player.SetStoneIcon(WHITETEAMICON);
		m_Player.SetStoneIcon_Enemy("��");
	}
	else if (save_player_packet.player_color == 1)
	{
		m_Player.SetCursorIcon(BLACKTEAMICON);
		m_Player.SetStoneIcon(BLACKTEAMICON);
		m_Player.SetStoneIcon_Enemy("��");
	}

	char buf_[256];
	sprintf(buf_, "mode con: lines=%d cols=%d", m_iHeight + 5, (m_iWidth * 2) + 1);
	system(buf_);
	while (1)
	{
		if (save_packet_header.index == PLAYER_GAME_OVER)
		{
			save_packet_header.index = PLAYER_REGAME;
			value = send(Socket, (char*)&save_packet_header, sizeof(save_packet_header), NULL);
		}

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
			game_exit = true;
			return;
		}
	}
}

int GameManager::NetWork_Main() // Ŭ���� ���ϸ���
{
	int value = 0;
	char buf[BUF_SIZE + 20] = {};

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		cout << "������ ���Ͽ����Դϴ�" << endl;

	SOCKET hSock;
	hSock = socket(PF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serveradr;
	memset(&serveradr, 0, sizeof(serveradr));
	serveradr.sin_family = AF_INET;
	serveradr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveradr.sin_port = htons(9001);

	if (connect(hSock, (SOCKADDR*)&serveradr, sizeof(serveradr)) == SOCKET_ERROR)
		cout << "���� �����Դϴ� (connect ����)" << endl;

	HANDLE hThread;
	DWORD dwThreadID;

	value = recv(hSock, buf, sizeof(buf), NULL); // �ο��� ����á���� üũ�ϴ� ���ú��Լ�

	if (value == -1)
		return 0;
	else if (value == 20)
	{
		cout << "�ο��� ���� á���ϴ�" << endl;
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
	char buf[BUF_SIZE + 20] = {};
	int trigger = false;
	// Ŭ������ getpeername ���ʿ����

	send_packet.index = PLAYER_WAIT;
	len = sizeof(send_packet);
	send_packet.size = len;

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
			cout << "���� �����Դϴ�" << endl;
			return 0;
		}
		else if (value == 0)
			break;

		value = recv(Socket, buf, sizeof(buf), NULL);
		recv_packet = (PACKET_HEADER*)buf;
		if (value == SOCKET_ERROR)
		{
			cout << "���ú� �����Դϴ�" << endl;
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
				cout << "������ ��ٸ��� ��..." << endl;
				trigger = true;
			}
		}
		else if (value == 4 && recv_packet->index == PLAYER_WAIT3)
		{
			if (game_exit == true)
				break;
			else
				Game_Menu_Main(Socket);
		}
	}

	closesocket(Socket);

	return 0;
}

GameManager::~GameManager()
{
}
