#pragma once
#include "Obj.h"
#include "VECTOR2.h"
#include "classObj.h"

enum DIR {
	DIR_RIGHT,		// �n���h���E�؂�
	DIR_LEFT,		// �n���h�����؂�
	DIR_UP,			// �W�����v���F�����
	DIR_DOWN,		// �W�����v���F������
	DIR_MAX
};

class Player :
	public Obj
{
public:
	Player();
	Player(VECTOR SetUpPos, VECTOR2 drawOffset);
	~Player();

private:
	void SetMove(const GameCtrl & controller);
	DIR dir;
	int speed;		// ��ڲ԰�̑��x
	int turbo;		// ����Ұ�
	bool OHFlag;	// ���ް˰��׸�
	VECTOR2 tmpPos;
};

