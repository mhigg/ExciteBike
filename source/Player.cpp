// ※※※マジックナンバーは定数化すること

#include <algorithm>
#include <DxLib.h>
#include "Player.h"
#include "Bike.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "GameCtrl.h"
#include "Judgment.h"
#include "classObj.h"

constexpr int KEY_GET_RANGE = 15;

Player::Player()
{
	inputFram = KEY_GET_RANGE;

	status = STATUS_NORMAL;
	unCtrlTime = READY_TIME;
	drawPos = { 0,0 };
	tilt = ANGLE_TYPE::STRAIGHT;
	turboFlag = false;
	initAnim();
}

Player::Player(VECTOR SetUpPos, VECTOR2 drawOffset):Obj(drawOffset)
{
	inputFram = KEY_GET_RANGE;

	init("image/player.act", "Running", SetUpPos);
	status = STATUS_NORMAL;
	unCtrlTime = READY_TIME;
	drawPos = { static_cast<int>(SetUpPos.x), static_cast<int>(SetUpPos.y + SetUpPos.z) };
	tilt = ANGLE_TYPE::STRAIGHT;
	turboFlag = false;
	initAnim();
}


Player::~Player()
{
}

bool Player::initAnim(void)
{
	AddAnim("Wait", 0, 1, lpImageMng.GetAct("image/player.act", "Wait")[0].duration, true);
	AddAnim("Running", 0, 2, lpImageMng.GetAct("image/player.act", "Running")[0].duration, true);
	AddAnim("Goal", 0, 1, lpImageMng.GetAct("image/player.act", "Goal")[0].duration, true);
	AddAnim("Wheelie", 0, 6, lpImageMng.GetAct("image/player.act", "Wheelie")[0].duration, false);
	return true;
}

//void Player::Draw(void)
//{
	//int scrollOffset = GetScroll();
	//DrawFormatString(drawOffset.x + drawPos.x - scrollOffset, drawOffset.y + drawPos.y, 0x00ffffff, "speed:%d temperature:%d", speed, temperature);
	//if (status == STATUS_OVERHEAT)
	//{
	//	OverHeatDraw();
	//}
	//DrawFormatString(pos.x, pos.y + pos.z, 0x00ffffff, "pos.x:%d pos.y + pos.z:%d", pos.x, pos.y + pos.z);
//}

void Player::OverHeatDraw(void)
{
	if ((unCtrlTime % 20) / 3 == 0)
	{
		DrawString(500, 50, "ＯＶＥＲ　ＨＥＡＴ", 0x00ffffff);
	}
	if (unCtrlTime < 0)
	{
		DrawString(550, 50, "ＧＯ", 0x00ffffff);
	}
}

bool Player::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_PLAYER);
}

bool Player::CheckAngleType(ANGLE_TYPE type)
{
	return (type == tilt);
}

bool Player::Move(const int accelKey, const int turboKey)
{
	if (turboKey && !accelKey)
	{
		SetAnim("Running");
		speed = 20;		// ←最初から急加速　(0-18-20くらい)
		turboFlag = (tmpTemp > 50);

		if (tmpTemp >= 100)
		{
			status = STATUS_OVERHEAT;
			unCtrlTime = COOLDOWN;
		}
		else
		{
			if (inputFram % 5 == 0)
			{
				tmpTemp++;
			}
		}
		inputFram++;
	}


	if (accelKey)
	{
		// 押し続けている間一定速度で走行し、ｱﾆﾒｰｼｮﾝを「走行中」にする
		SetAnim("Running");
		speed = 20;	// ←最初少し加速、あとは一定速度(0-2-8-20くらい)

		if (inputFram % 12 == 0)
		{
			tmpTemp++;
		}

		if (tmpTemp > 50)
		{
			if (turboFlag)
			{
				if (inputFram % 6 == 0)
				{
					tmpTemp--;
				}
			}
			else
			{
				tmpTemp = 50;
			}
		}

		inputFram++;
	}

	// Zｷｰを離すと減速していく。完全にｽﾋﾟｰﾄﾞが0になったらｱﾆﾒｰｼｮﾝを「待機」にする

	if (!accelKey && !turboKey)
	{
		if (inputFram % 12 == 0)
		{
			speed -= 5;
			tmpTemp -= 2;
		}
		inputFram--;
	}
	return (speed > 0);
}

