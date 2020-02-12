#include "Play.h"

Play::Play()
{
	m_iLife = FULL_HP;
	m_iScore = 0;
	m_iName = { "\0" };
	m_iWord = { "\0" };
	m_iTmpWord = { "\0" };
	m_iStage = 1;
	m_iload_word = 0; // 총 단어 갯수
	w = NULL; // 단어
	m_inum = 0;
	m_iTmp_Iw[INSERT_WORD_MAX] = { '\0' };
	m_iPause = FALSE;
	m_iSpeed = 900; //기본속도
	m_iCreate_Speed = 3000; // 기본생성속도
}

void Play::Life_Name()
{
	char buf[256];

	RED
	Ui.TextDraw("Life : ", 1, HEIGHT + 1);
	for (int i = 0, j = 8; i < m_iLife; i++) // 하트 보유수만큼 출력
	{
		Ui.HeartDraw(j, HEIGHT + 1);
		j += 2;
	}
	sprintf_s(buf, "Score : %d", m_iScore);
	Ui.DrawMidText(buf, WIDTH, HEIGHT + 1);
	if (m_iName == "\0")
	{
		Ui.DrawMidText("Name : 이름없음", WIDTH * 1.8, HEIGHT + 1);
	}
	else
	{
		Ui.DrawMidText("Name : " + m_iName, WIDTH * 1.8, HEIGHT + 1);
	}
}

void Play::Start()
{
	int Select = 0;

	if (w != NULL)
	{
		delete[] w;
	}
	w = new _Ward[WARD_MAX]; // 미리 공간을 할당해야 Load_Ward 에서 동작이됌

	Load_Ward(w, m_iload_word);	// 단어 불러오기
	Set_xy(w); // 단어 위치 세팅

	Ui.First_Screen();
	Life_Name();

	BLUE
	Ui.DrawMidText("1.Game Start", WIDTH , HEIGHT * 0.4);
	Ui.DrawMidText("2.Rank", WIDTH, HEIGHT * 0.4 + 3);
	Ui.DrawMidText("3.Exit", WIDTH, HEIGHT * 0.4 + 6);

	Select = Ui.MenuSelectCursor(3, 3, WIDTH * 0.4, HEIGHT * 0.4);

	if (Select == 1)
	{
		Game_Start();
	}

}

void Play::Game_Start()
{

	Ui.Game_Screen();
	Life_Name();

	BLUE
	Ui.DrawMidText("Skip : s", WIDTH, HEIGHT * 0.75);

	Story();
	Insert_Name();
	Playing();
}

void Play::Story()
{
	int i = 0;
	int line = 0;
	string story_talk[26] = { "0" };
	char ch = 0;
	ifstream Read;

	Read.open("베네치아_스토리.txt");




	if (!Read.eof())
	{
		Read >> line;
		while (line != 0)
		{
			getline(Read, story_talk[i]);
			i++;
			line--;
		}
	}


	for (int j = 0, k = 0, n = 0; j < i; j++)
	{
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 's')
			return;
		}

		Sleep(500);
		if (j > 9)
		{
			k = 0;
			n += 1;
			while (k != j - n)
			{
				if (_kbhit())
				{
					ch = _getch();
					if (ch == 's')
						return;
				}

				Ui.DrawMidText("                                          ", WIDTH, HEIGHT * 0.2 + k);
				Ui.DrawMidText(story_talk[k + n], WIDTH, HEIGHT * 0.2 + k);
				k++;
			}
			Ui.DrawMidText("                                          ", WIDTH, HEIGHT * 0.2 + j - n);
			Ui.DrawMidText(story_talk[j], WIDTH, HEIGHT * 0.2 + j - n);
		}
		else
		Ui.DrawMidText(story_talk[j], WIDTH, HEIGHT * 0.2 + j);
	}
}

void Play::Insert_Name()
{
	char ch = 0;
	char name_tmp[9] = { '\0' };
	int num = 0;
	string tmp = { "\0" };

	Ui.Game_Screen();
	Life_Name();


	BLUE
	Ui.DrawMidText("이름 입력", WIDTH, HEIGHT * 0.75 - 5);
	Ui.gotoxy(WIDTH, HEIGHT * 0.75);

	while (1)
	{
		ch = _getch();

		if (ch == BACK_SPACE && num >= 1)
		{
			num--;
			name_tmp[num] = { '\0' };
			tmp = { "\0" };
			for (int i = 0; i < num; i++)
			{
				tmp += name_tmp[i];
			}
			Ui.DrawMidText("                   ", WIDTH, HEIGHT * 0.75 - 4);
		}

		else if (name_tmp[8] != NULL)
		{
			Ui.DrawMidText("10글자 초과!!", WIDTH, HEIGHT * 0.75 - 4);
			_getch();
		}

		else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		{
			name_tmp[num] = ch;
			tmp += name_tmp[num];
			num++;
		}

		else if (ch == ENTER)
		{
			m_iName = tmp;
			break;
		}

		Ui.DrawMidText("                    ", WIDTH, HEIGHT * 0.75);
		Ui.DrawMidText(tmp, WIDTH, HEIGHT * 0.75);
	}

	// 영어이외에는 입력안되고 한글은 바로지워짐
	// 9글자 까지, 입력하는 즉시 텍스트가 중앙에 맞춰짐
}

