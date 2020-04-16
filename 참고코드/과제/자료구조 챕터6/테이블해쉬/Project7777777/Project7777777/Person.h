#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#pragma once
using namespace std;

#define STR_LEN 50

struct PersonS
{
	int ssn;
	char name[STR_LEN];
	char addr[STR_LEN];
};

class Person
{
public:
	Person();

	int GetSSN(PersonS *p);
	void ShowPerInfo(PersonS *p);
	PersonS *MakePersonData(int ssn, char *name, char *addr);

	~Person();
};