void Player::SetMove(const GameCtrl & controller)
{
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);

	VECTOR distance = VGet(0, 0, 0);	// 移動量 x:直進 y:ｼﾞｬﾝﾌﾟ z:手前と奥

	tmpTemp = temperature;

	// ﾌﾟﾚｲﾔｰと障害物の当たり判定
	if (lpJudgment.CheckSpin())
	{
		status = STATUS_SPIN;
	}

	switch (status)
	{
	case STATUS_BEF_START:
		// ｽﾀｰﾄ地点、ﾚｰｽ開始前
		// ｱｸｾﾙもﾀｰﾎﾞも、ﾒｰﾀｰ半分まで増える
		SetAnim("Wait");
		if (unCtrlTime < 0)
		{
			status = STATUS_WAIT;
		}
		unCtrlTime--;
		break;
	case STATUS_WAIT:
		SetAnim("Wait");
		if (Move(ctrl[KEY_INPUT_Z], ctrl[KEY_INPUT_X]))
		{
			status = STATUS_NORMAL;
		}

		// 左右同時押し時は右優先
		if (ctrl[KEY_INPUT_UP])
		{
			// 1回押すと1ﾚｰﾝ分左(画面上での上)に移動する
			// 押し続けていると1ﾚｰﾝずつ左に移動していく
			SetAnim("Left");
			distance.z--;
			dir = DIR_LEFT;
		}

		if (ctrl[KEY_INPUT_DOWN])
		{
			// 1回押すと1ﾚｰﾝ分右(画面上での下)に移動する
			// 押し続けていると1ﾚｰﾝずつ右に移動していく
			SetAnim("Right");
			distance.z++;
			dir = DIR_RIGHT;
		}

		break;
	case STATUS_NORMAL:
		// ｸｰﾙｿﾞｰﾝを通過したらﾀｰﾎﾞﾒｰﾀを最小値まで減らす
		// if()
		// {
		//		temperature = 20;
		// }

		if (!Move(ctrl[KEY_INPUT_Z], ctrl[KEY_INPUT_X]))
		{
			status = STATUS_WAIT;
		}

		// 左右同時押し時は右優先
		if (ctrl[KEY_INPUT_UP])
		{
			// 1回押すと1ﾚｰﾝ分左(画面上での上)に移動する
			// 押し続けていると1ﾚｰﾝずつ左に移動していく
			SetAnim("Left");
			distance.z--;
			dir = DIR_LEFT;
		}

		if (ctrl[KEY_INPUT_DOWN])
		{
			// 1回押すと1ﾚｰﾝ分右(画面上での下)に移動する
			// 押し続けていると1ﾚｰﾝずつ右に移動していく
			SetAnim("Right");
			distance.z++;
			dir = DIR_RIGHT;
		}

		// ｷｰを離したらﾚｰﾝ移動が完了するまで向きは戻さず、ﾌﾟﾚｲﾔｰとﾚｰﾝのX軸が一致したら向きを戻す→接地判定
		// 左右移動時は、X軸方向とY軸方向の両方に移動する(ﾍﾞｸﾄﾙ)

		if (ctrl[KEY_INPUT_LEFT])
		{
			inputFram++;
			if (inputFram >= KEY_GET_RANGE)
			{
				tilt++;
				inputFram = 0;
			}
		}

		break;
	case STATUS_JUMP:
		// 左右移動とｸｰﾙｿﾞｰﾝ以外はNORMALと同じ
		// 傾き状態を取得し、角度に応じて向いている方向への速度を調整する
		// ｼﾞｬﾝﾌﾟした瞬間(接地判定が偽になったとき)に向いている角度の方向の速度(X,Yそれぞれの移動量)を一度設定し、
		// そのあとは角度を変えるごとに、向いていない方向の速度を落としていく
		Move(ctrl[KEY_INPUT_Z], ctrl[KEY_INPUT_X]);

		break;
	case STATUS_OVERHEAT:
		// ﾀｰﾎﾞﾒｰﾀがﾏｯｸｽになったら速度を急激に下げ、強制停止させる。操作不可能
		speed -= 5;
		tmpTemp = 20;

		// 5秒経過後、再ｽﾀｰﾄ
		if (unCtrlTime < 0)
		{
			status = STATUS_WAIT;
		}
		unCtrlTime--;
		break;
	case STATUS_SPIN:
		// ｽﾋﾟﾝ時はﾊﾞｲｸをｲﾝｽﾀﾝｽし、同じ方向に同じ速さで移動する(投げ出される感じ)
		// ﾊﾞｲｸとﾌﾟﾚｲﾔｰの投げ出される移動量は異なり、投げ出される前のﾌﾟﾚｲﾔｰの速度が速いほど移動量は多くなる

		// 
		AddObjList()(objList, std::make_unique<Bike>(pos, drawOffset));
		reStartCnt = speed * tmpTemp;
		break;
	case STATUS_RESTART:
		if ((ctrl[KEY_INPUT_Z] & ~ctrlOld[KEY_INPUT_Z])
		 || (ctrl[KEY_INPUT_X] & ~ctrlOld[KEY_INPUT_X]))
		{
			reStartCnt--;
		}
	default:
		break;
	}

	// 最低値
	if (speed < 0)
	{
		speed = 0;
	}
	if (tmpTemp < 20)
	{
		tmpTemp = 20;
	}

	temperature = tmpTemp;
	distance.x = speed;

	pos.x += distance.x;
	pos.y += distance.y;
	pos.z += distance.z;
	drawPos = { static_cast<int>(pos.x), static_cast<int>(pos.y + pos.z) };
	AddScroll(distance.x);

//	_RPTN(_CRT_WARN, "pos.x:%d, pos.y:%d, pos.z:%d, temp:%d\n", static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(pos.z), temperature);
}