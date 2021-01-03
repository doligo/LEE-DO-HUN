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
	m_pBullet = JEngine::ResoucesManager::GetInstance()->GetBitmap("FlightGameBullet.bmp");
	m_pExplosion[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("explosion1.bmp");
	m_pExplosion[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("explosion2.bmp");
	m_pExplosion[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("explosion3.bmp");
	m_pStar[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("FlightGameStar1.bmp");
	m_pStar[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("FlightGameStar2.bmp");
	m_pStar[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("FlightGameStar3.bmp");
	m_pFever_Effect = JEngine::ResoucesManager::GetInstance()->GetBitmap("FeverEffect3.bmp");
	m_pShow_Time = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperTimeBar.bmp");
	m_pTimeOut = JEngine::ResoucesManager::GetInstance()->GetBitmap("TimeOver.bmp");
	m_pLoadingBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("LoadingBack.bmp");
	m_pLoading = JEngine::ResoucesManager::GetInstance()->GetBitmap("Loading.bmp");
	m_pLoadingWord = JEngine::ResoucesManager::GetInstance()->GetBitmap("Loading_Word.bmp");

	m_pShow_Score = new JEngine::Label();
	for (int i = 0; i < STAR_MAX; i++)
		m_pShow_Star_Score[i] = new JEngine::Label();

	JEngine::TimeManager::GetInstance()->init(1, 144); // 초당 프레임 설정

	ShowCursor(false); // 커서 오프

	GetClientRect(hWnd, &tmp_clip);
	
	pt1.x = tmp_clip.left;
	pt1.y = tmp_clip.top;

	ClientToScreen(hWnd, &pt1);

	tmp_clip.left = pt1.x;
	tmp_clip.top = pt1.y + 90;
	tmp_clip.right = pt1.x + 348;
	tmp_clip.bottom = pt1.y + 544;

	ClipCursor(&tmp_clip);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i] != NULL)
		{
			delete bullet[i];
			bullet[i] = NULL;
		}
	}

	for (int i = 0; i < STAR_MAX; i++)
	{
		if (star[i] != NULL)
		{
			delete star[i];
			star[i] = NULL;
		}
	}

	time = 0;
	player_alive = true;
	game_start = false;
	explosion_count = 0;
	b_create_time = 0;
	s_create_time = 0;
	s_create_time2 = 0;

	star_lv = 0;
	fever_full_check = false;
	combo_count = 0;
	star_score = 100;
	game_score = 0;
	fever_light = 0;
	full_fever_time = 0;
	game_time = 45000 + GetTickCount();
	loading_time = 2300 + GetTickCount();
	timeover_time = 0;
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
	Time();

	if (timeover_time == 0)
	{
		if (player_alive == true)
			Set_Flight();
		Set_Bullet();
		Set_Star();
		Bullet_Collision();
		Eat_Star();
		Player_Alive_Check();
		Set_Score();
		Set_Fever();
	}
}

void Game2_Scene::Draw(HDC hdc)
{
	if (loading_time >= GetTickCount())
	{
		m_pLoadingBack->Draw(0, 0);
		m_pLoading->Draw(115, 190);
		m_pLoadingWord->Draw(150, 370);
		game_time = 45000 + GetTickCount();
	}
	else
	{
		m_pBack->Draw(0, 0);
		m_pShow_Score->Draw();

		if (player_alive == true)
			m_pFlight->Draw(m_pFlight_Pt);
		else if (player_alive == false)
		{
			if (explosion_count <= 7)
			{
				m_pExplosion[0]->Draw(m_pFlight_Pt.x - 20, m_pFlight_Pt.y - 18);
				explosion_count++;
			}
			else if (explosion_count <= 14)
			{
				m_pExplosion[1]->Draw(m_pFlight_Pt.x - 20, m_pFlight_Pt.y - 18);
				explosion_count++;
			}
			else if (explosion_count <= 21)
			{
				m_pExplosion[2]->Draw(m_pFlight_Pt.x - 20, m_pFlight_Pt.y - 18);
				explosion_count = 0;
				player_alive = true;
				game_start = false;
			}
		}

		for (int i = 0; i < STAR_MAX; i++) // 별
		{
			if (star[i] != NULL && star[i]->s_speed != 0)
				m_pStar[star_lv]->Draw(star[i]->s_rt.left, star[i]->s_rt.top);
		}

		for (int i = 0; i < STAR_MAX; i++) // 별점수
		{
			if (star[i] != NULL && star[i]->s_speed != 0)
				m_pShow_Star_Score[i]->Draw();
		}

		for (int i = 0; i < BULLET_MAX; i++) // 총알
		{
			if (bullet[i] != NULL)
				if (bullet[i]->b_speed != 0)
					m_pBullet->Draw(bullet[i]->b_rt.left, bullet[i]->b_rt.top);
		}

		if (fever_full_check == false)
			m_pShow_Fever[0]->Draw2(22, 53, fever_gauge / 200, 1);
		else if (fever_full_check == true)
		{
			if (fever_light >= 0 && fever_light <= 9)
				m_pShow_Fever[0]->Draw2(22, 53, 1, 1);
			else if (fever_light >= 10 && fever_light <= 19)
			{
				m_pShow_Fever[1]->Draw2(22, 53, 1, 1);
				m_pFever_Effect->Draw(0, 0);
			}
			else if (fever_light >= 20 && fever_light <= 29)
				m_pShow_Fever[2]->Draw2(22, 53, 1, 1);
			else
				fever_light = 0;

			fever_light++;
		}

		if (timeover_time == 0)
			m_pShow_Time->Draw2(24, 618, (game_time - GetTickCount()) / 45000, 1.0);

		if (timeover_time != 0)
			m_pTimeOut->Draw(115, 280);
	}
}

void Game2_Scene::Release()
{
	JEngine::UIManager::GetInstance()->RelaaseUI();
}

void Game2_Scene::Set_Flight()
{
	if (game_start == true)
	{
		m_pFlight_Pt = JEngine::InputManager::GetInstance()->GetMousePoint();
		m_pFlight_Rt.Set(m_pFlight_Pt.x + 22, m_pFlight_Pt.y + 15, m_pFlight_Pt.x + 22 + 15, m_pFlight_Pt.y + 15 + 16);
	}
	else if (game_start == false)
	{
		JEngine::InputManager::GetInstance()->SetMousePoint(tmp_clip.left + 172, tmp_clip.top + 420);
		SetCursorPos(tmp_clip.left + 172, tmp_clip.top + 420);
		m_pFlight_Rt.Set(-1, -1, -1, -1);
		game_start = true;
	}
}

void Game2_Scene::Set_Bullet()
{
	int tmp_select = 0;
	int dir_select = 0;

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i] == NULL && b_create_time <= GetTickCount())
		{
			bullet[i] = new Bullet_Info;
			bullet[i]->b_speed = 0;
			b_create_time = 1000 + GetTickCount();
			break;
		}
	}

	// 뒤에는 값이 0일경우 처음 좌표, 방향2개(ex))좌상, 우하) , 속도 랜덤설정
	// 그뒤에는 좌표, 방향2개, 속도 설정된 총알은 계속 이동하게끔하기

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i] != NULL)
		{
			if (bullet[i]->b_speed == 0)
			{
				bullet[i]->b_speed = rand() % 2 + 1;

				bullet[i]->b_dir1 = rand() % 4;
				if (bullet[i]->b_dir1 == D_UP)
					bullet[i]->b_dir2 = rand() % 2 + 2;
				else if (bullet[i]->b_dir1 == D_DOWN)
					bullet[i]->b_dir2 = rand() % 2 + 2;
				else if (bullet[i]->b_dir1 == D_LEFT)
					bullet[i]->b_dir2 = D_LEFT;
				else if (bullet[i]->b_dir1 == D_RIGHT)
					bullet[i]->b_dir2 = D_RIGHT;

				tmp_select = rand() % 3;

				if (tmp_select == 0)
				{
					bullet[i]->b_rt.left = 0;
					bullet[i]->b_rt.top = rand() % 491 + 90;

					dir_select = rand() % 3;

					Set_Dir(i, tmp_select, dir_select, 0);
				}
				else if (tmp_select == 1)
				{
					bullet[i]->b_rt.left = 397;
					bullet[i]->b_rt.top = rand() % 491 + 90;

					dir_select = rand() % 3;

					Set_Dir(i, tmp_select, dir_select, 0);
				}
				else if (tmp_select == 2)
				{
					bullet[i]->b_rt.left = rand() % 361;
					bullet[i]->b_rt.top = 90;

					dir_select = rand() % 3;

					Set_Dir(i, tmp_select, dir_select, 0);
				}

				bullet[i]->b_rt.right = bullet[i]->b_rt.left + 5;
				bullet[i]->b_rt.bottom = bullet[i]->b_rt.top + 5;
			}

			else if (JEngine::TimeManager::GetInstance()->GetElipseTime() <= GetTickCount()) // 좌표이동
			{
				if (bullet[i]->b_dir1 == D_UP && bullet[i]->b_dir2 == D_LEFT)
				{
					bullet[i]->b_rt.left -= bullet[i]->b_speed;
					bullet[i]->b_rt.top -= bullet[i]->b_speed;
				}
				else if (bullet[i]->b_dir1 == D_UP && bullet[i]->b_dir2 == D_RIGHT)
				{
					bullet[i]->b_rt.left += bullet[i]->b_speed;
					bullet[i]->b_rt.top -= bullet[i]->b_speed;
				}
				else if (bullet[i]->b_dir1 == D_DOWN && bullet[i]->b_dir2 == D_LEFT)
				{
					bullet[i]->b_rt.left -= bullet[i]->b_speed;
					bullet[i]->b_rt.top += bullet[i]->b_speed;
				}
				else if (bullet[i]->b_dir1 == D_DOWN && bullet[i]->b_dir2 == D_RIGHT)
				{
					bullet[i]->b_rt.left += bullet[i]->b_speed;
					bullet[i]->b_rt.top += bullet[i]->b_speed;
				}
				else if (bullet[i]->b_dir1 == D_LEFT && bullet[i]->b_dir2 == D_LEFT)
					bullet[i]->b_rt.left -= bullet[i]->b_speed;
				else if (bullet[i]->b_dir1 == D_RIGHT && bullet[i]->b_dir2 == D_RIGHT)
					bullet[i]->b_rt.left += bullet[i]->b_speed;
				else if (bullet[i]->b_dir1 == D_DOWN && bullet[i]->b_dir2 == D_DOWN)
					bullet[i]->b_rt.top += bullet[i]->b_speed;

				bullet[i]->b_rt = { bullet[i]->b_rt.left, bullet[i]->b_rt.top, bullet[i]->b_rt.left + 5, bullet[i]->b_rt.top + 5 };
			}
		}
	}
	Out_of_Map(0);
}

