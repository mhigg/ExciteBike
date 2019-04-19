#include <DxLib.h>
#include "Obj.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "CourceCtrl.h"
#include "classObj.h"

Obj::Obj()
{
	scrollOffset = 0;
}

Obj::Obj(VECTOR2 drawOffset) :drawOffset(drawOffset)
{
	scrollOffset = 0;
}

bool Obj::init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt)
{
	lpImageMng.GetID(fileName, divSize, divCnt);
	imageName = fileName;
	this->divSize = divSize;
	this->divCnt = divCnt;
	return true;
}

bool Obj::init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR pos)
{
	init(fileName, divSize, divCnt);
	SetPos(pos);
	return true;
}

bool Obj::init(std::string fileName, std::string actName, VECTOR pos)
{
	lpImageMng.GetActID(fileName, actName);
	imageName = fileName;
	SetPos(pos);
	return true;
}



Obj::~Obj()
{

}

void Obj::UpDate(const GameCtrl &controller)
{
	SetMove(controller);
	lpCourceCtrl.SetScroll(scrollOffset);
}

void Obj::Draw(void)
{
	if (imageName.length() == 0)
	{
		return;
	}
	unsigned int id = 0;
	if (animTable.find(animName) != animTable.end())
	{
		int count = (animCnt / animTable[animName][ANIM_TBL_INV]);
		if (animTable[animName][ANIM_TBL_LOOP]
		 || count < animTable[animName][ANIM_TBL_FRAME])
		{
			count %= animTable[animName][ANIM_TBL_FRAME];
		}
		else
		{
			count = animTable[animName][ANIM_TBL_FRAME] - 1;
			animEndFlag = true;
		}
		id = animTable[animName][ANIM_TBL_START_ID] + count;
	}
	animCnt++;
	if (id < lpImageMng.GetActID(imageName, animName).size())
	{
		auto path = imageName.substr(0, imageName.rfind(".") + 1) + "png";

		//auto actData = lpImageMng.GetAct(imageName, animName);

		//DrawRectGraph(
		//	drawOffset.x + drawPos.x - scrollOffset,
		//	drawOffset.y + drawPos.y,
		//	actData[id].rect.x,
		//	actData[id].rect.y,
		//	actData[id].width,
		//	actData[id].height,
		//	lpImageMng.GetID(path)[id],
		//	false
		//);

		DrawGraph(drawOffset.x + drawPos.x - scrollOffset, drawOffset.y + drawPos.y, lpImageMng.GetActID(imageName, animName)[id], true);
//		_RPTN(_CRT_WARN, "id : %d\n", id);
	}
}

void Obj::Draw(unsigned int id)
{
	if (id < IMAGE_ID(imageName).size())
	{
		DrawGraph(drawOffset.x + drawPos.x - scrollOffset, drawOffset.y + drawPos.y, IMAGE_ID(imageName)[id], true);
	}
}

const VECTOR & Obj::GetPos(void)
{
	return pos;
}

void Obj::AddScroll(const int distanceX)
{
	scrollOffset += distanceX;
}

const int Obj::GetScroll(void)
{
	return scrollOffset;
}


void Obj::SetPos(VECTOR pos)
{
	Obj::pos = pos;
}

bool Obj::AddAnim(std::string animName, int id, int frame, int duration, bool loop)
{
	animTable[animName][ANIM_TBL_START_ID] = id;
	animTable[animName][ANIM_TBL_FRAME] = frame;
	animTable[animName][ANIM_TBL_INV] = duration;
	animTable[animName][ANIM_TBL_LOOP] = loop;
	return true;
}

bool Obj::SetAnim(std::string animName)
{
	//d•¡Žž
	if (Obj::animName == animName)
	{
		return true;
	}
	//ÃÞ°À‚ª‘¶Ý‚µ‚È‚¢ê‡
	if (animTable.find(animName) == animTable.end())
	{
		return false;
	}
	Obj::animName = animName;
	Obj::animCnt = 0;	//±ÆÒ°¼®Ý•ÏX‚É‚æ‚éºÏ”‚Ì¸Ø±
	Obj::animEndFlag = false;
	return true;
}

std::string Obj::GetAnim(void)
{
	return animName;
}