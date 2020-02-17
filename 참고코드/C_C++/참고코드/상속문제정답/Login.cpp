#include "Login.h"



Login::Login()
{
	m_iIdCount = 0;
}
void Login::SimpleShowID()
{
	cout << "============회원 정보============" << endl;
	cout << "ID : " << m_Id_List[m_iCurIdIndex].m_strID << "   닉네임 : " << m_Id_List[m_iCurIdIndex].m_strName << endl;
}
void Login::ShowID()
{
	system("cls");
	SimpleShowID();
	cout << " 나이 : " << m_Id_List[m_iCurIdIndex].m_iAge << "살" << "   휴대폰 번호 : " << m_Id_List[m_iCurIdIndex].m_strPhonNumber << endl;
	cout << "마일리지 : " << m_Id_List[m_iCurIdIndex].m_iMileage << "원" << endl;
}

void Login::Setstring(string* str, string tmp)
{
	string tmpstr;
	tmpstr = *str;
	cout << "현재 " << tmp << ": " << tmpstr << endl;
	cout << "변경할 " << tmp << "입력 : ";
	cin >> *str;
	cout << tmpstr << " -> " << *str << endl;
	system("pause");
}

void Login::Setint(int* num, string tmp)
{
	int tmpint;
	tmpint = *num;
	cout << "현재 " << tmp << " : " << tmpint << endl;
	cout << "변경할 " << tmp << "입력 : ";
	cin >> *num;
	cout << tmpint << " -> " << *num << endl;
	system("pause");
}

void Login::SetID()
{
	int Select;
	while (1)
	{
		ShowID();
		cout << "===================" << endl;
		cout << "1.닉네임 변경" << endl;
		cout << "2.나이 변경" << endl;
		cout << "3.휴대폰 번호 변경" << endl;
		cout << "4.돌아가기" << endl;
		cout << "입력 : ";
		cin >> Select;
		switch (Select)
		{
		case 1:
			Setstring(&m_Id_List[m_iCurIdIndex].m_strName, "닉네임");
			break;
		case 2:
			Setint(&m_Id_List[m_iCurIdIndex].m_iAge, "나이");
			break;
		case 3:
			Setstring(&m_Id_List[m_iCurIdIndex].m_strPhonNumber, "휴대폰 번호");
			break;
		case 4:
			return;
		}
	}
}

