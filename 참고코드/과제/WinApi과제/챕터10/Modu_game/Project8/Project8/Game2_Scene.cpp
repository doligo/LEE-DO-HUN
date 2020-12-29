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
	m_pBullet = JEngine::ResoucesManager::GetInstance()->GetBitmap("FlightGameBullet.bmp");
	m_pExplosion[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("explosion1.bmp");
	m_pExplosion[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("explosion2.bmp");
	m_pExplosion[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("explosion3.bmp");

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

	time = 0;
	bullet_move_time = 0;
	player_alive = true;
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
	Set_Bullet();
	Bullet_Collision();
}

void Game2_Scene::Draw(HDC hdc)
{
	m_pBack->Draw(0, 0);
	
	if (player_alive == true)
		m_pFlight->Draw(m_pFlight_Pt);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i]->b_speed != 0)
			m_pBullet->Draw(bullet[i]->b_rt.left, bullet[i]->b_rt.top);
	}
}

void Game2_Scene::Release()
{
	
}

void Game2_Scene::Set_Flight()
{
	m_pFlight_Pt = JEngine::InputManager::GetInstance()->GetMousePoint();
	m_pFlight_Rt.Set(m_pFlight_Pt.x, m_pFlight_Pt.y, m_pFlight_Pt.x + 10, m_pFlight_Pt.y + 10);
}

void Game2_Scene::Set_Bullet()
{
	int tmp_select = 0;
	int dir_select = 0;

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i] == NULL)
		{
			bullet[i] = new Bullet_Info;
			bullet[i]->b_speed = 0;
		}

		// 뒤에는 값이 0일경우 처음 좌표, 방향2개(ex))좌상, 우하) , 속도 랜덤설정
		// 그뒤에는 좌표, 방향2개, 속도 설정된 총알은 계속 이동하게끔하기

		else if (bullet[i]->b_speed == 0)
		{
			bullet[i]->b_speed = rand() % 2 + 1;

			bullet[i]->b_dir1 = rand() % 4;
			if (bullet[i]->b_dir1 == B_UP)
				bullet[i]->b_dir2 = rand() % 2 + 2;
			else if (bullet[i]->b_dir1 == B_DOWN)
				bullet[i]->b_dir2 = rand() % 2 + 2;
			else if (bullet[i]->b_dir1 == B_LEFT)
				bullet[i]->b_dir2 = B_LEFT;
			else if (bullet[i]->b_dir1 == B_RIGHT)
				bullet[i]->b_dir2 = B_RIGHT;

			tmp_select = rand() % 3;

			if (tmp_select == 0)
			{
				bullet[i]->b_rt.left = 0;
				bullet[i]->b_rt.top = rand() % 491 + 90;

				dir_select = rand() % 3;

				Set_Bullet_Dir(i, tmp_select, dir_select);
			}
			else if (tmp_select == 1)
			{
				bullet[i]->b_rt.left = 397;
				bullet[i]->b_rt.top = rand() % 491 + 90;

				dir_select = rand() % 3;

				Set_Bullet_Dir(i, tmp_select, dir_select);
			}
			else if (tmp_select == 2)
			{
				bullet[i]->b_rt.left = rand() % 361;
				bullet[i]->b_rt.top = 90;

				dir_select = rand() % 3;

				Set_Bullet_Dir(i, tmp_select, dir_select);
			}

			bullet[i]->b_rt.right = bullet[i]->b_rt.left + 5;
			bullet[i]->b_rt.bottom = bullet[i]->b_rt.top + 5;
		}

		else if (bullet_move_time >= GetTickCount()) // 좌표이동
		{
			if (bullet[i]->b_dir1 == B_UP && bullet[i]->b_dir2 == B_LEFT)
			{
				bullet[i]->b_rt.left -= bullet[i]->b_speed;
				bullet[i]->b_rt.top -= bullet[i]->b_speed;
			}
			else if (bullet[i]->b_dir1 == B_UP && bullet[i]->b_dir2 == B_RIGHT)
			{
				bullet[i]->b_rt.left += bullet[i]->b_speed;
				bullet[i]->b_rt.top -= bullet[i]->b_speed;
			}
			else if (bullet[i]->b_dir1 == B_DOWN && bullet[i]->b_dir2 == B_LEFT)
			{
				bullet[i]->b_rt.left -= bullet[i]->b_speed;
				bullet[i]->b_rt.top += bullet[i]->b_speed;
			}
			else if (bullet[i]->b_dir1 == B_DOWN && bullet[i]->b_dir2 == B_RIGHT)
			{
				bullet[i]->b_rt.left += bullet[i]->b_speed;
				bullet[i]->b_rt.top += bullet[i]->b_speed;
			}
			else if (bullet[i]->b_dir1 == B_LEFT && bullet[i]->b_dir2 == B_LEFT)
				bullet[i]->b_rt.left -= bullet[i]->b_speed;
			else if (bullet[i]->b_dir1 == B_RIGHT && bullet[i]->b_dir2 == B_RIGHT)
				bullet[i]->b_rt.left += bullet[i]->b_speed;
			else if (bullet[i]->b_dir1 == B_DOWN && bullet[i]->b_dir2 == B_DOWN)
				bullet[i]->b_rt.top += bullet[i]->b_speed;

			bullet[i]->b_rt = { bullet[i]->b_rt.left, bullet[i]->b_rt.top, bullet[i]->b_rt.left + 5, bullet[i]->b_rt.top + 5 };
		}
	}

	bullet_move_time = 10 + GetTickCount();
	Out_of_Map();
}

void Game2_Scene::Set_Bullet_Dir(int num, int start_point, int dir)
{
	if (start_point == 0)
	{
		if (dir == 0)
		{
			bullet[num]->b_dir1 = B_UP;
			bullet[num]->b_dir2 = B_RIGHT;
		}
		else if (dir == 1)
		{
			bullet[num]->b_dir1 = B_DOWN;
			bullet[num]->b_dir2 = B_RIGHT;
		}
		else if (dir == 2)
		{
			bullet[num]->b_dir1 = B_RIGHT;
			bullet[num]->b_dir2 = B_RIGHT;
		}
	}
	else if (start_point == 1)
	{
		if (dir == 0)
		{
			bullet[num]->b_dir1 = B_UP;
			bullet[num]->b_dir2 = B_LEFT;
		}
		else if (dir == 1)
		{
			bullet[num]->b_dir1 = B_DOWN;
			bullet[num]->b_dir2 = B_LEFT;
		}
		else if (dir == 2)
		{
			bullet[num]->b_dir1 = B_LEFT;
			bullet[num]->b_dir2 = B_LEFT;
		}
	}
	else if (start_point == 2)
	{
		if (dir == 0)
		{
			bullet[num]->b_dir1 = B_DOWN;
			bullet[num]->b_dir2 = B_LEFT;
		}
		else if (dir == 1)
		{
			bullet[num]->b_dir1 = B_DOWN;
			bullet[num]->b_dir2 = B_RIGHT;
		}
		else if (dir == 2)
		{
			bullet[num]->b_dir1 = B_DOWN;
			bullet[num]->b_dir2 = B_DOWN;
		}
	}
}

void Game2_Scene::Out_of_Map()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i] != NULL)
			if (bullet[i]->b_rt.left < 0 || bullet[i]->b_rt.left > 397 || bullet[i]->b_rt.top < 90 || bullet[i]->b_rt.top > 580)
			{
				bullet[i]->b_speed = 0;
			}
	}
}

void Game2_Scene::Bullet_Collision()
{

}

Game2_Scene::~Game2_Scene()
{
}