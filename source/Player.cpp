// �������}�W�b�N�i���o�[�͒萔�����邱��

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
		DrawString(500, 50, "�n�u�d�q�@�g�d�`�s", 0x00ffffff);
	}
	if (unCtrlTime < 0)
	{
		DrawString(550, 50, "�f�n", 0x00ffffff);
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
		speed = 20;		// ���ŏ�����}�����@(0-18-20���炢)
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
		// ���������Ă���Ԉ�葬�x�ő��s���A��Ұ��݂��u���s���v�ɂ���
		SetAnim("Running");
		speed = 20;	// ���ŏ����������A���Ƃ͈�葬�x(0-2-8-20���炢)

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

	// Z���𗣂��ƌ������Ă����B���S�ɽ�߰�ނ�0�ɂȂ������Ұ��݂��u�ҋ@�v�ɂ���

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

	VECTOR distance = VGet(0, 0, 0);	// �ړ��� x:���i y:�ެ��� z:��O�Ɖ�

	tmpTemp = temperature;

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

		// ���E�����������͉E�D��
		if (ctrl[KEY_INPUT_UP])
		{
			// 1�񉟂���1ڰݕ���(��ʏ�ł̏�)�Ɉړ�����
			// ���������Ă����1ڰ݂����Ɉړ����Ă���
			SetAnim("Left");
			distance.z--;
			dir = DIR_LEFT;
		}

		if (ctrl[KEY_INPUT_DOWN])
		{
			// 1�񉟂���1ڰݕ��E(��ʏ�ł̉�)�Ɉړ�����
			// ���������Ă����1ڰ݂��E�Ɉړ����Ă���
			SetAnim("Right");
			distance.z++;
			dir = DIR_RIGHT;
		}

		break;
	case STATUS_NORMAL:
		// ��ٿް݂�ʉ߂���������Ұ����ŏ��l�܂Ō��炷
		// if()
		// {
		//		temperature = 20;
		// }

		if (!Move(ctrl[KEY_INPUT_Z], ctrl[KEY_INPUT_X]))
		{
			status = STATUS_WAIT;
		}

		// ���E�����������͉E�D��
		if (ctrl[KEY_INPUT_UP])
		{
			// 1�񉟂���1ڰݕ���(��ʏ�ł̏�)�Ɉړ�����
			// ���������Ă����1ڰ݂����Ɉړ����Ă���
			SetAnim("Left");
			distance.z--;
			dir = DIR_LEFT;
		}

		if (ctrl[KEY_INPUT_DOWN])
		{
			// 1�񉟂���1ڰݕ��E(��ʏ�ł̉�)�Ɉړ�����
			// ���������Ă����1ڰ݂��E�Ɉړ����Ă���
			SetAnim("Right");
			distance.z++;
			dir = DIR_RIGHT;
		}

		// ���𗣂�����ڰ݈ړ�����������܂Ō����͖߂����A��ڲ԰��ڰ݂�X������v�����������߂����ڒn����
		// ���E�ړ����́AX��������Y�������̗����Ɉړ�����(�޸��)

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
		// ���E�ړ��Ƹ�ٿް݈ȊO��NORMAL�Ɠ���
		// �X����Ԃ��擾���A�p�x�ɉ����Č����Ă�������ւ̑��x�𒲐�����
		// �ެ��߂����u��(�ڒn���肪�U�ɂȂ����Ƃ�)�Ɍ����Ă���p�x�̕����̑��x(X,Y���ꂼ��̈ړ���)����x�ݒ肵�A
		// ���̂��Ƃ͊p�x��ς��邲�ƂɁA�����Ă��Ȃ������̑��x�𗎂Ƃ��Ă���
		Move(ctrl[KEY_INPUT_Z], ctrl[KEY_INPUT_X]);

		break;
	case STATUS_OVERHEAT:
		// ����Ұ���ϯ���ɂȂ����瑬�x���}���ɉ����A������~������B����s�\
		speed -= 5;
		tmpTemp = 20;

		// 5�b�o�ߌ�A�Ľ���
		if (unCtrlTime < 0)
		{
			status = STATUS_WAIT;
		}
		unCtrlTime--;
		break;
	case STATUS_SPIN:
		// ���ݎ����޲���ݽ�ݽ���A���������ɓ��������ňړ�����(�����o����銴��)
		// �޲�����ڲ԰�̓����o�����ړ��ʂ͈قȂ�A�����o�����O����ڲ԰�̑��x�������قǈړ��ʂ͑����Ȃ�

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

	// �Œ�l
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