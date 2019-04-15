#include "Rectangle.h"



Rectangle::Rectangle()
{
}

Rectangle::Rectangle(VECTOR2 UPPER_L, VECTOR2 DOWNER_R)
{
}


Rectangle::~Rectangle()
{
}

bool Rectangle::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_OBSTACLE);
}

OBSTACLE Rectangle::CheckType(void)
{
	return OBST_RECTANGLE;
}
