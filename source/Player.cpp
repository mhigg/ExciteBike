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

	VECTOR distance = { 0,0,0 };	// �ړ��� x:���i y:�ެ��� z:��O�Ɖ�

	if (ctrl[KEY_INPUT_Z] & ~ctrlOld[KEY_INPUT_Z])
	{
		// ���������Ă���ԉ������A��Ұ��݂��u���s���v�ɂ���
		// X����葬�x�܂ŉ����������������߂�
		distance.x++;
	}
	// Z���𗣂��ƌ������Ă����B���S�ɽ�߰�ނ�0�ɂȂ������Ұ��݂��u�ҋ@�v�ɂ���

	if (ctrl[KEY_INPUT_UP] & ~ctrlOld[KEY_INPUT_UP])
	{
		// 1�񉟂���1ڰݕ���(��ʏ�ł̏�)�Ɉړ�����
		// ���������Ă����1ڰ݂����Ɉړ����Ă���
		// �����Ă���Ԃͱ�Ұ��݂��u�������v�ɂ���
		distance.z--;
	}

	if (ctrl[KEY_INPUT_DOWN] & ~ctrlOld[KEY_INPUT_DOWN])
	{
		// 1�񉟂���1ڰݕ��E(��ʏ�ł̉�)�Ɉړ�����
		// ���������Ă����1ڰ݂��E�Ɉړ����Ă���
		// �����Ă���Ԃͱ�Ұ��݂��u�E�����v�ɂ���
		distance.z++;
	}

	// ���𗣂�����ڰ݈ړ�����������܂Ō����͖߂����A��ڲ԰��ڰ݂�X������v�����������߂�
	// ���E�ړ����́AX��������Y�������̗����Ɉړ�����(�޸��)

	pos.x += distance.x;
	pos.y += distance.y;
	pos.z += distance.z;

	_RPTN(_CRT_WARN, "x,y,z : %1f, %1f, %1f", distance.x, distance.y, distance.z);
}
