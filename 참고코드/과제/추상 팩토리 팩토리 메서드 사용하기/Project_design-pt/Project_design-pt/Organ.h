#pragma once
#include <iostream>
#include <string>
using namespace std;

class Organ
{
public:
	virtual string Naming() = 0;
};

class Brain : public Organ
{
public:
	virtual string Naming();
};

class Stomach : public Organ
{
public:
	virtual string Naming();
};

class Rectum : public Organ
{
public:
	virtual string Naming();
};