void Game2_Scene::Set_Dir(int num, int start_point, int dir, int bullet_or_star)
{
	if (bullet_or_star == 0)
	{
		if (start_point == 0)
		{
			if (dir == 0)
			{
				bullet[num]->b_dir1 = D_UP;
				bullet[num]->b_dir2 = D_RIGHT;
			}
			else if (dir == 1)
			{
				bullet[num]->b_dir1 = D_DOWN;
				bullet[num]->b_dir2 = D_RIGHT;
			}
			else if (dir == 2)
			{
				bullet[num]->b_dir1 = D_RIGHT;
				bullet[num]->b_dir2 = D_RIGHT;
			}
		}
		else if (start_point == 1)
		{
			if (dir == 0)
			{
				bullet[num]->b_dir1 = D_UP;
				bullet[num]->b_dir2 = D_LEFT;
			}
			else if (dir == 1)
			{
				bullet[num]->b_dir1 = D_DOWN;
				bullet[num]->b_dir2 = D_LEFT;
			}
			else if (dir == 2)
			{
				bullet[num]->b_dir1 = D_LEFT;
				bullet[num]->b_dir2 = D_LEFT;
			}
		}
		else if (start_point == 2)
		{
			if (dir == 0)
			{
				bullet[num]->b_dir1 = D_DOWN;
				bullet[num]->b_dir2 = D_LEFT;
			}
			else if (dir == 1)
			{
				bullet[num]->b_dir1 = D_DOWN;
				bullet[num]->b_dir2 = D_RIGHT;
			}
			else if (dir == 2)
			{
				bullet[num]->b_dir1 = D_DOWN;
				bullet[num]->b_dir2 = D_DOWN;
			}
		}
	}
	else if (bullet_or_star == 1)
	{
		if (start_point == 0)
		{
			if (dir == 0)
			{
				star[num]->s_dir1 = D_UP;
				star[num]->s_dir2 = D_RIGHT;
			}
			else if (dir == 1)
			{
				star[num]->s_dir1 = D_DOWN;
				star[num]->s_dir2 = D_RIGHT;
			}
			else if (dir == 2)
			{
				star[num]->s_dir1 = D_RIGHT;
				star[num]->s_dir2 = D_RIGHT;
			}
		}
		else if (start_point == 1)
		{
			if (dir == 0)
			{
				star[num]->s_dir1 = D_UP;
				star[num]->s_dir2 = D_LEFT;
			}
			else if (dir == 1)
			{
				star[num]->s_dir1 = D_DOWN;
				star[num]->s_dir2 = D_LEFT;
			}
			else if (dir == 2)
			{
				star[num]->s_dir1 = D_LEFT;
				star[num]->s_dir2 = D_LEFT;
			}
		}
		else if (start_point == 2)
		{
			if (dir == 0)
			{
				star[num]->s_dir1 = D_DOWN;
				star[num]->s_dir2 = D_LEFT;
			}
			else if (dir == 1)
			{
				star[num]->s_dir1 = D_DOWN;
				star[num]->s_dir2 = D_RIGHT;
			}
			else if (dir == 2)
			{
				star[num]->s_dir1 = D_DOWN;
				star[num]->s_dir2 = D_DOWN;
			}
		}
	}
}

