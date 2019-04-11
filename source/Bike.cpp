#include "Obj.h"
#include "Bike.h"



Bike::Bike()
{
}

Bike::Bike(VECTOR setUpPos, VECTOR2 drawOffset) : Obj(drawOffset)
{
	init("bike.png", VECTOR2(30, 30), VECTOR2(1, 1), setUpPos);
}


Bike::~Bike()
{
}

bool Bike::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_BIKE);
}

void Bike::SetMove(const GameCtrl & controller)
{

}
