#pragma once
#include "Obstacle.h"

class Slope :
	public Obstacle
{
public:
	Slope();
	Slope(VECTOR2 ground, VECTOR2 vertex, ANGLE_TYPE angle);
	~Slope();

	bool CheckObjType(OBJ_TYPE type);
	OBSTACLE CheckType(void);
	bool CheckAngleType(ANGLE_TYPE type);

private:
	VECTOR2 ground;		// ��̐ڒn�_
	VECTOR2 vertex;		// ��̒��_
	ANGLE_TYPE angle;	// ��̊p�x����
};

