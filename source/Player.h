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

enum STATUS {
	STATUS_BEF_START,	// ｽﾀｰﾄ地点(発進前)
	STATUS_NORMAL,		// 通常状態
	STATUS_JUMP,		// ｼﾞｬﾝﾌﾟ中
	STATUS_OVERHEAT,	// ｵｰﾊﾞｰﾋｰﾄ中
	STATUS_SPIN,		// ｽﾋﾟﾝ中
	STATUS_MAX
};

class Player :
	public Obj
{
public:
	Player();
	Player(VECTOR SetUpPos, VECTOR2 drawOffset);
	~Player();

	void Draw(void);
	bool CheckObjType(OBJ_TYPE type);

private:
	void SetMove(const GameCtrl & controller);
	void OverHeatDraw(void);
	void Move(const int accelKey, const int turboKey);	// ｱｸｾﾙ・ﾀｰﾎﾞ処理

	DIR dir;			// ﾌﾟﾚｲﾔｰの向き
	float speed;		// ﾌﾟﾚｲﾔｰの速度
	int turbo;			// ﾀｰﾎﾞﾒｰﾀ
	STATUS status;		// ﾌﾟﾚｲﾔｰの状態
	int coolDownTime;	// ｵｰﾊﾞｰﾋｰﾄ状態から復帰するまでの時間
	float tilt;			// ﾌﾟﾚｲﾔｰの傾き角度

	VECTOR2 tmpPos;

	sharedListObj objList;
};

