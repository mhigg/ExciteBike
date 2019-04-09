#pragma once
#include "Obj.h"
#include "VECTOR2.h"

enum DIR {
	DIR_RIGHT,		// ハンドル右切り
	DIR_LEFT,		// ハンドル左切り
	DIR_UP,			// ジャンプ中：上向き
	DIR_DOWN,		// ジャンプ中：下向き
	DIR_MAX
};

class Player
	: Obj
{
public:
	Player();
	Player(VECTOR SetUpPos, VECTOR2 drawOffset);
	~Player();

private:
	void SetMove(const GameCtrl & controller, weakListObj objList);
	
	DIR dir;
	int speed;
	VECTOR2 tmpPos;

	sharedListObj objList;
};

