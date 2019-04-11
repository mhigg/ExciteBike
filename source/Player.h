#pragma once
#include "Obj.h"
#include "VECTOR2.h"
#include "classObj.h"

enum DIR {
	DIR_RIGHT,		// �n���h���E�؂�
	DIR_LEFT,		// �n���h�����؂�
	DIR_UP,			// �W�����v���F�����
	DIR_DOWN,		// �W�����v���F������
	DIR_MAX
};

enum STATUS {
	STATUS_BEF_START,	// ���Ēn�_(���i�O)
	STATUS_NORMAL,		// �ʏ���
	STATUS_JUMP,		// �ެ��ߒ�
	STATUS_OVERHEAT,	// ���ް˰Ē�
	STATUS_SPIN,		// ���ݒ�
	STATUS_MAX
};

class Player :
	public Obj
{
public:
	Player();
	Player(VECTOR SetUpPos, VECTOR2 drawOffset);
	~Player();

	void Draw(void);
	bool CheckObjType(OBJ_TYPE type);

private:
	void SetMove(const GameCtrl & controller);
	void OverHeatDraw(void);
	void Move(const int accelKey, const int turboKey);	// ���فE���ޏ���

	DIR dir;			// ��ڲ԰�̌���
	float speed;		// ��ڲ԰�̑��x
	int turbo;			// ����Ұ�
	STATUS status;		// ��ڲ԰�̏��
	int coolDownTime;	// ���ް˰ď�Ԃ��畜�A����܂ł̎���
	float tilt;			// ��ڲ԰�̌X���p�x

	VECTOR2 tmpPos;

	sharedListObj objList;
};

