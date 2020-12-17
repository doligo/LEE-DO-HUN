#include "Game2_Scene.h"

Game2_Scene::Game2_Scene()
{
	time = 0;
}

void Game2_Scene::Init(HWND hWnd)
{

}

bool Game2_Scene::Input(float fETime)
{
	return false;
}

void Game2_Scene::Update(float fETime)
{
	time = fETime;
}

void Game2_Scene::Draw(HDC hdc)
{

}

void Game2_Scene::Release()
{

}

Game2_Scene::~Game2_Scene()
{
}