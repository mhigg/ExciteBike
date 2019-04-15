#pragma once
#include "Obj.h"
class Slope :
	public Obj
{
public:
	Slope();
	Slope(VECTOR2 ground, VECTOR2 vertex, float angle);
	~Slope();
};

