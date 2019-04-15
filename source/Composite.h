#pragma once
#include "Obj.h"
class Composite :
	public Obj
{
public:
	Composite();
	Composite(VECTOR2 ground, VECTOR2 vertex, float angle, int top);
	~Composite();

private:
	void initMad(VECTOR2 UPPER_L1, VECTOR2 DOWNER_R1, VECTOR2 UPPER_L2, VECTOR2 DOWNER_R2);	// 2⁄∞›ëÂÇÃÇ Ç©ÇÈÇ›Å~2
};

