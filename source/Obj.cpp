#include <DxLib.h>
#include "Obj.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "classObj.h"

Obj::Obj()
{
}

Obj::Obj(VECTOR2 drawOffset) :drawOffset(drawOffset)
{
	//���̺ݽ�׸����Ăяo���ꂽ�u�Ԑ^�����drawOffset�������������
}

//������
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

Obj::~Obj()
{

}

void Obj::UpDate(const GameCtrl &controller)
{
	SetMove(controller);
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
		id = (animTable[animName][ANIM_TBL_START_ID])
		  + ((animCnt / animTable[animName][ANIM_TBL_INV]) % animTable[animName][ANIM_TBL_FRAME]);
	}
	animCnt++;
	if (id < IMAGE_ID(imageName).size())
	{
		DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y, IMAGE_ID(imageName)[id], true);
	}
}

void Obj::Draw(unsigned int id)
{
	if (id < IMAGE_ID(imageName).size())
	{
		DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y, IMAGE_ID(imageName)[id], true);
	}
}

const VECTOR & Obj::GetPos(void)
{
	return pos;
}

void Obj::SetPos(VECTOR pos)
{
	Obj::pos = pos;
}

bool Obj::AddAnim(std::string animName, int id_x, int id_y, int frame, int inv)
{
	animTable[animName][ANIM_TBL_START_ID] = id_y * divCnt.x + id_x;
	animTable[animName][ANIM_TBL_FRAME] = frame;
	animTable[animName][ANIM_TBL_INV] = inv;
	return true;
}

bool Obj::SetAnim(std::string animName)
{
	//�d����
	if (Obj::animName == animName)
	{
		return true;
	}
	//�ް������݂��Ȃ��ꍇ
	if (animTable.find(animName) == animTable.end())
	{
		return false;
	}
	Obj::animName = animName;
	Obj::animCnt = 0;	//��Ұ��ݕύX�ɂ��ϐ��̸ر
	return true;
}

std::string Obj::GetAnim(void)
{
	return animName;
}

