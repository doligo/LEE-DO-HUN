#include "Game2_Scene.h"
#include "InputManager.h"
#include "ResoucesManager.h"
#include "UIManager.h"
#include "SceneManager.h"

Game2_Scene::Game2_Scene()
{
	time = 0;
}

void Game2_Scene::Init(HWND hWnd)
{

}

bool Game2_Scene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
		JEngine::SceneManager::GetInstance()->LoadScene(1);

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