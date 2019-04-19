#pragma once
#include <vector>
#include <array>
#include "OBJ_ID.h"
#include "classObj.h"
#include "VECTOR2.h"

#define lpCourceCtrl CourceCtrl::GetInstance()

class CourceCtrl
{
public:
	static CourceCtrl & GetInstance(void)
	{
		static CourceCtrl s_instance;
		return s_instance;
	}

	// �擾�������(mapData)�����Ƃɕ`�� modeFlag:true��EditMode false��GameMode
	void Draw(bool modeFlag);

	// ����̑S������������:���Ēn�_�ƍŒ��(���3�����炢)�����ݸ����
	bool SetUp(VECTOR2 mapSize, VECTOR2 blockSize, VECTOR2 drawOffset);

	// GameMode�̂݁A��ڲ԰��ݽ�ݽ����֐� 1�̲ݽ�ݽ������2�̖ڈȍ~�Ͳݽ�ݽ����Ȃ�
	// modeFlag:true��EditMode false��GameMode
	bool SetUpGameObj(sharedListObj objList, bool modeFlag);

	bool SetCourceData(VECTOR2 pos, OBJ_ID id);

	void SetScroll(int distance);

private:
	CourceCtrl();
	~CourceCtrl();

	std::vector<OBJ_ID> courceData;

	std::array<std::string, static_cast<int>(OBJ_ID::MAX)> actNameTbl;

	VECTOR2 mapSize;		// ������̐ݒu��ۯ���
	VECTOR2 blockSize;
	VECTOR2 drawOffset;
	int scrollOffsetX;
};

