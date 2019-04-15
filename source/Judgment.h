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

	// ÌßÚ²Ô°‚Ì‘O—Ö‚Æ“GÌßÚ²Ô°‚ÌØ±(Œã—Ö)
	bool CheckSpin(void);
	
	// ÌßÚ²Ô°‚Ì‘O‘Ì‚Æâ‚È‚Ç‚ÌáŠQ•¨
	bool CheckObstacle(void);

	// ÌßÚ²Ô°‚ÌÚ’n
	bool CheckIsGround(void);

private:
	Judgment();
	~Judgment();
};

