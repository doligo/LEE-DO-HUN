#include "Game_Scene.h"

Game_Scene::Game_Scene()
{
	time = 0;
}

void Game_Scene::Init(HWND hWnd)
{

}

bool Game_Scene::Input(float fETime)
{
	return false;
}

void Game_Scene::Update(float fETime)
{
	time = fETime;
}

void Game_Scene::Draw(HDC hdc)
{

}

void Game_Scene::Release()
{

}

Game_Scene::~Game_Scene()
{
}
