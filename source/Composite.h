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
	void initMad(VECTOR2 UPPER_L1, VECTOR2 DOWNER_R1, VECTOR2 UPPER_L2, VECTOR2 DOWNER_R2);	// 2ڰݑ�̂ʂ���݁~2

	VECTOR2 ground;		// ��̐ڒn�_
	VECTOR2 vertex;		// ��̒��_
	float angle;		// ��̊p�x
	int top;			// ��̓�
};

