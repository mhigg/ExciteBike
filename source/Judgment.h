#pragma once
#include "Obstacle.h"

#define lpJudgment Judgment::GetInstance()

class Judgment
{
public:
	static Judgment & GetInstance(void)
	{
		static Judgment s_instance;
		return s_instance;
	}

	// ��ڲ԰�̑O�ւƓG��ڲ԰��ر(���)
	bool CheckSpin(void);
	
	// ��ڲ԰�̑O�̂ƍ�Ȃǂ̏�Q��
	bool CheckObstacle(VECTOR2 actRect, VECTOR2 RectSize);

	// ��ڲ԰�̐ڒn
	bool CheckIsGround(void);

private:
	Judgment();
	~Judgment();
};

