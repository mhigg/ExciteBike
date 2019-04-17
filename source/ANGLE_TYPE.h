#pragma once

enum class ANGLE_TYPE
{
	STEEP_FOW,		// �}�ȎΖ�(-60�x���炢)
	MEDIUM_FOW,		// -50�x���炢
	NORMAL_FOW,		// ���ʂ̎Ζ�(-45�x���炢)
	LOOSE_FOW,		// �ɂ��Ζ�(-30�x���炢)
	STRAIGHT,		// �X���Ă��Ȃ����
	FINE,			// 15�x���炢:��ذ1�i�K��
	LOOSE,			// �ɂ��Ζ�(30�x���炢):��ذ2�i�K��
	NORMAL,			// ���ʂ̎Ζ�(45�x���炢):��ذ3�i�K��
	MEDIUM,			// 55�x���炢:��ذ4�i�K��
	STEEP,			// �}�ȎΖ�(60�x���炢):��ذ5�i�K��
	UPRIGHT,		// 90�x:��ذ6�i�K��
	MAX
};

// ANGLE_TYPE��int�^�̉��Z
ANGLE_TYPE operator+(ANGLE_TYPE& angle, int num);

// ANGLE_TYPE���m�̉��Z
ANGLE_TYPE operator+(ANGLE_TYPE& a, ANGLE_TYPE& b);

// �O�u�^�ݸ����
ANGLE_TYPE operator++(ANGLE_TYPE& angle);

// ��u�^�ݸ����
ANGLE_TYPE operator++(ANGLE_TYPE& angle, int);

// ANGLE_TYPE��int�^�̌��Z
ANGLE_TYPE operator-(ANGLE_TYPE& angle, int num);

// ANGLE_TYPE���m�̌��Z
ANGLE_TYPE operator-(ANGLE_TYPE& a, ANGLE_TYPE& b);

// �O�u�^�޸����
ANGLE_TYPE operator--(ANGLE_TYPE& angle);

// ��u�^�޸����
ANGLE_TYPE operator--(ANGLE_TYPE& angle, int);
