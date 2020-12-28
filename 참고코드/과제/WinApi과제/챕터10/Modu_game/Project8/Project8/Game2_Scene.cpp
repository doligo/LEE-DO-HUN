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

	ShowCursor(false); // 커서 오프

	m_pMovable_Rt.Set(0, 80, 345, 550); // left, top, right, bottom

	//ClipCursor(&tmp); 마우스가두기용

	time = 0;
	Draw_Check = true;
}

bool Game2_Scene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
	{
		ShowCursor(true); // 커서 온
		JEngine::SceneManager::GetInstance()->LoadScene(1);
	}

	return false;
}

void Game2_Scene::Update(float fETime)
{
	time = fETime;
	Set_Flight();
}

void Game2_Scene::Draw(HDC hdc)
{
	m_pBack->Draw(0, 0);
	if (Draw_Check == true)
		m_pFlight->Draw(m_pFlight_Pt);
}

void Game2_Scene::Release()
{
	
}

void Game2_Scene::Set_Flight()
{

	pre_pt = m_pFlight_Pt;

	m_pFlight_Pt = JEngine::InputManager::GetInstance()->GetMousePoint();
	m_pFlight_Rt.Set(m_pFlight_Pt.x, m_pFlight_Pt.y, m_pFlight_Pt.x + 10, m_pFlight_Pt.y + 10);

	if (m_pMovable_Rt.isCollision(m_pFlight_Rt))
		Draw_Check = true;
	else
		Draw_Check = false;


	/*
	if (m_pMovable_Rt.isPtin(m_pFlight_Pt))
	{
		m_pFlight_Rt.Set(m_pFlight_Pt.x, m_pFlight_Pt.y, m_pFlight_Pt.x + 15, m_pFlight_Pt.y + 15);
		Draw_Check = true;
	}
	else
	{
		m_pFlight_Pt = pre_pt;
		m_pFlight_Rt.Set(m_pFlight_Pt.x, m_pFlight_Pt.y, m_pFlight_Pt.x + 15, m_pFlight_Pt.y + 15);
		Draw_Check = false;
	}
	*/
	// 비행기의 영역을 그린후에 나가면 안그리게 체크한다
}

Game2_Scene::~Game2_Scene()
{
}