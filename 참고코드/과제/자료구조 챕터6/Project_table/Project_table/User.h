#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#pragma once
using namespace std;

#define STR_LEN 50

struct User_Info
{
	int phone_num;
	char name[STR_LEN];
	char addr[STR_LEN];
};

int GetSSN(User_Info *u);
void ShowPerInfo(User_Info *u);
User_Info *MakePersonData(int phone_num, char *name, char *addr);