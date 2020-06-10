#pragma once
#include "Observer.h"

class Subject
{
public:
	virtual void Notify() = 0;
	virtual void Add_Observer(Observer* ob) = 0;
	Subject();
	~Subject();
};

