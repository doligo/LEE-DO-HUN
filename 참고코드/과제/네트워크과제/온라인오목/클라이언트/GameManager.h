#pragma once
#include"Mecro.h"
#include"MapDraw.h"
#include"Player.h"
#include <winsock2.h>
#include <stdlib.h>

using namespace std;

#define BLACKTEAMICON "○"
#define WHITETEAMICON "●"
#define BUF_SIZE 512

enum OPTIONMENU
{
	OPTIONMENU_MAPSIZE = 1,
	OPTIONMENU_CURSOR,
	OPTIONMENU_STONE,
	OPTIONMENU_UNDO,
	OPTIONMENU_RETURN
};

enum LOBBYMENU
{
	LOBBYMENU_START = 1,
	LOBBYMENU_OPTION,
	LOBBYMENU_EXIT
};

enum PLAYERTYPE
{
	PLAYERTYPE_WHITE,
	PLAYERTYPE_BLACK,
	PLAYERTYPE_END
};

enum GAME_STATUS
{
	PLAYER_WAIT,
	PLAYER_WAIT2,
	PLAYER_WAIT3,
	PLAYER_READY,
	PLAYER_START,
	PLAYER_TURN
};

#pragma pack(push, 1)
struct PACKET_HEADER
{
	WORD index;
	WORD size;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PLAYER_INFO
{
	int player_color;
	char player_name[BUF_SIZE];
	int player_ready = 0;
	Point player_stone;
	int turn_count = 1;
};
#pragma pack(pop)

class GameManager
{
private:
	int m_iTurn;
	int m_iWidth;
	int m_iHeight;
	bool m_bPlayState;
	MapDraw m_DrawManager;
	Player m_Player;
	Player m_Enemy;
public:
	void SetMapSize();
	void CurPlayerInfoDraw();
	void InputInfoDraw();
	void SetName(string str,PLAYERTYPE type, int x, int y);
	void DrawPoint();
	void Input(SOCKET socket);
	void GameStart(SOCKET socket);
	void SetUndo();
	void Option();
	void SetCursor();
	void SetStone();
	void LobbyDraw();
	void GameMain();
	int NetWork_Main(); // 소켓메인
	unsigned WINAPI Control_Thread(void *arg);
	void Game_Menu_Main(SOCKET socket);
	PLAYER_INFO save_player_packet;
	PACKET_HEADER save_packet_header;
	GameManager();
	~GameManager();
};

