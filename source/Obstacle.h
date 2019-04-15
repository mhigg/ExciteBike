#pragma once
#include "Obj.h"

enum OBSTACLE {
	OBST_SLOPE,			// ç‚
	OBST_RECTANGLE,		// ãÈå`
	OBST_COMPOSITE,		// ï°çáínë—
	OBST_MAX
};

class Obstacle :
	public Obj
{
public:
	Obstacle();
	~Obstacle();
	
	virtual bool CheckObjType(OBJ_TYPE type) { return (type == OBJ_OBSTACLE); };
	virtual OBSTACLE CheckType(void) = 0;		// è·äQï®ÇÃ¿≤ÃﬂÇéÊìæÇ∑ÇÈ
	virtual bool CheckAngleType(ANGLE_TYPE type) { return (type == ANGLE_TYPE::STRAIGHT); };

private:
	virtual void SetMove(const GameCtrl &controller);
};

