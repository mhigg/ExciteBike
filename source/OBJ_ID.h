#pragma once
enum class OBJ_ID
{
	START,			// ���Ēn�_(DesignӰ�ނł͑I��s��)
	BLANK,			// ��Q���Ȃ�(DesignӰ�ނł͑I��s��)
	SMALL,			// ���R 45�x
	MEDIUM,			// ���R	45�x
	LARGE,			// ��R 45�x
	LOOSE,			// ���R 30�x
	STEEP,			// ��R 60�x
	L_TO_S,			// �ɂ���}
	S_TO_L,			// �}�����
	JUMPER,			// �ެ��ߑ�
	STEP_BACK,		// �i�� ��
	STEP_NEAR,		// �i�� ��
	MUDDY_BACK,		// �ʂ���� ��
	MUDDY_NEAR,		// �ʂ���� ��
	COOL_BACK,		// ��ٿް� ��
	COOL_NEAR,		// ��ٿް� ��
	TRACK_BACK,		// �ł����ׯ� ��
	TRACK_NEAR,		// �ł����ׯ� ��
	TRACK_NONE,		// �ł̂�
	MOUNTAIN,		// ��i�R
	COMPOSITE,		// �����n��
	END,			// ׯ�߁E�ްْn�_
	MAX
};

constexpr OBJ_ID PARTS_START = OBJ_ID::SMALL;

constexpr OBJ_ID PARTS_MAX = OBJ_ID::COMPOSITE;

OBJ_ID operator+(OBJ_ID id, OBJ_ID id2);

OBJ_ID operator-(OBJ_ID id, OBJ_ID id2);

OBJ_ID operator++(OBJ_ID id, int);

OBJ_ID operator--(OBJ_ID id, int);
