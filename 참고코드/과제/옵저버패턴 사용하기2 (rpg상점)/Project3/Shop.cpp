#include "Shop.h"



Shop::Shop()
{
	tmp_page1 = NULL;
	tmp_page2 = NULL;
	tmp_page3 = NULL;
	Dagger = NULL;
	Gun = NULL;
	Sword = NULL;
	Wand = NULL;
	Bow = NULL;
	Hammer = NULL;
	m_buy_wp_name = {};
	m_my_time = clock();
}

int Shop::Shop_MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
{
	int Select = 1;
	RED
		Draw_Gotoxy.DrawPoint("��", x, y);
	ORIGINAL
		m_my_time = clock();
		while (1)
		{
			if (clock() - m_my_time >= WEAPON_RESPAWN_TIME && m_buy_wp_name.size() != 0) // ���� ������Ʈ�� �ʿ��ϴ�
			{
				m_buy_wp_name = {};
				Draw_Gotoxy.gotoxy(0, 30);
				RED
					Notify(); // ��ü�鿡�� �ҽ��� �˷��ش�
				_getch();
				ORIGINAL
					Select += 99;
				return Select;
			}
			switch (_getch())
			{
			case UP:
				if (Select - 1 >= 1)
				{
					Draw_Gotoxy.ErasePoint(x, y);
					y -= AddCol;
					Select--;
				}
				break;
			case DOWN:
				if (Select + 1 <= MenuLen)
				{
					Draw_Gotoxy.ErasePoint(x, y);
					y += AddCol;
					Select++;
				}
				break;
			case ENTER:
				return Select;
			}
			RED
				Draw_Gotoxy.DrawPoint("��", x, y);
			ORIGINAL
		}
}

int Shop::Create_Weapon(string name)
{
	int j = 0;

	for (int i = 0; i < MAX_WEAPON; i++)
	{
		if (wp[i].weapon_type == name)
		{
			j++;
		}
	}
	return j;
}

void Shop::Create_Weapon2(string name, Weapon_Info *wp_name)
{
	int j = 0;

	for (int i = 0; i < MAX_WEAPON; i++)
	{
		if (wp[i].weapon_type == name)
		{
			wp_name[j].weapon_type = wp[i].weapon_type;
			wp_name[j].weapon_name = wp[i].weapon_name;
			wp_name[j].weapon_dmg = wp[i].weapon_dmg;
			wp_name[j].weapon_price = wp[i].weapon_price;
			j++;
		}
	}
	wp_name->weapon_max_count = j;
}

void Shop::Init_Weapon()
{
	int i = 0;
	int num = 0;

	Init(wp);
	wp = new Weapon_Info[MAX_WEAPON];

	ifstream load;
	load.open("WeaponList.txt");

	while (!load.eof())
	{
		load >> wp[i].weapon_type;
		load >> wp[i].weapon_name;
		load >> wp[i].weapon_dmg;
		load >> wp[i].weapon_price;

		i++; // ��������
	}

	load.close();

	if (tmp_page1 != NULL)
	{
		delete[] tmp_page1;
	}
	tmp_page1 = new Weapon_Info[MAX_WEAPON];
	if (tmp_page2 != NULL)
	{
		delete[] tmp_page2;
	}
	tmp_page2 = new Weapon_Info[MAX_WEAPON];
	if (tmp_page3 != NULL)
	{
		delete[] tmp_page3;
	}
	tmp_page3 = new Weapon_Info[MAX_WEAPON];

	////////////////
	if (Dagger != NULL)
	{
		delete[] Dagger;
	}
	if (Gun != NULL)
	{
		delete[] Gun;
	}
	if (Sword != NULL)
	{
		delete[] Sword;
	}
	if (Wand != NULL)
	{
		delete[] Wand;
	}
	if (Bow != NULL)
	{
		delete[] Bow;
	}
	if (Hammer != NULL)
	{
		delete[] Hammer;
	}
	/////////////////////

	num = Create_Weapon("Dagger");
	Dagger = new Weapon_Info[num];
	Create_Weapon2("Dagger", Dagger);

	num = Create_Weapon("Gun");
	Gun = new Weapon_Info[num];
	Create_Weapon2("Gun", Gun);

	num = Create_Weapon("Sword");
	Sword = new Weapon_Info[num];
	Create_Weapon2("Sword", Sword);

	num = Create_Weapon("Wand");
	Wand = new Weapon_Info[num];
	Create_Weapon2("Wand", Wand);

	num = Create_Weapon("Bow");
	Bow = new Weapon_Info[num];
	Create_Weapon2("Bow", Bow);

	num = Create_Weapon("Hammer");
	Hammer = new Weapon_Info[num];
	Create_Weapon2("Hammer", Hammer);
}