void Game2_Scene::Out_of_Map(int num)
{
	if (num == 0)
	{
		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (bullet[i] != NULL)
				if (bullet[i]->b_rt.left < 0 || bullet[i]->b_rt.left > 397 || bullet[i]->b_rt.top < 90 || bullet[i]->b_rt.top > 580)
					bullet[i]->b_speed = 0;
		}
	}
	else if (num == 1)
	{
		for (int i = 0; i < STAR_MAX; i++)
		{
			if (star[i] != NULL)
				if (star[i]->s_rt.left < 0 || star[i]->s_rt.left > 397 || star[i]->s_rt.top < 90 || star[i]->s_rt.top > 580)
					star[i]->s_speed = 0;
		}
	}
}

void Game2_Scene::Bullet_Collision()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i] != NULL)
			if (bullet[i]->b_rt.isCollision(m_pFlight_Rt))
			{
				player_alive = false;
				combo_count = 0;
				star_score = 100;
				fever_full_check = false;
				full_fever_time = 0;
				break;
			}
	}
}

void Game2_Scene::Player_Alive_Check()
{
	if (player_alive == false)
	{
		for (int j = 0; j < BULLET_MAX; j++)
		{
			if (bullet[j] == NULL)
				break;
			else
			{
				bullet[j]->b_rt = { -1,-1,-1,-1 };
				bullet[j]->b_speed = 0;
				bullet[j] = NULL;
			}
		}

		for (int i = 0; i < STAR_MAX; i++)
		{
			if (star[i] == NULL)
				break;
			else
			{
				star[i]->s_rt = { -1,-1,-1,-1 };
				star[i]->s_speed = 0;
				star[i] = NULL;
			}
		}
	}
}

