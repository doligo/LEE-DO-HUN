#include "Game_Scene.h"
#include "InputManager.h"

Game_Scene::Game_Scene()
{
	time = 0;
}

void Game_Scene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_UP);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_DOWN);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);


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
