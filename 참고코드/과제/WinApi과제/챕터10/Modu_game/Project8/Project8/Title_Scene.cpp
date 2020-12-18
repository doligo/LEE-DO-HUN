#include "Title_Scene.h"
#include "InputManager.h"
#include "ResoucesManager.h"
#include "UIManager.h"
#include "BitMap.h"
#include "SceneManager.h"

Title_Scene::Title_Scene()
{
	m_p_title_x = 414;
	m_p_title_y = 642;
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

	m_pTitle = JEngine::ResoucesManager::GetInstance()->GetBitmap("Title.bmp");

	JEngine::UIManager::GetInstance()->AddButton(180, 500, "OnSelect.bmp", std::bind(&Title_Scene::OnClick_Select, this));

	//m_pTitle->SetAnchor(JEngine::ANCHOR_RB); // 어디다 쓰이는지 알아보기
}

bool Title_Scene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
		return true;

	return false;
}

void Title_Scene::Update(float fETime)
{

}

void Title_Scene::Draw(HDC hdc)
{
	//m_pTitle->Draw((int)m_p_title_x, (int)m_p_title_y);
	m_pTitle->Draw(0,0);
}

void Title_Scene::Release()
{

}

bool Title_Scene::OnClick_Select()
{
	JEngine::SceneManager::GetInstance()->LoadScene(1);
	return true;
}

Title_Scene::~Title_Scene()
{
}
