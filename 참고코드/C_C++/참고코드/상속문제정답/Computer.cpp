#include "Computer.h"



Computer::Computer()
{
	m_strName = "최정호 컴퓨터";
	m_strGraphic = "GTX1060Ti";
	m_bOnOff = false;
	m_iRam = 16;
	m_strCpu = "I7";
}


void Computer::Computerdisplay()
{
	int Select;
	cout << "최정호 컴퓨터 on" << endl;
	Sleep(3000);
	system("cls");
	while (true) {
		cout << "===== 환 영 합 니 다 =====" << endl;
		cout << "1.컴퓨터 상태" << endl;
		cout << "2.기 능" << endl;
		cout << "3.회원 정보" << endl;
		cout << "4.회원 정보 변경" << endl;
		cout << "5.off" << endl;
		cout << "입력 >> ";
		cin >> Select;
		switch (Select) {
		case 1:
			condition();
			break;
		case 2:
			function();
			break;
		case 3:
			Login::ShowID();
			break;
		case 4:
			Login::SetID();
			break;
		case 5:
			for (int i = 5; i > 0; i--)
			{
				cout << "off " << i << " 초전" << endl;
				Sleep(1000);
			}
			return;
		}
		system("pause");
		system("cls");
	}
}

void Computer::condition()
{
	system("cls");
	cout << "제 품 명 : " << m_strName << endl;
	cout << "현재 상태 : ";
	if(m_bOnOff)	
		cout << "On " << endl;
	else
		cout << "Off " << endl;
	cout << "그래픽카드 : " << m_strGraphic << endl;
	cout << "C P U : " << m_strCpu << endl;
	cout << "메 모 리 : " << m_iRam << "G" << endl;
}

void Computer::function()
{
	int i;
	system("cls");
	while (true) {
		cout << "1.계 산 기" << endl;
		cout << "2.메 모 장" << endl;
		cout << "3.그 림 판" << endl;
		cout << "4.돌아가기" << endl;
		cout << "선택 >>>>"; cin >> i;
		switch (i) {
		case 1:
			system("calc");
			break;
		case 2:
			system("notepad");
			break;
		case 3:
			system("mspaint");
			break;
		default:
			return;
		}
		system("pause"); system("cls");
	}
}

Computer::~Computer()
{
}