void Shop::Weapon_Show(Weapon_Info *wp_name, int ht1, int ht2, int num)
{
	int n = 0;


	YELLOW
	while (n != num) // �ش繫���� ���κб���
	{
		if (m_buy_wp_name != wp_name[n].weapon_name) // ������ ���⸦ ���̰� �����ʰ� �ϱ����ؼ�
		{
			Draw_Gotoxy.gotoxy(WIDTH * 0.55, HEIGHT * 0.07 + ht1);
			cout << "���� : " << wp_name[n].weapon_price << " ����Ÿ�� : " << wp_name[n].weapon_type;
			Draw_Gotoxy.gotoxy(WIDTH * 0.44, HEIGHT * 0.07 + ht2);
			cout << "�����̸� : " << wp_name[n].weapon_name << " ���ݷ� : " << wp_name[n].weapon_dmg;
		}
			ht1 += 3;
			ht2 += 3;
			n++; // ���� ����

	}

	ORIGINAL
	Draw_Gotoxy.gotoxy(WIDTH * 0.84, HEIGHT * 0.07 + ht1);
	cout << "����������";
	Draw_Gotoxy.gotoxy(WIDTH * 0.84, HEIGHT * 0.07 + ht2 + 2);
	cout << "����������";
	Draw_Gotoxy.gotoxy(WIDTH * 0.9, HEIGHT * 0.07 + ht2 + 5);
	cout << "������";
}

int Shop::Buy_Weapon(Weapon_Info *wp_name, Character_Info *cr_name, int select_menu, int page)
{
	if (select_menu <= page)
	{
		if (cr_name->gold >= wp_name[select_menu - 1].weapon_price)
		{
			cr_name->cr_weapon_type = wp_name[select_menu - 1].weapon_type;
			cr_name->cr_weapon_name = wp_name[select_menu - 1].weapon_name;
			cr_name->cr_weapon_dmg = wp_name[select_menu - 1].weapon_dmg;
			cr_name->gold -= wp_name[select_menu - 1].weapon_price;

			m_buy_wp_name = wp_name[select_menu - 1].weapon_name; // ������ �̸� ����
		}

	}
	else if (select_menu == page + 1)
	{
		return 0;
	}
	else if (select_menu == page + 2)
	{
		return 1;
	}
	else if (select_menu == page + 3)
	{
		return 2;
	}
}

void Shop::Weapon_Shop(Weapon_Info *wp_name, Character_Info *cr_name)
{
	int select = 0;

	int height1 = 4;
	int height2 = 5;

	int page1_max = 0;
	int page2_max = 0;
	int page3_max = 0;

	int trigger = FALSE;
	int p_trigger = FALSE;


	while (trigger != 2)
	{
		system("cls");
		BLUE
		Draw_Gotoxy.BoxDraw(0, 0, WIDTH, HEIGHT);
		ORIGINAL
		Draw_Gotoxy.gotoxy(WIDTH * 0.78, HEIGHT * 0.07);
		cout << "���� Gold : " << cr_name->gold;
		Draw_Gotoxy.gotoxy(WIDTH * 0.8, HEIGHT * 0.07 + 2);
		cout << wp_name->weapon_type << " Shop";

		///// wp_name�� �ִ빫�ⰹ���� ���� ���� -> �ݺ������� �� page�� ������ �ִ밹�� üũ�ϰ� break;

		for (int i = 0, j = 0, k = 0; i < wp_name->weapon_max_count;) //// ���������� ������ ����
		{
			if (i + j + k == wp_name->weapon_max_count)
			{
				break;
			}
			if (i >= 0 && i <= 4)
			{
				tmp_page1[i].weapon_dmg = wp_name[i].weapon_dmg;
				tmp_page1[i].weapon_name = wp_name[i].weapon_name;
				tmp_page1[i].weapon_price = wp_name[i].weapon_price;
				tmp_page1[i].weapon_type = wp_name[i].weapon_type;
				i++;
				page1_max = i;
			}
			else if (i >= 5 && i <= 9)
			{
				tmp_page2[j].weapon_dmg = wp_name[i].weapon_dmg;
				tmp_page2[j].weapon_name = wp_name[i].weapon_name;
				tmp_page2[j].weapon_price = wp_name[i].weapon_price;
				tmp_page2[j].weapon_type = wp_name[i].weapon_type;
				j++;
				page2_max = j;
			}
			else if (i >= 10 && i <= 14)
			{
				tmp_page3[k].weapon_dmg = wp_name[i].weapon_dmg;
				tmp_page3[k].weapon_name = wp_name[i].weapon_name;
				tmp_page3[k].weapon_price = wp_name[i].weapon_price;
				tmp_page3[k].weapon_type = wp_name[i].weapon_type;
				k++;
				page3_max = k;
			}

		}


		if (trigger == FALSE)
		{
			Weapon_Show(tmp_page1, height1, height2, page1_max); // 1������
			select = Shop_MenuSelectCursor(page1_max + 3, 3, WIDTH * 0.2, HEIGHT * 0.1 + 3); // �޴� ����
			if (select == 100)
			{
				break;
			}
			trigger = Buy_Weapon(tmp_page1, cr_name, select, page1_max);
		}
		else if (trigger == TRUE && p_trigger == FALSE) // p_trigger�� 3�������� ���� ������
		{
			Weapon_Show(tmp_page2, height1, height2, page2_max); // 2������
			select = Shop_MenuSelectCursor(page2_max + 3, 3, WIDTH * 0.2, HEIGHT * 0.1 + 3); // �޴� ����
			if (select == 100)
			{
				break;
			}
			trigger = Buy_Weapon(tmp_page2, cr_name, select, page2_max);
			if (trigger == TRUE)
			{
				p_trigger = TRUE;
			}
		}
		else if (trigger == TRUE && p_trigger == TRUE)
		{
			Weapon_Show(tmp_page3, height1, height2, page3_max); // 3������
			select = Shop_MenuSelectCursor(page3_max + 3, 3, WIDTH * 0.2, HEIGHT * 0.1 + 3); // �޴� ����
			if (select == 100)
			{
				break;
			}
			trigger = Buy_Weapon(tmp_page3, cr_name, select, page3_max);
			if (trigger == FALSE)
			{
				trigger = TRUE;
				p_trigger = FALSE;
			}
		}
		else // ���⸦ ������� ùȭ������ ���ư���
		{
			trigger = FALSE;
		}

	}

}

