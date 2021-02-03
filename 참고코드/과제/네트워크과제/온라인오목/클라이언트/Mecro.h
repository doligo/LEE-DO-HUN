#pragma once
#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <process.h>
#include<iostream>
#include<string>
#include<conio.h>
#include<iomanip>
#include<Windows.h>
using namespace std;

#define WIDTH 20
#define HEIGHT 20

enum KEY
{
	KEY_LEFT = 'a',
	KEY_RIGHT = 'd',
	KEY_UP = 'w',
	KEY_DOWN = 's',
	KEY_ESC = 27,
	KEY_DROP = 13,
	KEY_UNDO = 'n',
	KEY_OPTION = 'p'
};