#include <memory>
#include <DxLib.h>
#include "CourceCtrl.h"
#include "SceneMng.h"
#include "Player.h"
#include "Slope.h"
#include "ANGLE_TYPE.h"
#include "classObj.h"
#include "VECTOR2.h"


CourceCtrl::CourceCtrl()
{

}


CourceCtrl::~CourceCtrl()
{
}

void CourceCtrl::Draw(bool modeFlag)
{
	if (modeFlag)
	{
		// DesignMode
	}
	else
	{
		// GameMode
	}
}

bool CourceCtrl::SetUp(VECTOR2 size, VECTOR2 blockSize, VECTOR2 drawOffset)
{
	mapSize = size / blockSize;		// ����S�� / 1��ۯ��̻���
	this->blockSize = blockSize;
	this->drawOffset = drawOffset;
	courceData.resize(mapSize.x * mapSize.y);
	for (int idx = 0; idx < courceData.size(); idx++)
	{
		courceData[idx] = OBJ_ID::BLANK;
	}

	return false;
}

bool CourceCtrl::SetUpGameObj(sharedListObj objList, bool modeFlag)
{
	if (modeFlag)
	{
		return false;
	}

	AddObjList()(objList, std::make_unique<Player>(VGet(0, 0, 0), VECTOR2(200, 500)));
	AddObjList()(objList, std::make_unique<Slope>(VECTOR2(400, 0), VECTOR2(436,36), ANGLE_TYPE::NORMAL));
	return true;
}


bool CourceCtrl::SetCourceData(VECTOR2 pos, OBJ_ID id)
{
	VECTOR2 mapPos = pos / blockSize;
	courceData[mapPos.x] = id;
	return true;
}
