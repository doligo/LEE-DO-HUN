#include "Game2_Scene.h"
#include "InputManager.h"
#include "ResoucesManager.h"
#include "UIManager.h"
#include "SceneManager.h"

Game2_Scene::Game2_Scene()
{
}

void Game2_Scene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_UP);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_DOWN);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("FlightGameBack.bmp");
	m_pShow_Time = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperTimeBar.bmp");
	m_pShow_Fever[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("Fever1.bmp");
	m_pShow_Fever[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("Fever2.bmp");
	m_pShow_Fever[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("Fever3.bmp");
	m_pFlight = JEngine::ResoucesManager::GetInstance()->GetBitmap("FlightGameFlight.bmp");

	/*
	JEngine::RECT m_pMovable_Rt;
	JEngine::RECT m_pFlight_Rt;
	JEngine::POINT m_pFlight_Pt; 세팅하기, 마우스 없애기
	*/

	time = 0;
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
	m_pBack->Draw(0, 0);
	m_pFlight->Draw(JEngine::InputManager::GetInstance()->GetMousePoint());
}

void Game2_Scene::Release()
{
	
}

Game2_Scene::~Game2_Scene()
{
}