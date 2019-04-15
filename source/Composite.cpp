#include "Composite.h"



Composite::Composite()
{
}

Composite::Composite(VECTOR2 ground, VECTOR2 vertex, float angle, int top)
{
}


Composite::~Composite()
{
}

void Composite::initMad(VECTOR2 UPPER_L1, VECTOR2 DOWNER_R1, VECTOR2 UPPER_L2, VECTOR2 DOWNER_R2)
{
}

bool Composite::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_OBSTACLE);
}

OBSTACLE Composite::CheckType(void)
{
	return OBST_COMPOSITE;
}
