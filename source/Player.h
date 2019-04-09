#pragma once
#include "Obj.h"
#include "VECTOR2.h"

enum DIR {
	DIR_RIGHT,		// �n���h���E�؂�
	DIR_LEFT,		// �n���h�����؂�
	DIR_UP,			// �W�����v���F�����
	DIR_DOWN,		// �W�����v���F������
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

