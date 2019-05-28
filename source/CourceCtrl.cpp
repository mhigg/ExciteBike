#include <memory>
#include <DxLib.h>
#include "CourceCtrl.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "Player.h"
#include "Slope.h"
#include "Rectangle.h"
#include "ANGLE_TYPE.h"
#include "classObj.h"
#include "VECTOR2.h"


CourceCtrl::CourceCtrl()
{
	actNameTbl = {
		"Start",	// ｽﾀｰﾄ地点(Designﾓｰﾄﾞでは選択不可)
		"blank",	// 障害物なし(Designﾓｰﾄﾞでは選択不可)
		"A",		// 小山 45度
		"B",		// 中山	45度
		"C",		// 大山 45度
		"D",		// 小山 30度
		"E",		// 大山 60度
		"F",		// 緩から急
		"G",		// 急から緩
		"H",		// ｼﾞｬﾝﾌﾟ台
		"I",		// 段差 上
		"J",		// 段差 下
		"K",		// ぬかるみ 上
		"L",		// ぬかるみ 下
		"M",		// ｸｰﾙｿﾞｰﾝ 上
		"N",		// ｸｰﾙｿﾞｰﾝ 下
		"O",		// 芝ありﾄﾗｯｸ 上
		"P",		// 芝ありﾄﾗｯｸ 下
		"Q",		// 芝のみ
		"R",		// 二段山
		"S",		// 複合地帯
		"END"		// ﾗｯﾌﾟ・ｺﾞｰﾙ地点
	};
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
//		DrawGraph(drawOffset.x /* - scroll*/, drawOffset.y, actData, true);

		for (int x = 0; x < mapSize.x;)
		{
			OBJ_ID id = courceData[x];
			auto actData = lpImageMng.GetAct("image/cource.act", actNameTbl[static_cast<int>(id)])[0];
			switch (id)
			{
			case OBJ_ID::BLANK:
				DrawRectGraph(
					x * blockSize.x - scrollOffsetX,
					200,
					actData.rect.x - 16,
					actData.rect.y - 56,
					actData.width,
					actData.height,
					lpImageMng.GetID("image/track_parts.png")[0],
					true
				);
				break;
			case OBJ_ID::START:
				DrawRectGraph(
					x * blockSize.x - scrollOffsetX,
					200,
					actData.rect.x - 32,
					actData.rect.y - 56,
					actData.width,
					actData.height,
					lpImageMng.GetID("image/track_parts.png")[0],
					true
				);
				break;
			case OBJ_ID::LARGE:
				DrawRectGraph(
					x * blockSize.x - scrollOffsetX,
					200,
					actData.rect.x - 32,
					actData.rect.y - 56,
					actData.width,
					actData.height,
					lpImageMng.GetID("image/track_parts.png")[0],
					true
				);
			default:
				break;
			}

			x += (actData.width / blockSize.x);
		}
	}

	_RPTN(_CRT_WARN, "scroll:%d\n", scrollOffsetX);
}

bool CourceCtrl::SetUp(VECTOR2 size, VECTOR2 blockSize, VECTOR2 drawOffset)
{
	mapSize = size / blockSize;		// ｺｰｽ全長 / 1ﾌﾞﾛｯｸのｻｲｽﾞ
	this->blockSize = blockSize;
	this->drawOffset = drawOffset;
	courceData.resize(mapSize.x);
	courceData[0] = OBJ_ID::BLANK;
	courceData[1] = OBJ_ID::START;
	for (int idx = 5; idx < courceData.size(); idx++)
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

	AddObjList()(objList, std::make_unique<Player>(VGet(0, 0, 0), lpSceneMng.GetDrawOffset()));

	for (int x = 0; x < mapSize.x; x++)
	{
		OBJ_ID id = courceData[x];
		switch (id)
		{
		case OBJ_ID::LARGE:
//			AddObjList()(objList, std::make_unique<Slope>(VECTOR2(0, 0), actData.))
			break;
		default:
			break;
		}
	}
	return true;
}


bool CourceCtrl::SetCourceData(VECTOR2 pos, OBJ_ID id)
{
	VECTOR2 mapPos = pos / blockSize;
	courceData[mapPos.x] = id;
	return true;
}

void CourceCtrl::SetScroll(int distance)
{
	this->scrollOffsetX = distance;
}
