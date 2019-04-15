#pragma once
#include "Obj.h"

enum OBSTACLE {
	OBST_SLOPE,			// ��
	OBST_RECTANGLE,		// ��`
	OBST_COMPOSITE,		// �����n��
	OBST_MAX

};

class Obstacle :
	public Obj
{
public:
	Obstacle();
	~Obstacle();
	
	bool CheckObjType(OBJ_TYPE type) { return (type == OBJ_OBSTACLE); };
	virtual OBSTACLE CheckType(void) = 0;		// ��Q�������߂��擾����
};

