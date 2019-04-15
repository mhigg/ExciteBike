#pragma once
#include "Obj.h"

enum OBSTACLE {
	OBST_SLOPE,			// β
	OBST_RECTANGLE,		// ι`
	OBST_COMPOSITE,		// ‘nΡ
	OBST_MAX

};

class Obstacle :
	public Obj
{
public:
	Obstacle();
	~Obstacle();
	
	bool CheckObjType(OBJ_TYPE type) { return (type == OBJ_OBSTACLE); };
	virtual OBSTACLE CheckType(void) = 0;		// αQ¨Μΐ²ΜίπζΎ·ι
};

