#include "Slope.h"



Slope::Slope()
{
}

Slope::Slope(VECTOR2 ground, VECTOR2 vertex, ANGLE_TYPE angle)
{
	this->ground = ground;
	this->vertex = vertex;
	this->angle = angle;
}


Slope::~Slope()
{
}

bool Slope::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_OBSTACLE);
}

OBSTACLE Slope::CheckType(void)
{
	return OBST_SLOPE;
}

bool Slope::CheckAngleType(ANGLE_TYPE type)
{
	return (type == angle);
}