bool Login::LoginDisplay()
{

	string TmpId, TmpPassword;
	int Select;
	bool Id_Flag, PasswordFlag, LoginFlag;
	while (1)
	{
		LoginFlag = false;
		system("cls");
		cout << "=====Login=====(회원수[" << m_iIdCount << "명])" << endl;
		cout << "   1.회원 가입" << endl;
		cout << "   2.로그인" << endl;
		cout << "   3.종료" << endl;
		cout << "입력 : ";
		cin >> Select;
		switch (Select)
		{
		case 1:
			if (m_iIdCount >= IDMAX)
			{
				cout << "더이상 회원을 등록할 수 없습니다." << endl;
				system("pause");
				break;
			}
			Join();
			break;
		case 2:
			while (!LoginFlag)
			{
				Id_Flag = false;
				PasswordFlag = false;
				system("cls");
				cout << "아이디 입력 : ";
				cin >> TmpId;
				cout << "비밀번호 입력 : ";
				cin >> TmpPassword;
				for (int i = 0; i < m_iIdCount; i++)
				{
					if (TmpId == m_Id_List[i].m_strID)
					{
						Id_Flag = true;
						if (TmpPassword == m_Id_List[i].m_strPassword)
						{
							PasswordFlag = true;
							LoginFlag = true;
							m_iCurIdIndex = i;
							return true;
						}
					}
				}
				if (!Id_Flag)
					cout << "해당 아이디가 없습니다." << endl;
				else if (!PasswordFlag)
					cout << "비밀번호가 틀렸습니다." << endl;
			}
			break;
		case 3:
			return false;
		}
	}
}
void Login::Join()
{
	bool Flag, Flag2, Flag3;
	int CountNum = 0;
	string CheckPassword;
	while (1)
	{
		Flag = true;
		Flag3 = true;
		system("cls");
		cout << "아이디 입력([3글자↑] AND [한글X]) : ";
		cin >> m_Id_List[m_iIdCount].m_strID;
		for (int i = 0; i < m_Id_List[m_iIdCount].m_strID.length(); i++)
		{
			if (m_Id_List[m_iIdCount].m_strID[i] <'A' || (m_Id_List[m_iIdCount].m_strID[i] > 'Z' && m_Id_List[m_iIdCount].m_strID[i] < 'a') || m_Id_List[m_iIdCount].m_strID[i] > 'z')
			{
				if (m_Id_List[m_iIdCount].m_strID[i] >= '0' &&m_Id_List[m_iIdCount].m_strID[i] <= '9')
					Flag = true;
				else
					Flag = false;
			}
		}
		for (int i = 0; i < m_iIdCount; i++)
		{
			if (i != m_iIdCount && m_Id_List[i].m_strID == m_Id_List[m_iIdCount].m_strID)
				Flag3 = false;
		}
		if (!Flag3)
		{
			cout << "동일한 아이디가 존재합니다." << endl;
			system("pause");
			continue;
		}
		if (Flag && m_Id_List[m_iIdCount].m_strID.length() >= IDLEN)
			break;
		if (!Flag)
			cout << "id가 영문이 아닙니다." << endl;
		if (m_Id_List[m_iIdCount].m_strID.length() < IDLEN)
			cout << "id가 세글자 이하 입니다." << endl;
		system("pause");
	}
	while (1)
	{
		Flag = true;
		Flag2 = true;
		system("cls");
		cout << "비밀번호 입력([8글자↑]AND[영문]AND[숫자 포함]) : ";
		cin >> m_Id_List[m_iIdCount].m_strPassword;
		for (int i = 0; i < m_Id_List[m_iIdCount].m_strPassword.length(); i++)
		{
			if (m_Id_List[m_iIdCount].m_strPassword[i] <'A' || (m_Id_List[m_iIdCount].m_strPassword[i] > 'Z' && m_Id_List[m_iIdCount].m_strPassword[i] < 'a') || m_Id_List[m_iIdCount].m_strPassword[i] > 'z')
			{
				if (m_Id_List[m_iIdCount].m_strPassword[i] >= '0' && m_Id_List[m_iIdCount].m_strPassword[i] <= '9')
					CountNum++;
				else
					Flag = false;
			}
		}
		cout << "비밀번호 확인 : ";
		cin >> CheckPassword;
		if (CheckPassword != m_Id_List[m_iIdCount].m_strPassword)
			Flag2 = false;
		if (Flag && Flag2 && m_Id_List[m_iIdCount].m_strPassword.length() >= PASSWORDLEN && CountNum >= 1)
			break;
		if (!Flag)
			cout << "password가 영문이 아닙니다." << endl;
		if (m_Id_List[m_iIdCount].m_strPassword.length() < PASSWORDLEN)
			cout << "Password가 여덟글자 이하 입니다." << endl;
		if (CountNum == 0)
			cout << "숫자가 포함되어 있지 않습니다." << endl;
		if (!Flag2)
			cout << "비밀번호가 일치하지 않습니다." << endl;
		system("pause");
	}
	system("cls");
	cout << "닉네임 입력 : ";
	cin >> m_Id_List[m_iIdCount].m_strName;
	cout << "나이 입력 :";
	cin >> m_Id_List[m_iIdCount].m_iAge;
	cout << "휴대폰 번호 입력 : ";
	cin >> m_Id_List[m_iIdCount].m_strPhonNumber;
	cout << "회원가입 성공 !! 마일리지 1000원 등록" << endl;
	m_Id_List[m_iIdCount].m_iMileage = 1000;
	m_iIdCount++;
	system("pause");
}

Login::~Login()
{

}
