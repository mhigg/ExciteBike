#pragma once
#include <DxLib.h>
#include <string>
#include <map>
#include "ANGLE_TYPE.h"
#include "VECTOR2.h"
#include "classObj.h"

enum ANIM_TBL {
	ANIM_TBL_START_ID,		// ��Ұ��݂̊J�n
	ANIM_TBL_FRAME,			// ��Ұ��݂̺ϐ�
	ANIM_TBL_INV,			// �ς��Ƃ̊Ԋu
	ANIM_TBL_MAX
};

enum OBJ_TYPE {
	OBJ_PLAYER,			// ��ڲ԰
	OBJ_BIKE,			// �޲�
	OBJ_OBSTACLE,		// ��Q��
	OBJ_MAX
};

class GameCtrl;

class Obj
{

public:
	Obj();
	Obj(VECTOR2 drawOffset);	// �󂯎����drawOffset�������̎���drawOffset�ɓ����
	bool init(
		std::string fileName,	// �摜��̧�ٖ�
		VECTOR2 divSize,		// ��������
		VECTOR2 divCnt			// �������̏�����
	);
	bool init(
		std::string fileName,	// �摜��̧�ٖ�
		VECTOR2 divSize,		// ��������
		VECTOR2 divCnt,			// �������̏�����
		VECTOR pos				// ���W
	);
	bool init(
		std::string fileName,	// �摜��̧�ٖ�(act�`��)
		std::string actName,	// ����ݖ�
		VECTOR pos				// ���W
	);

	virtual ~Obj();
	void UpDate(const GameCtrl &controller);	// ���X�V	���۰װ���̂��߲����n��
	virtual void Draw(void);					// �`��
	void Draw(unsigned int id);					// ID�w��`��
//	void Draw()
	const VECTOR &GetPos(void);					// ���W�擾�֐�

	bool AddAnim(
		std::string animName,	// ��Ұ��݂̖��O
		int id_x,				// ����
		int id_y,				// ���
		int frame,				// �ϐ�
		int inv					// �Ԋu�̐ݒ�
	);
	bool SetAnim(std::string animName);
	std::string GetAnim(void);
	const int GetScroll(void);
	virtual bool CheckDeath(void) { return false; };	// Player:���S����
	virtual bool CheckObjType(OBJ_TYPE type) = 0;
	virtual bool CheckAngleType(ANGLE_TYPE type) = 0;	// ��/��ڲ԰�̌��݂̊p�x���߂��m�F����

private:
	virtual void SetMove(const GameCtrl &controller) = 0;

	std::string animName;	// �\�������Ұ��ݖ�
	std::map<std::string, int[ANIM_TBL_MAX]> animTable;
	int scrollOffset;			// ��۰قɂ��`��̂����(�������̂�)

protected:
	void AddScroll(const int distanceX);	// ��۰ٗʂ̑���

	std::string imageName;	// �\������摜��̧�ٖ�
	VECTOR2 divSize;		// �摜�̕�������
	VECTOR2 divCnt;			// �摜�̕�����

	unsigned int animCnt;	// ��Ұ��̶݂���

	VECTOR2 drawPos;			// �\������ۂ̍��W : y���W����ڲ԰���W��y��z�𑫂����l
	VECTOR pos;					// ��ڲ԰�̽ð�ޏ�̍��W
	void SetPos(VECTOR pos);

	const VECTOR2 drawOffset;		// �`��̾��
};