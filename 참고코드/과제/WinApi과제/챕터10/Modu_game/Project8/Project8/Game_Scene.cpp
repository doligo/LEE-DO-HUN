#include "Game_Scene.h"
#include "InputManager.h"
#include "ResoucesManager.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "BitMap.h"

Game_Scene::Game_Scene()
{
	time = 0;
	game_time = 0;
	game_score = 0;
	paper_score = 100;
	paper_dir = NULL;
	moving_check = false;
	fever_lv = 0;
	fever_gauge = 0;
	combo_count = 0;
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

	paper_x = 155;
	paper_y = 300;

	for (int i = 0; i < 2; i++)
		visible_paper[i] = rand() % 4;

	game_time = 35000 + GetTickCount();
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
	time = fETime; // fps에 쓰인다?

	Time();
	Move();
	Point();
	Fever();
}

void Game_Scene::Draw(HDC hdc)
{
	m_pBack->Draw(0, 0); // 배경

	m_pPaper[visible_paper[1]]->Draw(155, 300);
	m_pPaper[visible_paper[0]]->Draw(paper_x, paper_y);

	m_pShow_Score->Draw();
	m_pShow_Paper_Score->Draw();
	m_pShow_Time->Draw2(24, 618, (game_time - GetTickCount()) / 35000, 1.0);

	if (fever_lv == 1)
		m_pShow_Fever[0]->Draw2(22, 53, 1, 1);
	else if (fever_lv == 2)
		m_pShow_Fever[1]->Draw2(22, 53, 1, 1);
	m_pShow_Fever[fever_lv]->Draw2(22, 53, fever_gauge / 200, 1);
}

void Game_Scene::Release()
{

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
		if (paper_y >= UP_END || paper_y <= DOWN_END || paper_x >= LEFT_END || paper_x <= RIGHT_END) // 종이를 맞췄을때
		{
			if (paper_dir == UP && visible_paper[0] == GREEN)
			{
				game_score += paper_score;
				if (fever_lv < 3)
					fever_gauge += 20;
				combo_count++;
			}
			else if (paper_dir == DOWN && visible_paper[0] == YELLOW)
			{
				game_score += paper_score;
				if (fever_lv < 3)
					fever_gauge += 20;
				combo_count++;
			}
			else if (paper_dir == LEFT && visible_paper[0] == BLUE)
			{
				game_score += paper_score;
				if (fever_lv < 3)
					fever_gauge += 20;
				combo_count++;
			}
			else if (paper_dir == RIGHT && visible_paper[0] == RED)
			{
				game_score += paper_score;
				if (fever_lv < 3)
					fever_gauge += 20;
				combo_count++;
			}
			else // 틀렸을때
			{
				combo_count = 0;
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
	if (game_time <= GetTickCount())
		JEngine::SceneManager::GetInstance()->LoadScene(1);
}

void Game_Scene::Fever()
{
	if (fever_gauge > 0)
		fever_gauge -= 0.02;

	if (fever_lv > 0 && fever_gauge <= 0)
	{
		fever_lv--;
		fever_gauge = 199;
	}

	if (fever_gauge >= 200)
	{
		if (fever_lv < 2)
		{
			fever_lv++;
			fever_gauge = 10;
		}
		else
			fever_gauge = 200;
	}

	if (fever_lv == 1)
		paper_score += 100;
	else if (fever_lv == 2)
		paper_score += 200;

	//// 5콤보당 현재 페이퍼포인트 2배
	/*
	피버 1단계 - 기본페이퍼포인트 + 100 계속증가
	피버 2단계 - 기본페이퍼포인트 + 200 계속증가
	피버 3단계 - 기본페이퍼포인트 + 300 계속증가
	*/
}

Game_Scene::~Game_Scene()
{
}
