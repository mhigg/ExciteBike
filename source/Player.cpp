#include <DxLib.h>
#include "Player.h"
#include "Bike.h"
#include "SceneMng.h"
#include "GameCtrl.h"
#include "classObj.h"


Player::Player()
{
	init("player.png", VECTOR2(30, 30), VECTOR2(5, 6));
	status = STATUS_NORMAL;
}

Player::Player(VECTOR SetUpPos, VECTOR2 drawOffset):Obj(drawOffset)
{
	init("player.png", VECTOR2(30, 30), VECTOR2(5, 6), SetUpPos);
	status = STATUS_NORMAL;
}


Player::~Player()
{
}

void Player::Draw(void)
{
	VECTOR2 drawOffset = lpSceneMng.GetDrawOffset();

	DrawFormatString(pos.x - drawOffset.x, 500, 0x00ffffff, "speed:%d turbo:%d", speed, turbo);
	if (status == STATUS_OVERHEAT)
	{
		OverHeatDraw();
	}
}

bool Player::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_PLAYER);
}

void Player::OverHeatDraw(void)
{
	if ((coolDownTime ) == 0)
	{
		DrawString(500, 50, "ＯＶＥＲ　ＨＥＡＴ", 0x00ffffff);
	}
}

void Player::Move(const int accelKey, const int turboKey)
{
	if (accelKey)
	{
		// 押し続けている間一定速度で走行し、ｱﾆﾒｰｼｮﾝを「走行中」にする
		speed = 20;	// ←最初少し加速、あとは一定速度(0-2-8-20くらい)
		// 33.3ﾌﾚｰﾑに1回
		turbo += 33;
		if (turbo > 181)
		{
			turbo -= 33;
			// 一定の値で止める
			//turbo = 50;
		}
	}
	// Zｷｰを離すと減速していく。完全にｽﾋﾟｰﾄﾞが0になったらｱﾆﾒｰｼｮﾝを「待機」にする
	else
	{
		speed -= 2;
		turbo -= 2;
	}

	if (turboKey)
	{
		speed = 20;	// ←最初から急加速　(0-18-20くらい)
		if (turbo >= 360)
		{
			status = STATUS_OVERHEAT;
			coolDownTime = lpSceneMng.GetFram(true);
		}
		else
		{
			// 15ﾌﾚｰﾑに1回
			turbo += 15;
		}
	}

}

void Player::SetMove(const GameCtrl & controller)
{
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);

	VECTOR distance = VGet(0,0,0);	// 移動量 x:直進 y:ｼﾞｬﾝﾌﾟ z:手前と奥

	// ﾌﾟﾚｲﾔｰと障害物の当たり判定
	// 

	switch (status)
	{
	case STATUS_BEF_START:
		// ｽﾀｰﾄ地点、ﾚｰｽ開始前
		// ｱｸｾﾙもﾀｰﾎﾞも、ﾒｰﾀｰ半分まで増える
		Move(ctrl[KEY_INPUT_Z], ctrl[KEY_INPUT_X]);
		break;
	case STATUS_NORMAL:
		// ｸｰﾙｿﾞｰﾝを通過したらﾀｰﾎﾞﾒｰﾀを最小値まで減らす
		// if()
		// {
		//		turbo = 20;
		// }
		
		Move(ctrl[KEY_INPUT_Z], ctrl[KEY_INPUT_X]);

		if (ctrl[KEY_INPUT_UP] & ~ctrlOld[KEY_INPUT_UP])
		{
			// 1回押すと1ﾚｰﾝ分左(画面上での上)に移動する
			// 押し続けていると1ﾚｰﾝずつ左に移動していく
			// 押している間はｱﾆﾒｰｼｮﾝを「左向き」にする
			distance.z--;
		}

		if (ctrl[KEY_INPUT_DOWN] & ~ctrlOld[KEY_INPUT_DOWN])
		{
			// 1回押すと1ﾚｰﾝ分右(画面上での下)に移動する
			// 押し続けていると1ﾚｰﾝずつ右に移動していく
			// 押している間はｱﾆﾒｰｼｮﾝを「右向き」にする
			distance.z++;
		}

		// ｷｰを離したらﾚｰﾝ移動が完了するまで向きは戻さず、ﾌﾟﾚｲﾔｰとﾚｰﾝのX軸が一致したら向きを戻す→接地判定
		// 左右移動時は、X軸方向とY軸方向の両方に移動する(ﾍﾞｸﾄﾙ)

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
		turbo = 20;
		// 4秒経過後、再ｽﾀｰﾄ
		if (lpSceneMng.GetFram(true) - coolDownTime >= 4)
		{
			status = STATUS_NORMAL;
		}
		break;
	case STATUS_SPIN:
		// ｽﾋﾟﾝ時はﾊﾞｲｸをｲﾝｽﾀﾝｽし、同じ方向に同じ速さで移動する(投げ出される感じ)
		// ﾊﾞｲｸとﾌﾟﾚｲﾔｰの投げ出される移動量は異なり、投げ出される前のﾌﾟﾚｲﾔｰの速度が速いほど移動量は多くなる
		
		// 
		AddObjList()(objList, std::make_unique<Bike>(pos, drawOffset));
		break;
	default:
		break;
	}

	if (speed <= 0)
	{
		speed = 0;
	}
	if (turbo <= 20)
	{
		turbo = 20;
	}

	distance.x = speed;
	lpSceneMng.SetDrawOffset(VECTOR2(static_cast<int>(distance.x),static_cast<int>(distance.y)));

	pos.x += distance.x;
	pos.y += distance.y;
	pos.z += distance.z;
}