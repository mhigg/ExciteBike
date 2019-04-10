#include <DxLib.h>
#include "Player.h"
#include "Obj.h"
#include "GameCtrl.h"
#include "classObj.h"


Player::Player()
{
	init("player.png", VECTOR2(30, 30), VECTOR2(5, 6));
}

Player::Player(VECTOR SetUpPos, VECTOR2 drawOffset):Obj(drawOffset)
{
	init("player.png", VECTOR2(30, 30), VECTOR2(5, 6), SetUpPos);
}


Player::~Player()
{
}

void Player::SetMove(const GameCtrl & controller)
{
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);

	VECTOR distance = VGet(0,0,0);	// 移動量 x:直進 y:ｼﾞｬﾝﾌﾟ z:手前と奥

	// ﾀｰﾎﾞﾒｰﾀがﾏｯｸｽになったら速度を急激に下げ、強制停止させる。操作不可能
	if (OHFlag)
	{
		speed -= 5;
	}
	else
	{
		if (ctrl[KEY_INPUT_Z])
		{
			// 押し続けている間加速し、ｱﾆﾒｰｼｮﾝを「走行中」にする
			// X→一定速度まで加速したら加速をやめる
			speed = 20;
			turbo += 2;
			if (turbo > 50)
			{
				turbo -= 2;
				// 一定の値で止める
				//turbo = 50;
			}
		}
		// Zｷｰを離すと減速していく。完全にｽﾋﾟｰﾄﾞが0になったらｱﾆﾒｰｼｮﾝを「待機」にする
		else
		{
			speed -= 2;
		}

		if (ctrl[KEY_INPUT_X])
		{
			if (turbo >= 100)
			{
				OHFlag = true;
			}
			else
			{
				turbo += 5;
			}
		}

		// ↑仮にｽﾋﾟｰﾄﾞを定数で増減し、移動量にする↓
		distance.x = speed;

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

		// ｷｰを離したらﾚｰﾝ移動が完了するまで向きは戻さず、ﾌﾟﾚｲﾔｰとﾚｰﾝのX軸が一致したら向きを戻す
		// 左右移動時は、X軸方向とY軸方向の両方に移動する(ﾍﾞｸﾄﾙ)

		pos.x += distance.x;
		pos.y += distance.y;
		pos.z += distance.z;
	}
}
