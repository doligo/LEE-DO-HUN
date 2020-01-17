#include "Computer.h"

int Computer::exit = FALSE;

Computer::Computer()
{
	create_com = NULL;
	m_create_next_com = NULL;
}


void Computer::User_Search()
{
	m_idcheck_com = create_com;

	for (int i = 0; i < m_icount; i++)
	{
		if (m_id_save == m_idcheck_com->id)
		{
			m_tmp_com = m_idcheck_com;
			break;
		}
		else
		{
			if (m_idcheck_com->m_pNext != NULL)
			{
				m_idcheck_com = m_idcheck_com->m_pNext;
			}
		}
	}
}

void Computer::User_Info()
{
	User_Search();
	system("cls");
	cout << "============ȸ�� ����============" << endl;
	cout << "ID : " << m_tmp_com->id << "     �г��� : " << m_tmp_com->nick_name << endl;
	cout << "���� : " << m_tmp_com->age << "��" << "     �޴�����ȣ : " << m_tmp_com->phone << endl;
	cout << "���ϸ��� : " << m_tmp_com->money << "��" << endl;
	system("pause");
}

void Computer::User_Info_Change()
{
	int select = 0;

	string change_nick = { 0 };
	string change_phone = { 0 };
	int change_age = 0;

	string ex_value = { 0 };
	int ex_value2 = 0;

	while (1)
	{
		User_Search();
		system("cls");
		cout << "============ȸ�� ����============" << endl;
		cout << "ID : " << m_tmp_com->id << "     �г��� : " << m_tmp_com->nick_name << endl;
		cout << "���� : " << m_tmp_com->age << "��" << "     �޴�����ȣ : " << m_tmp_com->phone << endl;
		cout << "���ϸ��� : " << m_tmp_com->money << "��" << endl;
		cout << "=================================" << endl;
		cout << "1.�г��� ����" << endl;
		cout << "2.���� ����" << endl;
		cout << "3.�޴��� ����" << endl;
		cout << "4.���ư���" << endl;
		cout << "�Է� : ";
		cin >> select;
		switch (select)
		{
		case 1:
			cout << "���� �г��� : " << m_tmp_com->nick_name << endl;
			ex_value = m_tmp_com->nick_name;
			cout << "������ �г��� �Է� : ";
			cin >> change_nick;
			m_tmp_com->nick_name = change_nick;
			cout << ex_value << " -> " << m_tmp_com->nick_name;
			break;
		case 2:
			cout << "���� ���� : " << m_tmp_com->age << endl;
			ex_value2 = m_tmp_com->age;
			cout << "������ ���� �Է� : ";
			cin >> change_age;
			m_tmp_com->age = change_age;
			cout << ex_value2 << " -> " << m_tmp_com->age;
			break;
		case 3:
			cout << "���� ��ȣ : " << m_tmp_com->phone << endl;
			ex_value = m_tmp_com->phone;
			cout << "������ ��ȣ �Է� : ";
			cin >> change_phone;
			m_tmp_com->phone = change_phone;
			cout << ex_value << " -> " << m_tmp_com->phone;
			break;
		case 4:
			return;
		}
	}

}

void Computer::Util()
{
	int select = 0;
	
	while (1)
	{
		system("cls");
		cout << "1.�� �� ��" << endl;
		cout << "2.�� �� ��" << endl;
		cout << "3.�� �� ��" << endl;
		cout << "4.���� ����" << endl;
		cout << "���� >>>> ";
		cin >> select;
		switch (select)
		{
		case 1:
			system("calc");
			break;
		case 2:
			system("notepad");
			break;
		case 3:
			system("mspaint");
			break;
		case 4:
			return;
		}
	}
}

