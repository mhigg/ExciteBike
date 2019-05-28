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
		"Start",	// ���Ēn�_(DesignӰ�ނł͑I��s��)
		"blank",	// ��Q���Ȃ�(DesignӰ�ނł͑I��s��)
		"A",		// ���R 45�x
		"B",		// ���R	45�x
		"C",		// ��R 45�x
		"D",		// ���R 30�x
		"E",		// ��R 60�x
		"F",		// �ɂ���}
		"G",		// �}�����
		"H",		// �ެ��ߑ�
		"I",		// �i�� ��
		"J",		// �i�� ��
		"K",		// �ʂ���� ��
		"L",		// �ʂ���� ��
		"M",		// ��ٿް� ��
		"N",		// ��ٿް� ��
		"O",		// �ł����ׯ� ��
		"P",		// �ł����ׯ� ��
		"Q",		// �ł̂�
		"R",		// ��i�R
		"S",		// �����n��
		"END"		// ׯ�߁E�ްْn�_
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
	mapSize = size / blockSize;		// ����S�� / 1��ۯ��̻���
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
