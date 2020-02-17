#pragma once
#include"School.h"
#include"Person.h"
class Student : public School, public Person
{
public:
	void SetStudent();
	void ShowStudent();
	Student();
	~Student();
};

