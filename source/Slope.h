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
	VECTOR2 ground;		// 坂の接地点
	VECTOR2 vertex;		// 坂の頂点
	ANGLE_TYPE angle;	// 坂の角度ﾀｲﾌﾟ
};

