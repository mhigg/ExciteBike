#pragma once
#include "Obj.h"
class Bike :
	public Obj
{
public:
	Bike();
	~Bike();

private:
	void SetMove(const GameCtrl &controller);
};

