#pragma once
#include "Obstacle.h"

class Rectangle :
	public Obstacle
{
public:
	Rectangle();
	Rectangle(VECTOR2 UPPER_L, VECTOR2 DOWNER_R);
	~Rectangle();

	bool CheckObjType(OBJ_TYPE type);
	OBSTACLE CheckType(void);

private:
	VECTOR2 upperLeft;		// ãÈå`ÇÃç∂è„
	VECTOR2 downerRight;	// ãÈå`ÇÃâEâ∫
};

