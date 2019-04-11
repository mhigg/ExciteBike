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

	// ﾌﾟﾚｲﾔｰの前輪と敵ﾌﾟﾚｲﾔｰのﾘｱ(後輪)
	bool CheckSpin(void);

	// ﾌﾟﾚｲﾔｰのﾘｱ(後輪)と敵ﾌﾟﾚｲﾔｰの前輪
	bool CheckAttack(void);
	
	// ﾌﾟﾚｲﾔｰの前体と坂などの障害物
	bool CheckObstacle(void);

	// ﾌﾟﾚｲﾔｰの接地
	bool CheckIsGround(void);

private:
	Judgment();
	~Judgment();
};

