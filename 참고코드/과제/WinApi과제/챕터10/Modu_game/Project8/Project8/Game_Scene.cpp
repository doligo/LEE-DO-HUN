#include "Game_Scene.h"
#include "InputManager.h"
#include "ResoucesManager.h"
#include "UIManager.h"
#include "SceneManager.h"

Game_Scene::Game_Scene()
{
	time = 0;
	game_score = 0;
	paper_score = 100;
	paper_dir = NULL;
	moving_check = false;
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

	paper_x = 155;
	paper_y = 300;

	for (int i = 0; i < 2; i++)
		visible_paper[i] = rand() % 4;
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
	time = fETime;

	Move();
	Point();
}

void Game_Scene::Draw(HDC hdc)
{

	m_pBack->Draw(0, 0); // ¹è°æ

	m_pPaper[visible_paper[1]]->Draw(155, 300);
	m_pPaper[visible_paper[0]]->Draw(paper_x, paper_y);

	m_pShow_Score->Draw();
	m_pShow_Paper_Score->Draw();
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
		if (paper_y >= UP_END || paper_y <= DOWN_END || paper_x >= LEFT_END || paper_x <= RIGHT_END)
		{
			if (paper_dir == UP && visible_paper[0] == GREEN)
				game_score += paper_score;
			else if (paper_dir == DOWN && visible_paper[0] == YELLOW)
				game_score += paper_score;
			else if (paper_dir == LEFT && visible_paper[0] == BLUE)
				game_score += paper_score;
			else if (paper_dir == RIGHT && visible_paper[0] == RED)
				game_score += paper_score;

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

Game_Scene::~Game_Scene()
{
}
