#pragma once
#include "Obj.h"
#include "VECTOR2.h"
#include "classObj.h"

enum DIR {
	DIR_RIGHT,		// ハンドル右切り
	DIR_LEFT,		// ハンドル左切り
	DIR_UP,			// ジャンプ中：上向き
	DIR_DOWN,		// ジャンプ中：下向き
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
	int speed;		// ﾌﾟﾚｲﾔｰの速度
	int turbo;		// ﾀｰﾎﾞﾒｰﾀ
	bool OHFlag;	// ｵｰﾊﾞｰﾋｰﾄﾌﾗｸﾞ
	VECTOR2 tmpPos;
};

