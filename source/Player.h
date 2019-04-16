#pragma once
#include <type_traits>
#include "Obj.h"
#include "VECTOR2.h"
#include "classObj.h"

constexpr int READY_TIME = 600;
constexpr int COOLDOWN = 300;

enum DIR {
	DIR_NONE,
	DIR_RIGHT,		// ハンドル右切り
	DIR_LEFT,		// ハンドル左切り
	DIR_UP,			// ジャンプ中：上向き
	DIR_DOWN,		// ジャンプ中：下向き
	DIR_MAX
};

enum STATUS {
	STATUS_BEF_START,	// ｽﾀｰﾄ地点(発進前)
	STATUS_WAIT,		// 待機状態
	STATUS_NORMAL,		// 通常状態
	STATUS_JUMP,		// ｼﾞｬﾝﾌﾟ中
	STATUS_OVERHEAT,	// ｵｰﾊﾞｰﾋｰﾄ中
	STATUS_SPIN,		// ｽﾋﾟﾝ中
	STATUS_RESTART,		// ｽﾋﾟﾝからの復帰
	STATUS_MAX
};

class Player :
	public Obj
{
public:
	Player();
	Player(VECTOR SetUpPos, VECTOR2 drawOffset);
	~Player();

	bool initAnim(void);

	//void Draw(void);
	bool CheckObjType(OBJ_TYPE type);
	bool CheckAngleType(ANGLE_TYPE type);

private:
	void SetMove(const GameCtrl & controller);
	void OverHeatDraw(void);
	bool Move(const int accelKey, const int turboKey);	// ｱｸｾﾙ・ﾀｰﾎﾞ処理

	DIR dir;			// ﾌﾟﾚｲﾔｰの向き
	float speed;		// ﾌﾟﾚｲﾔｰの速度
	int temperature;	// ｴﾝｼﾞﾝの温度
	int tmpTemp;		// 仮の温度
	bool turboFlag;		// ﾀｰﾎﾞによる温度半分超えをしたかどうか
	STATUS status;		// ﾌﾟﾚｲﾔｰの状態
	ANGLE_TYPE tilt;	// ﾌﾟﾚｲﾔｰの傾き角度

	int unCtrlTime;		// 操作不能状態の経過時間
	int reStartCnt;		// 再ｽﾀｰﾄまでの時間

	int inputFram;

	VECTOR2 tmpPos;

	sharedListObj objList;
};

