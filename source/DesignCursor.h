#pragma once
#include "Obj.h"
#include "OBJ_ID.h"

constexpr int SPEED = 10;
constexpr int KEY_GET_RNG = 60;

class DesignCursor
	: public Obj
{
public:
	DesignCursor();
	DesignCursor(VECTOR2 drawOffset);
	~DesignCursor();

	void SetMove(const GameCtrl & controller);
	void Draw(void);
	bool CheckObjType(OBJ_TYPE type);
	bool CheckAngleType(ANGLE_TYPE type);

private:
	OBJ_ID id;


	int inputFram;
};

