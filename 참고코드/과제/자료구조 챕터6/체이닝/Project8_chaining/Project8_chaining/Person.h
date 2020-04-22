#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
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
private:
public:
	Person();

	int GetSSN(PersonS *p);
	void ShowPerInfo(PersonS *p);
	PersonS *MakePersonData(int ssn, const char * name, const char * addr);

	~Person();
};

