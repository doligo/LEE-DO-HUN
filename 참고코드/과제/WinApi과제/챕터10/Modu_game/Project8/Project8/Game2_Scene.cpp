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
	RECT tmp_clip;
	POINT pt1;

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

	m_pMovable_Rt.Set(0, 80, 360, 570); // left, top, right, bottom - 사용할때 다시수정 or 안쓰면 삭제하기
	GetClientRect(hWnd, &tmp_clip);
	
	pt1.x = tmp_clip.left;
	pt1.y = tmp_clip.top;

	ClientToScreen(hWnd, &pt1);

	tmp_clip.left = pt1.x;
	tmp_clip.top = pt1.y + 90;
	tmp_clip.right = pt1.x + 348;
	tmp_clip.bottom = pt1.y + 544;

	ClipCursor(&tmp_clip);

	time = 0;
}

bool Game2_Scene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
	{
		ShowCursor(true); // 커서 온
		ClipCursor(NULL);
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
	m_pFlight->Draw(m_pFlight_Pt);
}

void Game2_Scene::Release()
{
	
}

void Game2_Scene::Set_Flight()
{

	m_pFlight_Pt = JEngine::InputManager::GetInstance()->GetMousePoint();
	m_pFlight_Rt.Set(m_pFlight_Pt.x, m_pFlight_Pt.y, m_pFlight_Pt.x + 10, m_pFlight_Pt.y + 10);

}

Game2_Scene::~Game2_Scene()
{
}