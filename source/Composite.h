#pragma once
#include "Obstacle.h"

class Composite :
	public Obstacle
{
public:
	Composite();
	Composite(VECTOR2 ground, VECTOR2 vertex, float angle, int top);
	~Composite();

	bool CheckObjType(OBJ_TYPE type);
	OBSTACLE CheckType(void);

private:
	void initMad(VECTOR2 UPPER_L1, VECTOR2 DOWNER_R1, VECTOR2 UPPER_L2, VECTOR2 DOWNER_R2);	// 2ﾚｰﾝ大のぬかるみ×2

	VECTOR2 ground;		// 坂の接地点
	VECTOR2 vertex;		// 坂の頂点
	float angle;		// 坂の角度
	int top;			// 上の道
};

