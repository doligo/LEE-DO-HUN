#include "Select_Scene.h"
#include "InputManager.h"
#include "ResoucesManager.h"
#include "UIManager.h"
#include "SceneManager.h"

Select_Scene::Select_Scene()
{
	time = 0;
}

void Select_Scene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("GameSelect.bmp");

	JEngine::UIManager::GetInstance()->AddButton(320, 166, "OnSelect.bmp", std::bind(&Select_Scene::OnClick_Game, this));
	JEngine::UIManager::GetInstance()->AddButton(320, 249, "OnSelect.bmp", std::bind(&Select_Scene::OnClick_Game2, this));
}

bool Select_Scene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
		JEngine::SceneManager::GetInstance()->LoadScene(0);

	return false;
}

void Select_Scene::Update(float fETime)
{
	time = fETime;
}

void Select_Scene::Draw(HDC hdc)
{
	m_pBack->Draw(0, 0);
}

void Select_Scene::Release()
{

}

bool Select_Scene::OnClick_Game()
{
	JEngine::SceneManager::GetInstance()->LoadScene(2);
	return true;
}

bool Select_Scene::OnClick_Game2()
{
	JEngine::SceneManager::GetInstance()->LoadScene(3);
	return true;
}

Select_Scene::~Select_Scene()
{

}