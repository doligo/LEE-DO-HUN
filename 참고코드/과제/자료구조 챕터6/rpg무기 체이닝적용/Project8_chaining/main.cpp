#include "Table.h"

int MyHashFunc(int n)
{
	return n % 100;
}

void Show_Weapon_All(TableS *tbs, int num)
{
	Table TB;
	Weapon WP;
	Slot tmp_slot;

	system("cls");

	if (TB.LFirst(&tbs->tbl[num], &tmp_slot) == TRUE)
	{
		WP.ShowWeaponInfo(tmp_slot.val);
	}
	while (TB.LNext(&tbs->tbl[num], &tmp_slot) == TRUE)
	{
		WP.ShowWeaponInfo(tmp_slot.val);
	}

	system("pause");
}

int main()
{
	Table TB;
	Weapon WP;

	TableS tbs;
	WeaponS *wps;
	WeaponS *wps_delete;
	ifstream read;

	int tmp_hsn = 0;
	int tmp_dam = 0;
	int tmp_price = 0;
	char tmp_type[STR_LEN] = {};
	char tmp_name[STR_LEN] = {};
	
	int select = 0;
	int num = 0;

	TB.TBLInit(&tbs, MyHashFunc);
	read.open("WeaponList.txt");

	if (!read)
	{
		cout << "������ ���������ʽ��ϴ�" << endl;
		return 0;
	}
	else
	{
		while (!read.eof())
		{
			read >> tmp_type;

			if (strcmp(tmp_type, "Bow") == 0)
				tmp_hsn = 1051;
			else if (strcmp(tmp_type, "Dagger") == 0)
				tmp_hsn = 1052;
			else if (strcmp(tmp_type, "Gun") == 0)
				tmp_hsn = 1053;
			else if (strcmp(tmp_type, "Sword") == 0)
				tmp_hsn = 1054;
			else if (strcmp(tmp_type, "Wand") == 0)
				tmp_hsn = 1055;
			else if (strcmp(tmp_type, "Hammer") == 0)
				tmp_hsn = 1056;

			read >> tmp_name;
			read >> tmp_dam;
			read >> tmp_price;

			wps = WP.MakeWeaponData(tmp_type, tmp_name, tmp_dam, tmp_price, tmp_hsn);
			TB.TBLInsert(&tbs, tmp_hsn, wps);
		}

	}

	read.close();

	while (1)
	{
		system("cls");
		cout << "<�޴�>" << endl;
		cout << "1.������ ����" << endl;
		cout << "2.������� �ϱ�" << endl;
		cout << "3.����" << endl;
		cout << "�Է� : ";
		cin >> select;
		switch (select)
		{
		case 1:
			system("cls");
			cout << "�ݡݺ������ �������� �Է��ϼ��� (������ �Է�)�ݡ�" << endl;
			cout << "Bow : 51, Dagger : 52, Gun : 53, Sword : 54, Wand : 55, Hammer : 56" << endl;
			cout << "�Է� : ";
			cin >> num;
			if (num >= 51 && num <= 56)
				Show_Weapon_All(&tbs, num);
			else
			{
				cout << "�߸��Է� �߽��ϴ�" << endl;
				system("pause");
			}
			break;
		case 2:
			system("cls");
			cout << "�ݡݻ����ϰ���� �������� �Է��ϼ��� (������ �Է�)�ݡ�" << endl;
			cout << "Bow : 51, Dagger : 52, Gun : 53, Sword : 54, Wand : 55, Hammer : 56" << endl;
			cout << "�Է� : ";
			cin >> num;
			if (num >= 51 && num <= 56)
			{
				wps_delete = TB.TBLDelete(&tbs, num + 1000);
				if (wps_delete != NULL)
					free(wps_delete);
				cout << "������ ������ �� �����ֱٿ� �߰��� ���⸦ �����Ͽ����ϴ�" << endl;
				system("pause");
			}
			else
			{
				cout << "�߸��Է� �߽��ϴ�" << endl;
				system("pause");
			}
			break;
		case 3:
			return 0;
		}
	}



	return 0;
}