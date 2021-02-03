#include "GameManager.h"



GameManager::GameManager()
{
	m_bPlayState = false;
	m_iTurn = 1;
	m_iHeight = HEIGHT;
	m_iWidth = WIDTH;
	m_Player[PLAYERTYPE_BLACK].SetCursorIcon(BLACKTEAMICON);
	m_Player[PLAYERTYPE_BLACK].SetStoneIcon(BLACKTEAMICON);
	m_Player[PLAYERTYPE_WHITE].SetCursorIcon(WHITETEAMICON);
	m_Player[PLAYERTYPE_WHITE].SetStoneIcon(WHITETEAMICON);
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
	m_DrawManager.Erase(m_Player[m_iTurn % 2].GetCursor().m_ix, m_Player[m_iTurn % 2].GetCursor().m_iy, m_iWidth, m_iHeight);
	m_Player[PLAYERTYPE_BLACK].DrawStone(m_Player[m_iTurn % 2].GetCursor().m_ix, m_Player[m_iTurn % 2].GetCursor().m_iy);
	m_Player[PLAYERTYPE_WHITE].DrawStone(m_Player[m_iTurn % 2].GetCursor().m_ix, m_Player[m_iTurn % 2].GetCursor().m_iy);

}

void GameManager::InputInfoDraw()
{
	m_DrawManager.DrawMidText("====조작키====", m_iWidth, m_iHeight);
	m_DrawManager.DrawMidText("이동 : A,S,W,D 돌놓기 : ENTER", m_iWidth, m_iHeight+1);
	m_DrawManager.DrawMidText("무르기 : N 옵션 : P 종료 : ESC", m_iWidth, m_iHeight + 2);
}

void GameManager::CurPlayerInfoDraw()
{
	string Name = m_Player[m_iTurn % 2].GetName();
	int UndoCount = m_Player[m_iTurn % 2].GetUndo();
	string str = "Player Name : " + Name + "       무르기 : " + to_string(UndoCount) + "  ";
	m_DrawManager.DrawMidText(str, m_iWidth, m_iHeight + 3);
	m_DrawManager.DrawMidText("Turn : " + to_string(m_iTurn) + "  " , m_iWidth, m_iHeight + 4);
}

void GameManager::Input()
{
	char ch = getch();
	Point Cursor;
	switch(ch)
	{
		case KEY_LEFT:
		case KEY_RIGHT:
		case KEY_UP:
		case KEY_DOWN:
			DrawPoint();
			m_Player[m_iTurn % 2].Move(ch, m_iWidth, m_iHeight);
			break;
		case KEY_ESC:
			m_bPlayState = false;
			break;
		case KEY_DROP:
			Cursor = m_Player[m_iTurn % 2].GetCursor();
			if(m_Player[PLAYERTYPE_BLACK].CompareStone(Cursor.m_ix, Cursor.m_iy) || m_Player[PLAYERTYPE_WHITE].CompareStone(Cursor.m_ix, Cursor.m_iy))
				break;
			m_Player[m_iTurn % 2].CreateStone();
			if(m_Player[m_iTurn % 2].WinCheck(m_iWidth, m_iHeight))
			{
				m_bPlayState = false;
				m_DrawManager.DrawMidText(m_Player[m_iTurn % 2].GetName() + "팀 승리!!", m_iWidth, m_iHeight* 0.5f);
				getch();
				return;
			}
			m_iTurn++;
			CurPlayerInfoDraw();
			break;
		case KEY_UNDO:
			if(m_Player[m_iTurn % 2].GetUndo() > 0 && m_iTurn > 1)
			{
				m_Player[m_iTurn % 2].EraseCursor(m_iWidth,m_iHeight);
				m_Player[m_iTurn % 2].DownUndo();
				m_iTurn--;
				m_Player[m_iTurn % 2].Undo(m_iWidth, m_iHeight);
				CurPlayerInfoDraw();
			}
			break;
		case KEY_OPTION:
			Option();
			system("cls");
			m_DrawManager.Draw(m_iWidth, m_iHeight);
			InputInfoDraw();
			CurPlayerInfoDraw();
			m_Player[PLAYERTYPE_BLACK].AllStoneDraw();
			m_Player[PLAYERTYPE_WHITE].AllStoneDraw();
			break;
	}
}


