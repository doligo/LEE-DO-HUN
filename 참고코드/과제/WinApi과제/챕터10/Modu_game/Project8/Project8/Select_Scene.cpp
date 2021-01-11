#include "Select_Scene.h"
#include "InputManager.h"
#include "ResoucesManager.h"
#include "UIManager.h"
#include "SceneManager.h"

Select_Scene::Select_Scene()
{

}

void Select_Scene::Init(HWND hWnd)
{
	ifstream Load;
	ofstream Save;
	int count = 0;
	char buf[256];

	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("GameSelect.bmp");

	JEngine::UIManager::GetInstance()->AddButton(320, 166, "OnSelect.bmp", std::bind(&Select_Scene::OnClick_Game, this));
	JEngine::UIManager::GetInstance()->AddButton(320, 249, "OnSelect.bmp", std::bind(&Select_Scene::OnClick_Game2, this));
	for (int i = 0; i < 2; i++)
		m_pShow_Rank[i] = new JEngine::Label();

	time = 0;

	for (int i = 0; i < 2; i++)
		rank[i] = new Show_Top_Rank;

	for (int i = 0; i < 2; i++)
	{
		sprintf_s(buf, "Rank%d.txt", i + 1);

		Load.open(buf);
		if (!Load) // 파일없으면 생성
		{
			Save.open(buf, ios::app);
			Save.close();
		}
		else // 불러오기
		{
			if (Load.eof() == TRUE)
			{
				rank[count]->rank = 1;
				rank[count]->score = 0;
			}
			else
			{
				Load >> rank[count]->rank;
				Load >> rank[count]->score;
			}
			count++;
		}
		Load.close();
	}

	Set_Show_Rank();
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
	for (int i = 0; i < 2; i++)
		m_pShow_Rank[i]->Draw();
}

void Select_Scene::Release()
{

}

void Select_Scene::Set_Show_Rank()
{
	int num = 0;
	int tmp_y = 200;
	char buf[256] = {};

	while (num != 2)
	{
		if (rank[num]->score <= 0)
			rank[num]->score = 0;

		sprintf_s(buf, "최고점수 : %d", rank[num]->score);
		m_pShow_Rank[num]->Init(buf, 120, tmp_y, DT_CENTER);
		num++;
		tmp_y += 80;
	}
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
	for (int i = 0; i < 2; i++)
	{
		if (rank[i] != NULL)
			delete rank[i];
	}
}