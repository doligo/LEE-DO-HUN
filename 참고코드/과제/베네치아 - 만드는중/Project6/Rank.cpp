#include "Rank.h"

Rank::Rank()
{
	count = NULL;
}

int Rank::Count_Rank()
{
	ifstream Load;
	int i = 0;

	if (count != NULL)
	{
		delete[] count;
	}
	count = new Ranking[COUNT_MAX];

	Load.open("Rank.txt");
	if (!Load)
	{
		system("cls");
		cout << "해당 파일이 없습니다" << endl;
		_getch();
	}
	else
	{
		while (!Load.eof())
		{
			Load >> count[i].name;
			if (count[i].name.length() == NULL)
			{
				return i;
			}
			Load >> count[i].stage;
			Load >> count[i].total_score;
			i++;
		}
	}
	Load.close();

	return i;
}

void Rank::Load_Rank(Ranking *name)
{
	ifstream Load;
	int i = 0;

	Load.open("Rank.txt");
	if (!Load)
	{
		system("cls");
		cout << "해당 파일이 없습니다" << endl;
		_getch();
	}
	else
	{
		while (!Load.eof())
		{
			Load >> name[i].name;
			Load >> name[i].stage;
			Load >> name[i].total_score;
			i++;
		}
	}
	Load.close();

}

Rank::~Rank()
{
	if (count != NULL)
	{
		delete[] count; // 해제
	}
}