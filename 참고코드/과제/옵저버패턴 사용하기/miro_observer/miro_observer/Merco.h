#pragma once
#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
//////////////////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//색상 지정
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
//////////////////////////////////////////////////////
#define WALL 1
#define NULL 0
#define Y 0
#define X 1
#define FLAG 2 // 문 스위치 온오프
#define ENTRY_MAX 18 //입구 갯수
#define EXIT_MAX 18 // 출구 갯수
#define CHARACTER 2
#define ENTRY_START 10
#define EXIT_START 30
#define DOOR_MAX 7 // 문 갯수
#define DOOR_START 60
#define SWITCH_MAX 7// 스위치 갯수
#define SWITCH_START 50
#define EXIT 99
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define WIDTH 20
#define HEIGHT 20