void Computer::Register()
{
	int id_complete = FALSE;
	int pw_complete = FALSE;


	if (create_com == NULL)
	{
		create_com = new Register_id; // ù �����϶��� create�� ����.
		m_tmp_com = create_com;
	}
	else if (create_com != NULL)
	{
		m_create_next_com = new Register_id;
		m_tmp_com = m_create_next_com;
	}

	while (id_complete != TRUE)
	{
		id_complete = TRUE;
		system("cls");
		cout << "���̵� �Է� (3���� �̻�, �ѱ��� �ȉ�) : ";
		cin >> m_tmp_com->id;
		if (m_icount != FALSE) // ���̵� �Ѱ� �̻� ������� �����϶��� ����ȴ�.
		{
			if (Id_Check(m_tmp_com->id, create_com, m_idcheck_com) == false)
			{
				cout << "�ߺ��� ���̵� �Դϴ�." << endl;
				_getch();
				id_complete = FALSE;
			}
		}
		if (m_tmp_com->id.length() < 3)
		{
			cout << "���̵� ������ �����Դϴ�." << endl;
			_getch();
			id_complete = FALSE;
		}
		if (korean_check(m_tmp_com->id) == false)
		{
			cout << "���̵� �ѱ��� ��� �� �� �����ϴ�." << endl;
			_getch();
			id_complete = FALSE;
		}
	}

	while (pw_complete != TRUE)
	{
		pw_complete = TRUE;
		system("cls");
		cout << "��й�ȣ �Է� (8���� �̻�, ������ ��������) : ";
		cin >> m_tmp_com->pw;
		cout << "��й�ȣ Ȯ�� : ";
		cin >> m_tmp_com->pw_check;

		if (m_tmp_com->pw.length() < 8)
		{
			cout << "��й�ȣ�� �������� ���� �Դϴ�." << endl;
			_getch();
			pw_complete = FALSE;
		}
		if (korean_check(m_tmp_com->pw) == false || korean_check(m_tmp_com->pw_check) == false)
		{
			cout << "��й�ȣ�� ������ �ƴմϴ�." << endl;
			_getch();
			pw_complete = FALSE;
		}
		if (number_check(m_tmp_com->pw) == false)
		{
			cout << "���ڰ� ���ԵǾ� ���� �ʽ��ϴ�." << endl;
			_getch();
			pw_complete = FALSE;
		}
		if (pw_correct_check(m_tmp_com->pw, m_tmp_com->pw_check) == false)
		{
			cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
			_getch();
			pw_complete = FALSE;
		}
	}
	system("cls");
	cout << "�г��� �Է� : ";
	cin >> m_tmp_com->nick_name;
	cout << "���� �Է� : ";
	cin >> m_tmp_com->age;
	cout << "�޴��� ��ȣ �Է� : ";
	cin >> m_tmp_com->phone;
	m_tmp_com->money = 1000;
	m_icount++;
	m_tmp_com->m_pNext = NULL;

	cout << "ȸ������ ����!! ���ϸ��� 1000�� ���" << endl;


	if (m_create_next_com != NULL)
	{
		m_tmp_com = create_com;
		while (m_tmp_com->m_pNext != NULL)
		{
			m_tmp_com = m_tmp_com->m_pNext;
		}
		m_tmp_com->m_pNext = m_create_next_com;
	}

	system("pause");
}

void Computer::Go_Login()
{
	string tmp_id = { 0 };
	string tmp_pw = { 0 };
	int trigger = FALSE;

	while (trigger != TRUE)
	{
		trigger = TRUE;
		system("cls");
		cout << "���̵� �Է� : ";
		cin >> tmp_id;
		cout << "��й�ȣ �Է� : ";
		cin >> tmp_pw;
		if (Id_Check(tmp_id, create_com, m_idcheck_com) == true)
		{
			cout << "���̵� �����ϴ�." << endl;
			trigger = FALSE;
			_getch();
		}
		if (pw_login_check(tmp_id, tmp_pw, create_com, m_idcheck_com) == false)
		{
			cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl;
			trigger = FALSE;
			_getch();
		}
		m_login_check = TRUE; // �α��� ����
	}
	m_id_save = tmp_id;
	m_pw_save = tmp_pw;
	cout << "�̵��� ��ǻ�� ON" << endl;
	Sleep(4000);

}

void Computer::Menu()
{
	int num = 0;

	while (m_login_check != TRUE)
	{
		system("cls");
		cout << "=====Login=====<ȸ����[" << m_icount << "��]>" << endl;
		cout << "    1.ȸ�� ����" << endl;
		cout << "    2.�α���" << endl;
		cout << "    3.����" << endl;
		cout << "�Է� : ";
		cin >> num;
		switch (num)
		{
		case 1:
			Register();
			break;
		case 2:
			if (create_com == NULL)
			{
				cout << "ȸ������ ���� ���ּ��� !" << endl;
				system("pause");
			}
			else
			{
				Go_Login();
			}
			break;
		case 3:
			exit = TRUE;
			return;
		}
	}
}

void Computer::Menu2()
{
	int select = 0;

	while (1)
	{
		system("cls");
		cout << "===== ȯ �� �� �� �� =====" << endl;
		cout << "1.��ǻ�� ����" << endl;
		cout << "2.�� ��" << endl;
		cout << "3.ȸ�� ����" << endl;
		cout << "4.ȸ�� ���� ����" << endl;
		cout << "5.OFF" << endl;
		cout << "�Է� >> ";
		cin >> select;
		switch (select)
		{
		case 1:
			Show_Computer();
			break;
		case 2:
			Util();
			break;
		case 3:
			User_Info();
			break;
		case 4:
			User_Info_Change();
			break;
		case 5:
			for (int i = 5; i > 0; i--)
			{
				cout << "���� " << i << "�� ��" << endl;
				Sleep(1000);
			}
			return;
		}
	}
}


Computer::~Computer()
{
	m_tmp_com = create_com;
	if (m_tmp_com == NULL)
	{
		return;
	}
	else
	{
		Release(m_tmp_com);
		delete m_tmp_com;
		m_tmp_com = NULL;
	}
}
