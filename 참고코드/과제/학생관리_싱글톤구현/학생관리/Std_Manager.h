#pragma once
#include "Student.h"

#define S_MAX 30

template <typename T>
class Std_manager 
{
	T* std[S_MAX];

	static T *m_stmanager;
public:
	static T *GetInstance()
	{
		if (m_stmanager == NULL)
			m_stmanager = new T;

		return m_stmanager;
	}

	Std_manager();

	T display();
	T setStudent();
	T showStudent();
	T findNumber();
	T findname();
	T findClass();

	~Std_manager()
	{
		for (int i = 0; i < 30; i++)
		{
			delete std[i];
		}
	}

};