void Game2_Scene::Set_Star()
{
	int tmp_select = 0;
	int dir_select = 0;

	for (int i = 0; i < STAR_MAX; i++)
	{
		if (star[i] == NULL && s_create_time <= GetTickCount())
		{
			star[i] = new Star_Info;
			star[i]->s_speed = 0;
			s_create_time = 2000 + GetTickCount();
			break;
		}
	}

	for (int i = 0; i < STAR_MAX; i++)
	{
		if (star[i] != NULL)
		{
			if (star[i]->s_speed == 0 && s_create_time2 <= GetTickCount())
			{
				star[i]->s_speed = 1;

				star[i]->s_dir1 = rand() % 4;
				if (star[i]->s_dir1 == D_UP)
					star[i]->s_dir2 = rand() % 2 + 2;
				else if (star[i]->s_dir1 == D_DOWN)
					star[i]->s_dir2 = rand() % 2 + 2;
				else if (star[i]->s_dir1 == D_LEFT)
					star[i]->s_dir2 = D_LEFT;
				else if (star[i]->s_dir1 == D_RIGHT)
					star[i]->s_dir2 = D_RIGHT;

				tmp_select = rand() % 3;

				if (tmp_select == 0)
				{
					star[i]->s_rt.left = 0;
					star[i]->s_rt.top = rand() % 491 + 90;

					dir_select = rand() % 3;

					Set_Dir(i, tmp_select, dir_select, 1);
				}
				else if (tmp_select == 1)
				{
					star[i]->s_rt.left = 397;
					star[i]->s_rt.top = rand() % 491 + 90;

					dir_select = rand() % 3;

					Set_Dir(i, tmp_select, dir_select, 1);
				}
				else if (tmp_select == 2)
				{
					star[i]->s_rt.left = rand() % 361;
					star[i]->s_rt.top = 90;

					dir_select = rand() % 3;

					Set_Dir(i, tmp_select, dir_select, 1);
				}

				star[i]->s_rt.right = star[i]->s_rt.left + 12;
				star[i]->s_rt.bottom = star[i]->s_rt.top + 12;

				s_create_time2 = 1500 + GetTickCount();
			}

			else if (JEngine::TimeManager::GetInstance()->GetElipseTime() <= GetTickCount())
			{
				if (star[i]->s_dir1 == D_UP && star[i]->s_dir2 == D_LEFT)
				{
					star[i]->s_rt.left -= star[i]->s_speed;
					star[i]->s_rt.top -= star[i]->s_speed;
				}
				else if (star[i]->s_dir1 == D_UP && star[i]->s_dir2 == D_RIGHT)
				{
					star[i]->s_rt.left += star[i]->s_speed;
					star[i]->s_rt.top -= star[i]->s_speed;
				}
				else if (star[i]->s_dir1 == D_DOWN && star[i]->s_dir2 == D_LEFT)
				{
					star[i]->s_rt.left -= star[i]->s_speed;
					star[i]->s_rt.top += star[i]->s_speed;
				}
				else if (star[i]->s_dir1 == D_DOWN && star[i]->s_dir2 == D_RIGHT)
				{
					star[i]->s_rt.left += star[i]->s_speed;
					star[i]->s_rt.top += star[i]->s_speed;
				}
				else if (star[i]->s_dir1 == D_LEFT && star[i]->s_dir2 == D_LEFT)
					star[i]->s_rt.left -= star[i]->s_speed;
				else if (star[i]->s_dir1 == D_RIGHT && star[i]->s_dir2 == D_RIGHT)
					star[i]->s_rt.left += star[i]->s_speed;
				else if (star[i]->s_dir1 == D_DOWN && star[i]->s_dir2 == D_DOWN)
					star[i]->s_rt.top += star[i]->s_speed;

				star[i]->s_rt = { star[i]->s_rt.left, star[i]->s_rt.top, star[i]->s_rt.left + 47, star[i]->s_rt.top + 45 };
			}
		}

	}
	Out_of_Map(1);
}

