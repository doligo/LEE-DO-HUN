#include "Game_Scene.h"
#include "InputManager.h"
#include "ResoucesManager.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "BitMap.h"

Game_Scene::Game_Scene()
{
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

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperBack.bmp");
	m_pPaper[RED] = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperRed.bmp");
	m_pPaper[GREEN] = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperGreen.bmp");
	m_pPaper[BLUE] = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperBlue.bmp");
	m_pPaper[YELLOW] = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperYellow.bmp");
	m_pShow_Score = new JEngine::Label();
	m_pShow_Paper_Score = new JEngine::Label();
	m_pShow_Time = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperTimeBar.bmp");
	m_pShow_Fever[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("Fever1.bmp");
	m_pShow_Fever[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("Fever2.bmp");
	m_pShow_Fever[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("Fever3.bmp");
	m_pLoadingBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("LoadingBack.bmp");
	m_pLoading = JEngine::ResoucesManager::GetInstance()->GetBitmap("Loading.bmp");
	m_pLoadingWord = JEngine::ResoucesManager::GetInstance()->GetBitmap("Loading_Word.bmp");
	m_pTimeOut = JEngine::ResoucesManager::GetInstance()->GetBitmap("TimeOver.bmp");

	time = 0;
	game_score = 0;
	paper_score = 100;
	paper_dir = NULL;
	moving_check = false;
	fever_lv = 0;
	fever_gauge = 0;
	combo_count = 0;
	full_fever_time = 0;
	fever_light = 0;

	paper_x = 155;
	paper_y = 300;

	for (int i = 0; i < 2; i++)
		visible_paper[i] = rand() % 4;

	game_time = 45000 + GetTickCount();
	loading_time = 2300 + GetTickCount();
	timeover_time = 0;

}

bool Game_Scene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyDown(VK_UP) && moving_check == false)
	{
		paper_dir = UP;
		moving_check = true;
	}
	else if (JEngine::InputManager::GetInstance()->isKeyDown(VK_DOWN) && moving_check == false)
	{
		paper_dir = DOWN;
		moving_check = true;
	}
	else if (JEngine::InputManager::GetInstance()->isKeyDown(VK_LEFT) && moving_check == false)
	{
		paper_dir = LEFT;
		moving_check = true;
	}
	else if (JEngine::InputManager::GetInstance()->isKeyDown(VK_RIGHT) && moving_check == false)
	{
		paper_dir = RIGHT;
		moving_check = true;
	}
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
		JEngine::SceneManager::GetInstance()->LoadScene(1);

	return false;
}

void Game_Scene::Update(float fETime)
{
	time = fETime; // fps�� ���δ�?

	Time();
	if (timeover_time == 0)
		Move();
	Point();
	Fever();
}

void Game_Scene::Draw(HDC hdc)
{
	if (loading_time >= GetTickCount())
	{
		m_pLoadingBack->Draw(0, 0); // �ε�
		m_pLoading->Draw(115, 190);
		m_pLoadingWord->Draw(150, 370);
		game_time = 45000 + GetTickCount();
	}
	else
	{
		m_pBack->Draw(0, 0); // ���

		m_pPaper[visible_paper[1]]->Draw(155, 300);
		m_pPaper[visible_paper[0]]->Draw(paper_x, paper_y);

		m_pShow_Score->Draw();
		m_pShow_Paper_Score->Draw();
		if (timeover_time == 0)
			m_pShow_Time->Draw2(24, 618, (game_time - GetTickCount()) / 45000, 1.0);

		if (fever_lv == 1 && full_fever_time == 0)
			m_pShow_Fever[0]->Draw2(22, 53, 1, 1);
		else if (fever_lv == 2 && full_fever_time == 0)
			m_pShow_Fever[1]->Draw2(22, 53, 1, 1);
		else if (fever_lv == 2 && full_fever_time != 0)
		{
			if (fever_light >= 0 && fever_light <= 9)
				m_pShow_Fever[0]->Draw2(22, 53, 1, 1);
			else if (fever_light >= 10 && fever_light <= 19)
				m_pShow_Fever[1]->Draw2(22, 53, 1, 1);
			else if (fever_light >= 20 && fever_light <= 29)
				m_pShow_Fever[2]->Draw2(22, 53, 1, 1);
			else
				fever_light = 0;

			fever_light++;
		}

		if (full_fever_time == 0)
			m_pShow_Fever[fever_lv]->Draw2(22, 53, fever_gauge / 200, 1);

		if (timeover_time != 0)
			m_pTimeOut->Draw(115, 280);
	}

}

void Game_Scene::Release()
{
	JEngine::UIManager::GetInstance()->RelaaseUI();
}

void Game_Scene::Move()
{
	if (paper_dir == UP && paper_y > UP_END)
	{
		paper_y -= 11;
	}
	else if (paper_dir == DOWN && paper_y < DOWN_END)
	{
		paper_y += 11;
	}
	else if (paper_dir == LEFT && paper_x > LEFT_END)
	{
		paper_x -= 11;
	}
	else if (paper_dir == RIGHT && paper_x < RIGHT_END)
	{
		paper_x += 11;
	}
	else if (moving_check == true)
	{
		if (paper_y >= UP_END || paper_y <= DOWN_END || paper_x >= LEFT_END || paper_x <= RIGHT_END) // ���̸� ��������
		{
			if (fever_lv == 1)
				paper_score += 100;
			else if (fever_lv == 2 && fever_gauge < 200 && full_fever_time == 0)
				paper_score += 200;
			else if (full_fever_time != 0)
				paper_score += 300;

			if (paper_dir == UP && visible_paper[0] == GREEN)
			{
				game_score += paper_score;
				if (fever_lv < 3 && fever_gauge <= 200)
					fever_gauge += 20;
				combo_count++;
			}
			else if (paper_dir == DOWN && visible_paper[0] == YELLOW)
			{
				game_score += paper_score;
				if (fever_lv < 3 && fever_gauge <= 200)
					fever_gauge += 20;
				combo_count++;
			}
			else if (paper_dir == LEFT && visible_paper[0] == BLUE)
			{
				game_score += paper_score;
				if (fever_lv < 3 && fever_gauge <= 200)
					fever_gauge += 20;
				combo_count++;
			}
			else if (paper_dir == RIGHT && visible_paper[0] == RED)
			{
				game_score += paper_score;
				if (fever_lv < 3 && fever_gauge <= 200)
					fever_gauge += 20;
				combo_count++;
			}
			else // Ʋ������
			{
				combo_count = 0;
				fever_gauge -= 40;

				if (fever_lv == 1)
					paper_score = 200;
				else if (fever_lv == 2 && fever_gauge < 200 && full_fever_time == 0)
					paper_score = 300;
				else if (full_fever_time != 0)
					paper_score = 400;
				else
					paper_score = 100;
			}


			moving_check = false;
			paper_dir = NULL;
			visible_paper[0] = visible_paper[1];
			visible_paper[1] = rand() % 4;
			paper_x = 155;
			paper_y = 300;

		}
	}
}

void Game_Scene::Point()
{
	char buf[256] = {};
	char buf2[256] = {};

	sprintf_s(buf, "%d", game_score);
	m_pShow_Score->Init(buf, 200, 25, DT_CENTER);

	sprintf_s(buf2, "%d", paper_score);
	m_pShow_Paper_Score->Init(buf2, paper_x + 40, paper_y + 45, DT_CENTER);
}

void Game_Scene::Time()
{
	if (game_time <= GetTickCount() && timeover_time == 0)
		timeover_time = 3000 + GetTickCount();
	else if (game_time <= GetTickCount() && timeover_time <= GetTickCount())
		JEngine::SceneManager::GetInstance()->LoadScene(1);
}

void Game_Scene::Fever()
{
	if (fever_gauge > 0 && fever_lv < 3)
		fever_gauge -= 0.02;

	if (fever_gauge <= 0 && fever_lv > 0)
	{
		fever_lv--;
		fever_gauge = 199;
	}
	else if (fever_gauge <= 0 && fever_lv == 0)
		fever_gauge = 0;

	if (fever_gauge >= 200)
	{
		if (fever_lv < 2)
		{
			fever_gauge = 10;
			fever_lv++;
		}
		else if (fever_lv == 2)
		{
			fever_gauge = 200;
		}
	}

	if (fever_lv == 2 && fever_gauge == 200)
	{
		if (full_fever_time == 0)
			full_fever_time = 5500 + GetTickCount();
		else if (full_fever_time <= GetTickCount())
		{
			full_fever_time = 0;
			fever_lv = 0;
			fever_gauge = 0;
			paper_score = 100;
		}
	}

	if (combo_count == 5)
	{
		fever_gauge += 40;
		combo_count = 0;
	}

	/*
	�ǹ� 1�ܰ� - �⺻����������Ʈ + 100 ������� - ��������Ʈ 200
	�ǹ� 2�ܰ� - �⺻����������Ʈ + 200 ������� - ��������Ʈ 300
	�ǹ� 3�ܰ� - �⺻����������Ʈ + 300 ������� - ��������Ʈ 400

	�޺� 5������ �ǹ������� 2�� ����
	*/
}

Game_Scene::~Game_Scene()
{
}

