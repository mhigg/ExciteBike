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
	
	virtual bool CheckObjType(OBJ_TYPE type) { return (type == OBJ_OBSTACLE); };
	virtual OBSTACLE CheckType(void) = 0;		// αQ¨Μΐ²ΜίπζΎ·ι
	virtual bool CheckAngleType(ANGLE_TYPE type) { return (type == ANGLE_TYPE::STRAIGHT); };

private:
	virtual void SetMove(const GameCtrl &controller);
};

