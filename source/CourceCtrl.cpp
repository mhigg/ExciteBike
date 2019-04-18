#include <memory>
#include <DxLib.h>
#include "CourceCtrl.h"
#include "SceneMng.h"
#include "ImageMng.h"
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
	//	auto actData = lpImageMng.GetAct("image/cource.act", "blank")[0];
		DrawGraph(drawOffset.x /* - scroll*/, drawOffset.y, lpImageMng.GetActID("image/cource.act", "blank")[0], true);
	}
}

bool CourceCtrl::SetUp(VECTOR2 size, VECTOR2 blockSize, VECTOR2 drawOffset)
{
	mapSize = size / blockSize;		// º°½‘S’· / 1ÌÞÛ¯¸‚Ì»²½Þ
	this->blockSize = blockSize;
	this->drawOffset = drawOffset;
	courceData.resize(mapSize.x * mapSize.y);
	for (int start = 0; start < 4; start++)
	{
		courceData[start] = OBJ_ID::START;
	}
	for (int idx = 4; idx < courceData.size(); idx++)
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
