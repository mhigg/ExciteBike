// �������}�W�b�N�i���o�[�͒萔�����邱��

#include <DxLib.h>
#include "Player.h"
#include "Bike.h"
#include "SceneMng.h"
#include "GameCtrl.h"
#include "Judgment.h"
#include "classObj.h"


Player::Player()
{
	init("player.png", VECTOR2(30, 30), VECTOR2(5, 6));
	status = STATUS_NORMAL;
	drawPos = { 0,0 };
}

Player::Player(VECTOR SetUpPos, VECTOR2 drawOffset):Obj(drawOffset)
{
	init("player.png", VECTOR2(30, 30), VECTOR2(5, 6), SetUpPos);
	status = STATUS_NORMAL;
	drawPos = { static_cast<int>(SetUpPos.x), static_cast<int>(SetUpPos.y + SetUpPos.z) };
}


Player::~Player()
{
}

void Player::Draw(void)
{
	int scrollOffset = GetScroll();
	DrawFormatString(drawOffset.x + drawPos.x - scrollOffset, drawOffset.y + drawPos.y, 0x00ffffff, "speed:%d temperature:%d", speed, temperature);
	if (status == STATUS_OVERHEAT)
	{
		OverHeatDraw();
	}
	DrawFormatString(pos.x, pos.y + pos.z, 0x00ffffff, "pos.x:%d pos.y + pos.z:%d", pos.x, pos.y + pos.z);
}

void Player::OverHeatDraw(void)
{
	if ((coolDownTime ) == 0)
	{
		DrawString(500, 50, "�n�u�d�q�@�g�d�`�s", 0x00ffffff);
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

void Player::Move(const int accelKey, const int turboKey)
{
	if (accelKey)
	{
		// ���������Ă���Ԉ�葬�x�ő��s���A��Ұ��݂��u���s���v�ɂ���
		speed = 20;	// ���ŏ����������A���Ƃ͈�葬�x(0-2-8-20���炢)
		// 33.3�ڰт�1��
		temperature += 33;

		if (temperature > 180)
		{
			temperature = 180;
			// ���̒l�Ŏ~�߂�
			//temperature = 50;
		}
	}
	// Z���𗣂��ƌ������Ă����B���S�ɽ�߰�ނ�0�ɂȂ������Ұ��݂��u�ҋ@�v�ɂ���
	else
	{
		speed -= 2;
		temperature -= 2;
	}


	if (turboKey)
	{
		speed = 20;	// ���ŏ�����}�����@(0-18-20���炢)
		if (temperature >= 360)
		{
			status = STATUS_OVERHEAT;
			coolDownTime = lpSceneMng.GetFram(true);
		}
		else
		{
			// 15�ڰт�1��
			temperature += 15;
		}
	}

}

void Player::SetMove(const GameCtrl & controller)
{
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);

	VECTOR distance = VGet(0, 0, 0);	// �ړ��� x:���i y:�ެ��� z:��O�Ɖ�

	// ��ڲ԰�Ə�Q���̓����蔻��
	if (lpJudgment.CheckSpin())
	{
		status = STATUS_SPIN;
	}

	switch (status)
	{
	case STATUS_BEF_START:
		// ���Ēn�_�Aڰ��J�n�O
		// ���ق����ނ��AҰ�������܂ő�����
		Move(ctrl[KEY_INPUT_Z], ctrl[KEY_INPUT_X]);
		break;
	case STATUS_NORMAL:
		// ��ٿް݂�ʉ߂���������Ұ����ŏ��l�܂Ō��炷
		// if()
		// {
		//		temperature = 20;
		// }

		Move(ctrl[KEY_INPUT_Z], ctrl[KEY_INPUT_X]);

		if (ctrl[KEY_INPUT_UP] & ~ctrlOld[KEY_INPUT_UP])
		{
			// 1�񉟂���1ڰݕ���(��ʏ�ł̏�)�Ɉړ�����
			// ���������Ă����1ڰ݂����Ɉړ����Ă���
			// �����Ă���Ԃͱ�Ұ��݂��u�������v�ɂ���
			distance.z--;
			dir = DIR_LEFT;
		}

		if (ctrl[KEY_INPUT_DOWN] & ~ctrlOld[KEY_INPUT_DOWN])
		{
			// 1�񉟂���1ڰݕ��E(��ʏ�ł̉�)�Ɉړ�����
			// ���������Ă����1ڰ݂��E�Ɉړ����Ă���
			// �����Ă���Ԃͱ�Ұ��݂��u�E�����v�ɂ���
			distance.z++;
			dir = DIR_RIGHT;
		}

		// ���𗣂�����ڰ݈ړ�����������܂Ō����͖߂����A��ڲ԰��ڰ݂�X������v�����������߂����ڒn����
		// ���E�ړ����́AX��������Y�������̗����Ɉړ�����(�޸��)

		break;
	case STATUS_JUMP:
		// ���E�ړ��Ƹ�ٿް݈ȊO��NORMAL�Ɠ���
		// �X����Ԃ��擾���A�p�x�ɉ����Č����Ă�������ւ̑��x�𒲐�����
		// �ެ��߂����u��(�ڒn���肪�U�ɂȂ����Ƃ�)�Ɍ����Ă���p�x�̕����̑��x(X,Y���ꂼ��̈ړ���)����x�ݒ肵�A
		// ���̂��Ƃ͊p�x��ς��邲�ƂɁA�����Ă��Ȃ������̑��x�𗎂Ƃ��Ă���
		Move(ctrl[KEY_INPUT_Z], ctrl[KEY_INPUT_X]);

		break;
	case STATUS_OVERHEAT:
		// ����Ұ���ϯ���ɂȂ����瑬�x���}���ɉ����A������~������B����s�\
		speed -= 5;
		temperature = 20;
		// 5�b�o�ߌ�A�Ľ���
		if (lpSceneMng.GetFram(true) - coolDownTime >= 5)
		{
			status = STATUS_NORMAL;
		}
		break;
	case STATUS_SPIN:
		// ���ݎ����޲���ݽ�ݽ���A���������ɓ��������ňړ�����(�����o����銴��)
		// �޲�����ڲ԰�̓����o�����ړ��ʂ͈قȂ�A�����o�����O����ڲ԰�̑��x�������قǈړ��ʂ͑����Ȃ�

		// 
		AddObjList()(objList, std::make_unique<Bike>(pos, drawOffset));
		break;
	default:
		break;
	}

	if (speed < 0)
	{
		speed = 0;
	}
	if (temperature < 20)
	{
		temperature = 20;
	}

	distance.x = speed;

	pos.x += distance.x;
	pos.y += distance.y;
	pos.z += distance.z;
	drawPos = { static_cast<int>(pos.x), static_cast<int>(pos.y + pos.z) };
	AddScroll(distance.x);
}