void Shop::Show_Shop(Character_Info *name)
{
	int select = 0;

	Add_Observer(&chr);
	m_my_time = clock();

	while (1)
	{
		BLUE
		Draw_Gotoxy.BoxDraw(0, 0, WIDTH, HEIGHT); // x������,y������,����,����
		ORIGINAL
		Draw_Gotoxy.DrawMidText("�� �� S H O P �� ��", WIDTH, HEIGHT * 0.3);
		Draw_Gotoxy.DrawMidText("Dagger", WIDTH, HEIGHT * 0.3 + 2);
		Draw_Gotoxy.DrawMidText("Gun", WIDTH, HEIGHT * 0.3 + 4);
		Draw_Gotoxy.DrawMidText("Sword", WIDTH, HEIGHT * 0.3 + 6);
		Draw_Gotoxy.DrawMidText("Wand", WIDTH, HEIGHT * 0.3 + 8);
		Draw_Gotoxy.DrawMidText("Bow", WIDTH, HEIGHT * 0.3 + 10);
		Draw_Gotoxy.DrawMidText("Hammer", WIDTH, HEIGHT * 0.3 + 12);
		Draw_Gotoxy.DrawMidText("���ư���", WIDTH, HEIGHT * 0.3 + 14);

		select = Shop_MenuSelectCursor(SHOP_MENU_COUNT, 2, WIDTH * 0.37, HEIGHT * 0.3 + 2);

		if (select == 1)
		{
			Weapon_Shop(Dagger, name);
		}
		else if (select == 2)
		{
			Weapon_Shop(Gun, name);
		}
		else if (select == 3)
		{
			Weapon_Shop(Sword, name);
		}
		else if (select == 4)
		{
			Weapon_Shop(Wand, name);
		}
		else if (select == 5)
		{
			Weapon_Shop(Bow, name);
		}
		else if (select == 6)
		{
			Weapon_Shop(Hammer, name);
		}
		else if (select == 7)
		{
			return;
		}
	}
}

void Shop::Add_Observer(Observer* ob)
{
	observerList.push_back(ob); // �˸����� ��ü ����
}

void Shop::Notify()
{
	for (auto iter = observerList.begin(); iter != observerList.end(); iter++)
	{
		(*iter)->Update(); // �������� ��ϵ� ��ü�鿡�� ������Ʈ ���ش�
	}
}

Shop::~Shop()
{
	if (tmp_page1 != NULL)
	{
		delete[] tmp_page1;
		tmp_page1 = NULL;
	}
	if (tmp_page2 != NULL)
	{
		delete[] tmp_page2;
		tmp_page2 = NULL;
	}
	if (tmp_page3 != NULL)
	{
		delete[] tmp_page3;
		tmp_page3 = NULL;
	}


	if (Dagger != NULL)
	{
		delete[] Dagger;
		Dagger = NULL;
	}
	if (Gun != NULL)
	{
		delete[] Gun;
		Gun = NULL;
	}
	if (Sword != NULL)
	{
		delete[] Sword;
		Sword = NULL;
	}
	if (Wand != NULL)
	{
		delete[] Wand;
		Wand = NULL;
	}
	if (Bow != NULL)
	{
		delete[] Bow;
		Bow = NULL;
	}
	if (Hammer != NULL)
	{
		delete[] Hammer;
		Hammer = NULL;
	}
}