void Game2_Scene::Set_Fever()
{
	if (fever_gauge > 0 && fever_full_check == false)
		fever_gauge += 0.02;

	if (fever_gauge >= 200 && fever_full_check == false)
	{
		fever_gauge = 0;
		fever_full_check = true;
	}

	if (fever_full_check == true)
	{
		if (full_fever_time == 0)
			full_fever_time = 4500 + GetTickCount();
		else if (full_fever_time <= GetTickCount())
		{
			full_fever_time = 0;
			fever_gauge = 0;
			fever_full_check = false;
		}
		s_create_time = 0;
		s_create_time2 = 0;
	}
}

void Game2_Scene::Set_Score()
{
	char buf[256] = {};
	char buf2[256] = {};

	sprintf_s(buf, "%d", game_score);
	m_pShow_Score->Init(buf, 200, 25, DT_CENTER);

	sprintf_s(buf2, "%d", star_score);
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (star[i] != NULL)
			m_pShow_Star_Score[i]->Init(buf2, star[i]->s_rt.left + 17, star[i]->s_rt.top + 21, DT_CENTER);
	}
}

void Game2_Scene::Eat_Star()
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (star[i] != NULL)
			if (star[i]->s_rt.isCollision(m_pFlight_Rt))
			{
				game_score += star_score;
				star_score += 100;
				combo_count++;
				if (fever_full_check == false)
					fever_gauge += 20;
				star[i] = NULL;
				break;
			}
	}

	if (combo_count >= 10 && combo_count < 20)
		star_lv = 1;
	else if (combo_count >= 20)
		star_lv = 2;
	else if (combo_count < 10)
		star_lv = 0;
}

void Game2_Scene::Time()
{
	if (game_time <= GetTickCount() && timeover_time == 0)
		timeover_time = 3000 + GetTickCount();
	else if (game_time <= GetTickCount() && timeover_time <= GetTickCount())
	{
		ShowCursor(true); // 커서 온
		ClipCursor(NULL);
		JEngine::SceneManager::GetInstance()->LoadScene(1);
	}
}

Game2_Scene::~Game2_Scene()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i] != NULL)
		{
			delete bullet[i];
			bullet[i] = NULL;
		}
	}

	for (int i = 0; i < STAR_MAX; i++)
	{
		if (star[i] != NULL)
		{
			delete star[i];
			star[i] = NULL;
		}
	}
}

/*
<콤보>
10콤보당 별레벨 업하기
죽으면 콤보 올초기화

<피버>
피버모드 진입 시 존재하는 모든별 젠되게하기
죽으면 피버 올초기화

*/