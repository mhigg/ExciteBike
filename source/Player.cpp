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

	VECTOR distance = VGet(0,0,0);	// �ړ��� x:���i y:�ެ��� z:��O�Ɖ�

	// ����Ұ���ϯ���ɂȂ����瑬�x���}���ɉ����A������~������B����s�\
	if (OHFlag)
	{
		speed -= 5;
	}
	else
	{
		if (ctrl[KEY_INPUT_Z])
		{
			// ���������Ă���ԉ������A��Ұ��݂��u���s���v�ɂ���
			// X����葬�x�܂ŉ����������������߂�
			speed = 20;
			turbo += 2;
			if (turbo > 50)
			{
				turbo -= 2;
				// ���̒l�Ŏ~�߂�
				//turbo = 50;
			}
		}
		// Z���𗣂��ƌ������Ă����B���S�ɽ�߰�ނ�0�ɂȂ������Ұ��݂��u�ҋ@�v�ɂ���
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

		// �����ɽ�߰�ނ�萔�ő������A�ړ��ʂɂ��遫
		distance.x = speed;

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
	}
}
