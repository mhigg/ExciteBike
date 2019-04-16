#pragma once
enum class ANGLE_TYPE
{
	STRAIGHT,		// �X���Ă��Ȃ����
	FINE,			// 15�x���炢:��ذ1�i�K��
	LOOSE,			// �ɂ��Ζ�(30�x���炢):��ذ2�i�K��
	NORMAL,			// ���ʂ̎Ζ�(45�x���炢):��ذ3�i�K��
	MEDIUM,			// 55�x���炢:��ذ4�i�K��
	STEEP,			// �}�ȎΖ�(60�x���炢):��ذ5�i�K��
	UPRIGHT,		// 90�x:��ذ6�i�K��
	LOOSE_DOWN,
	MAX
};

// FIRE_DIR�̐擪��Ԃ�
ANGLE_TYPE begin(ANGLE_TYPE);

// FIRE_DIR�̍Ō����Ԃ�
ANGLE_TYPE end(ANGLE_TYPE);

// �ݸ����
ANGLE_TYPE operator++(ANGLE_TYPE& dir);

// �Q�Ƃ̱��ڽ�����̂܂ܕԂ�	
ANGLE_TYPE operator*(ANGLE_TYPE& dir);