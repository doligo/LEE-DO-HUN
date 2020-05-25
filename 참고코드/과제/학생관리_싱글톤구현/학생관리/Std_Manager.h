#pragma once
#include "Student.h"

#define S_MAX 30

// ΩÃ±€≈Ê∏∏ ≈€«√∏¥»≠ «œ±‚
template <typename T>
class Std_manager
{
	Student* std[S_MAX];

	static T *m_stmanager;

public:

	static T *GetInstance()
	{
		if (m_stmanager == NULL)
			m_stmanager = new T;

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
