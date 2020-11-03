#include <windows.h>
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#pragma once
class GameSystem
{
private:
	static GameSystem *game_system;
public:

	GameSystem();

	static GameSystem *GetInstane()
	{
		if (game_system == NULL)
			game_system = new GameSystem();
		return game_system;
	}

	void Init();

	~GameSystem();
};