void Play::Insert_Word() // m_iPause == FALSE 구문 3개로 비패널티와 패널티시에 구분
{
	char ch = 0;

	BLUE

	if (m_iPause == FALSE)
	{
		Ui.gotoxy(WIDTH, HEIGHT * 0.75);
	}

	ch = _getch();

	if (ch == BACK_SPACE && m_inum >= 1)
	{
		m_inum--;
		m_iTmp_Iw[m_inum] = { '\0' };
		m_iTmpWord = { "\0" };
		for (int i = 0; i < m_inum; i++)
		{
			m_iTmpWord += m_iTmp_Iw[i];
		}
		Ui.DrawMidText("                   ", WIDTH, HEIGHT * 0.75 - 4);
	}

	else if (m_iTmp_Iw[18] != NULL)
	{
		Ui.DrawMidText("20글자 초과!!", WIDTH, HEIGHT * 0.75 - 4);
		_getch();
	}

	
	else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
	{
		if (m_iPause == FALSE)
		{
			m_iTmp_Iw[m_inum] = ch;
			m_iTmpWord += m_iTmp_Iw[m_inum];
			m_inum++;
		}
	}

	else if (ch == ENTER)
	{
		m_iWord = m_iTmpWord;
		m_iTmpWord = { "\0" }; // 다음단어를 위해 초기화
		m_inum = 0;
		m_iTmp_Iw[INSERT_WORD_MAX] = { '\0' };
		Correct_Word();
		Life_Name(); // 점수 바로 출력
	}

	if (m_iPause == FALSE)
	{
		Ui.DrawMidText("                    ", WIDTH, HEIGHT * 0.75);
		Ui.DrawMidText(m_iTmpWord, WIDTH, HEIGHT * 0.75);
	}

}

void Play::Draw_Drop()
{
	int printed_word[WARD_MAX] = {'\0'};
	int word_num = 0;
	int num = 0;

	int move_time = 0;
	int old_time = 0;
	int cur_time = 0;

	int pause_old_time = 0; // 패널티
	int pause_cur_time = 0;

	int warning_time = 0;

	move_time = clock();
	old_time = clock();
	pause_old_time = clock();
	warning_time = clock();

	while (word_num != WARD_MAX)
	{
		cur_time = clock();
		pause_cur_time = clock();

		if (_kbhit()) // ★★★ kbhit는 경험상 딜레이가 있어도 미리 입력해놓으면 나중에 실행된다;;??
		{            // 그래서 && 로 진입이 안되게하지말고 다른방향으로 코드짜기
			Insert_Word();
			pause_old_time = pause_cur_time; // 패널티시간 일정하게 하기위함
		}

		if (clock() - move_time >= m_iSpeed && word_num != NULL)
		{
			for (int i = 0; i < num; i++) // 출력된것은 전부 움직이게 하기
			{
				Drop_Word(w, printed_word[i]);
			}
			move_time = clock();

			BLUE
			Ui.LittleBox(WIDTH, HEIGHT * 0.7, WIDTH * 0.3, HEIGHT * 0.15);

			if (m_iTmpWord.length() != 0)  // 입력창 깜박이는것 방지
			Ui.DrawMidText(m_iTmpWord, WIDTH, HEIGHT * 0.75);
		}

		if (cur_time - old_time >= m_iCreate_Speed)
		{
			printed_word[num] = Draw_Word(w, printed_word[num]); // 단어 출력
			word_num++; // 단어 갯수
			num++;
			old_time = cur_time;
		}

		if (clock() - warning_time >= 25 && m_iPause == TRUE)
		{
			RED
				Ui.DrawMidText("Miss [채팅잠금]", WIDTH, HEIGHT * 0.75);
			BLUE
				warning_time = clock();
		}

		if (m_iPause == TRUE && pause_cur_time - pause_old_time >= 2000) // 패널티시간
		{
			pause_old_time = pause_cur_time;
			m_iPause = FALSE;
		}
	}
}

void Play::Correct_Word() // 단어 맞추면 점수가 오른다
{
	int num = 0;

	for (int i = 0; i < WARD_MAX; i++)
	{
		if (m_iWord == w[i].name)
		{
			if (w[i].status == TRUE)
			{
				num = w[i].name.length(); // 단어 길이 저장

				Ui.gotoxy(w[i].x, w[i].y);
				Ui.EraseWord(num);
				w[i].status = FALSE;
				m_iScore += 153 * (m_iStage * 0.5);
				return;
			}
		}
	}
	m_iPause = TRUE; // 정지 패널티
}

void Play::Playing()
{
	char buf[256];
	sprintf_s(buf, "★ %d Stage ★", m_iStage);

	PLUM
	Ui.BoxDraw(0, 0, WIDTH, HEIGHT);
	BLUE
	Ui.DrawMidText(buf, WIDTH, HEIGHT * 0.4);
	Life_Name();

	Sleep(2000);
	system("cls");
	Ui.Game_Screen();
	Life_Name();
	Draw_Drop(); //단어 그리고 떨어지는함수
}

Play::~Play()
{
	if (w != NULL)
	{
		delete[] w;
	}
	w = NULL;
}