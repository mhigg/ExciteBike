#pragma once


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
	bool CheckObstacle(void);

	// ��ڲ԰�̐ڒn
	bool CheckIsGround(void);

private:
	Judgment();
	~Judgment();
};

