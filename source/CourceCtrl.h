#pragma once
#include "classObj.h"
#include "VECTOR2.h"

#define lpCourceCtrl = CourceCtrl::GetInstance()

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

	// GameMode�̂݁A��ڲ԰��ݽ�ݽ����֐� 1�̲ݽ�ݽ������2�̖ڈȍ~�Ͳݽ�ݽ����Ȃ�
	// modeFlag:true��EditMode false��GameMode
	bool SetUpGameObj(sharedListObj objList, bool modeFlag);

private:
	CourceCtrl();
	~CourceCtrl();

	VECTOR2 drawOffset;
};

