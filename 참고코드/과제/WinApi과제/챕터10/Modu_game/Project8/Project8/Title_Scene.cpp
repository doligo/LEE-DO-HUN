#include "Title_Scene.h"
#include "InputManager.h"
#include "ResoucesManager.h"
#include "UIManager.h"

Title_Scene::Title_Scene()
{
	m_p_title_x = 1024;
	m_p_title_y = 768;
	m_p_speed_x = 200;
}

void Title_Scene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("GameSelect.bmp");
	m_pTitle = JEngine::ResoucesManager::GetInstance()->GetBitmap("Title.bmp");

	JEngine::UIManager::GetInstance()->AddButton(180, 490, "OnSelect.bmp", std::bind(&Title_Scene::OnClick, this));
	m_pTitle->SetAnchor(JEngine::ANCHOR_RB); // 찾아보기
}

bool Title_Scene::Input(float fETime)
{

	return false;
}

void Title_Scene::Update(float fETime)
{

}

void Title_Scene::Draw(HDC hdc)
{
	m_pBack->DrawBitblt(0, 0);
	m_pTitle->Draw((int)m_p_title_x, (int)m_p_title_y);
}

void Title_Scene::Release()
{

}

bool Title_Scene::OnClick()
{
	return true;
}

Title_Scene::~Title_Scene()
{
}
