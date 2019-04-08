#pragma once
#include "Obj.h"

enum DIR {
	DIR_RIGHT,
	DIR_LEFT,
	DIR_UP,
	DIR_DOWN,
	DIR_MAX
};

class Player
	: Obj
{
public:
	Player();
	~Player();

private:
	void SetMove(const GameCtrl & controller, weakListObj objList);
	DIR dir;
	sharedListObj objList;
};

