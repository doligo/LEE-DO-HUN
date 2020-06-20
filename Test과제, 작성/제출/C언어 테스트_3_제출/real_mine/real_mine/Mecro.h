#pragma once
#include<iostream>
#include<string>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<fstream>
using namespace std;

#define HEIGHT 30
#define WIDTH 30

#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
