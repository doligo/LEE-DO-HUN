#include "Login.h"

string Login::m_id_save = { 0 };
string Login::m_pw_save = { 0 };
int Login::m_icount = 0;
int Login::m_login_check = FALSE;

Login::Login()
{
}

void Login::Release(Register_id *Node)
{
	if (Node == NULL)
	{
		return;
	}
	else
	{
		Release(Node->m_pNext);
		delete Node;
	}
}

bool Login::Id_Check(string str, Register_id *Node1, Register_id *Node4)
{
	Node4 = Node1; // m_idcheck = 4 , create = 1

	for (int i = 0; i <= m_icount; i++)
	{
		if (str == Node4->id)
		{
			return false;
		}
		else
		{
			if (Node4->m_pNext != NULL)
			{
				Node4 = Node4->m_pNext;
			}
		}
	}

	return true;
}

bool Login::korean_check(string str) // �ѱ��� üũ
{
	int count = 0;

	while (str[count] != NULL)
	{
		count++;
	}

	for (int i = 0; i < count;)
	{
		if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
		{
			i++;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Login::number_check(string str) //��ȣ üũ
{
	int count = 0;

	while (str[count] != NULL)
	{
		count++;
	}

	for (int i = 0; i < count;)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			return true;
		}
		else
		{
			i++;
		}
	}

	return false;
}

bool Login::pw_correct_check(string str1, string str2)
{
	int count = 0;

	if (str1.length() != str2.length())
	{
		return false;
	}

	while (str1[count] != NULL)
	{
		count++;
	}

	for (int i = 0; i < count;)
	{
		if (str1[i] == str2[i])
		{
			i++;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Login::pw_login_check(string str1, string str2, Register_id *Node1, Register_id *Node4)
{
	Node4 = Node1;

	for (int i = 0; i <= m_icount; i++)
	{
		if (str1 == Node4->id)
		{
			if (str2 == Node4->pw)
			{
				return true;
			}
			else
			{
				if (Node4->m_pNext != NULL)
				{
					Node4 = Node4->m_pNext;
				}
			}
		}
		else
		{
			if (Node4->m_pNext != NULL)
			{
				Node4 = Node4->m_pNext;
			}
		}
	}
	return false;
}

void Login::Show_Computer()
{
	system("cls");
	cout << "�� ǰ �� : �̵��� ��ǻ��" << endl;
	cout << "���� ���� : On" << endl;
	cout << "�׷��� ī�� : GTX2080TI" << endl;
	cout << "C P U : I9" << endl;
	cout << "�޸� 64G" << endl;
	system("pause");
}

void Login::Change_Login_Status(int num)
{
	m_login_check = num;
}

Login::~Login()
{
}
