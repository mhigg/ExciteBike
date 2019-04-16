#pragma once
#include <type_traits>
#include "Obj.h"
#include "VECTOR2.h"
#include "classObj.h"

constexpr int READY_TIME = 600;
constexpr int COOLDOWN = 300;

enum DIR {
	DIR_NONE,
	DIR_RIGHT,		// �n���h���E�؂�
	DIR_LEFT,		// �n���h�����؂�
	DIR_UP,			// �W�����v���F�����
	DIR_DOWN,		// �W�����v���F������
	DIR_MAX
};

enum STATUS {
	STATUS_BEF_START,	// ���Ēn�_(���i�O)
	STATUS_WAIT,		// �ҋ@���
	STATUS_NORMAL,		// �ʏ���
	STATUS_JUMP,		// �ެ��ߒ�
	STATUS_OVERHEAT,	// ���ް˰Ē�
	STATUS_SPIN,		// ���ݒ�
	STATUS_RESTART,		// ���݂���̕��A
	STATUS_MAX
};

class Player :
	public Obj
{
public:
	Player();
	Player(VECTOR SetUpPos, VECTOR2 drawOffset);
	~Player();

	bool initAnim(void);

	//void Draw(void);
	bool CheckObjType(OBJ_TYPE type);
	bool CheckAngleType(ANGLE_TYPE type);

private:
	void SetMove(const GameCtrl & controller);
	void OverHeatDraw(void);
	bool Move(const int accelKey, const int turboKey);	// ���فE���ޏ���

	DIR dir;			// ��ڲ԰�̌���
	float speed;		// ��ڲ԰�̑��x
	int temperature;	// �ݼ�݂̉��x
	int tmpTemp;		// ���̉��x
	bool turboFlag;		// ���ނɂ�鉷�x�����������������ǂ���
	STATUS status;		// ��ڲ԰�̏��
	ANGLE_TYPE tilt;	// ��ڲ԰�̌X���p�x

	int unCtrlTime;		// ����s�\��Ԃ̌o�ߎ���
	int reStartCnt;		// �Ľ��Ă܂ł̎���

	int inputFram;

	VECTOR2 tmpPos;

	sharedListObj objList;
};

