#pragma once
#include "Student.h"

#define S_MAX 30

// ΩÃ±€≈Ê∏∏ ≈€«√∏¥»≠ «œ±‚
class Std_manager 
{
	Student* std[S_MAX];

	static Std_manager *m_stmanager;
public:
	static Std_manager *GetInstance()
	{
		if (m_stmanager == NULL)
			m_stmanager = new Std_manager;

		return m_stmanager;
	}

	Std_manager();

	void display();
	void setStudent();
	void showStudent();
	void findNumber();
	void findname();
	void findClass();

	~Std_manager()
	{
		for (int i = 0; i < 30; i++)
		{
			delete std[i];
		}
	}

};

