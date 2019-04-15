#pragma once
#include "Obj.h"
class Rectangle :
	public Obj
{
public:
	Rectangle();
	Rectangle(VECTOR2 UPPER_L, VECTOR2 DOWNER_R);
	~Rectangle();
};