void GameManager::SetName(string str,PLAYERTYPE type, int x, int y)
{
	m_DrawManager.DrawMidText(str, x,y);
	m_DrawManager.DrawMidText("입력 : ", x, y + 1);
	m_Player[type].SetName();
	m_Player[type].PlayerSet(m_iWidth, m_iHeight);
}

void GameManager::GameStart()
{
	system("cls");
	m_DrawManager.BoxDraw(0, 0, m_iWidth, m_iHeight);
	SetName("P1 이름", PLAYERTYPE_BLACK, m_iWidth, m_iHeight * 0.3f);
	SetName("P2 이름", PLAYERTYPE_WHITE, m_iWidth, m_iHeight * 0.5f);
	system("cls");
	m_DrawManager.Draw(m_iWidth, m_iHeight); 
	InputInfoDraw();
	CurPlayerInfoDraw();
	while(m_bPlayState)
	{
		m_Player[m_iTurn % 2].DrawCursor();
		Input();
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
							m_Player[PLAYERTYPE_BLACK].SetUndo(Select);
							m_Player[PLAYERTYPE_WHITE].SetUndo(Select);
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
					m_Player[PLAYERTYPE_BLACK].SetUndo(0);
					m_Player[PLAYERTYPE_WHITE].SetUndo(0);
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
			m_Player[PLAYERTYPE_BLACK].SetCursorIcon("○");
			m_Player[PLAYERTYPE_WHITE].SetCursorIcon("●");
			system("pause");
			break;
		case 2:
			m_Player[PLAYERTYPE_BLACK].SetCursorIcon("♡");
			m_Player[PLAYERTYPE_WHITE].SetCursorIcon("♥");
			system("pause");
			break;
		case 3:
			m_Player[PLAYERTYPE_BLACK].SetCursorIcon("☞");
			m_Player[PLAYERTYPE_WHITE].SetCursorIcon("☜");
			system("pause");
			break;
		case 4:
			m_Player[PLAYERTYPE_BLACK].SetCursorIcon("①");
			m_Player[PLAYERTYPE_WHITE].SetCursorIcon("②");
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
			m_Player[PLAYERTYPE_BLACK].SetStoneIcon("○");
			m_Player[PLAYERTYPE_WHITE].SetStoneIcon("●");
			system("pause");
			break;
		case 2:
			m_Player[PLAYERTYPE_BLACK].SetStoneIcon("♡");
			m_Player[PLAYERTYPE_WHITE].SetStoneIcon("♥");
			system("pause");
			break;
		case 3:
			m_Player[PLAYERTYPE_BLACK].SetStoneIcon("☏");
			m_Player[PLAYERTYPE_WHITE].SetStoneIcon("☎");
			system("pause");
			break;
		case 4:
			m_Player[PLAYERTYPE_BLACK].SetStoneIcon("①");
			m_Player[PLAYERTYPE_WHITE].SetStoneIcon("②");
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

	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", m_iHeight+5, (m_iWidth*2)+1);
	system(buf);
	while(1)
	{
		system("cls");
		m_DrawManager.Draw(m_iWidth, m_iHeight);
		LobbyDraw();
		int Select;
		cin >> Select;
		switch(Select)
		{
			case LOBBYMENU_START:
				m_bPlayState = true;
				m_iTurn = 1;
				GameStart();
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
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		cout << "윈도우 소켓에러입니다" << endl;

	SOCKET hSock;
	hSock = socket(PF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN c_serveradr;
	memset(&c_serveradr, 0, sizeof(c_serveradr));
	c_serveradr.sin_family = AF_INET;
	c_serveradr.sin_addr.s_addr = inet_addr("127.0.0.1");
	c_serveradr.sin_port = htons(9001);

	if (connect(hSock, (SOCKADDR*)&c_serveradr, sizeof(c_serveradr)) == SOCKET_ERROR)
		cout << "연결 오류입니다 (connect 오류)" << endl;

	HANDLE hThread;
	DWORD dwThreadID;

	hThread = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)Control_Thread(&hSock), (void*)&hSock, 0, (unsigned int*)&dwThreadID);

	return 0;
}

unsigned WINAPI GameManager::Control_Thread(void *arg)
{
	SOCKET Socket = *((SOCKET*)arg);



	return 0;
}

GameManager::~GameManager()
{
}
