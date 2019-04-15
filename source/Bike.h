#pragma once
#include "Obj.h"
#include "VECTOR2.h"

class Bike :
	public Obj
{
public:
	Bike();
	Bike(VECTOR setUpPos, VECTOR2 drawOffset);
	~Bike();
	bool CheckObjType(OBJ_TYPE type);
	bool CheckAngleType(ANGLE_TYPE type);

private:
	void SetMove(const GameCtrl &controller);
};

