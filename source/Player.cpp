#include <DxLib.h>
#include "Player.h"
#include "GameCtrl.h"



Player::Player()
{
}

Player::Player(VECTOR SetUpPos, VECTOR2 drawOffset):Obj(drawOffset)
{
	pos = SetUpPos;
}


Player::~Player()
{
}

void Player::SetMove(const GameCtrl & controller, weakListObj objList)
{
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);

	VECTOR distance = { 0,0,0 };	// 移動量 x:直進 y:ｼﾞｬﾝﾌﾟ z:手前と奥

	if (ctrl[KEY_INPUT_Z] & ~ctrlOld[KEY_INPUT_Z])
	{
		// 押し続けている間加速し、ｱﾆﾒｰｼｮﾝを「走行中」にする
		// X→一定速度まで加速したら加速をやめる
		distance.x++;
	}
	// Zｷｰを離すと減速していく。完全にｽﾋﾟｰﾄﾞが0になったらｱﾆﾒｰｼｮﾝを「待機」にする

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

	_RPTN(_CRT_WARN, "x,y,z : %1f, %1f, %1f", distance.x, distance.y, distance.z);
}
