#include <DxLib.h>
#include "DesignCursor.h"
#include "Obj.h"
#include "ImageMng.h"
#include "CourceCtrl.h"
#include "GameCtrl.h"


DesignCursor::DesignCursor()
{
	id = PARTS_START;
}

DesignCursor::DesignCursor(VECTOR2 drawOffset):Obj(drawOffset)
{
	id = PARTS_START;
}


DesignCursor::~DesignCursor()
{
}

void DesignCursor::SetMove(const GameCtrl & controller)
{
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);

	if (ctrl[KEY_INPUT_Z] | ctrl[KEY_INPUT_X])
	{
		pos.x += SPEED;
	}

	if (ctrl[KEY_INPUT_RIGHT])
	{
		inputFram++;
		if (inputFram >= KEY_GET_RNG)
		{
			id = id + (id > PARTS_MAX ? PARTS_START : static_cast<OBJ_ID>(1));
			inputFram = 0;
		}
	}

	if (ctrl[KEY_INPUT_LEFT])
	{
		inputFram++;
		if (inputFram >= KEY_GET_RNG)
		{
			id = id - (id < PARTS_START ? PARTS_MAX : static_cast<OBJ_ID>(1));
			inputFram = 0;
		}
	}

	if (ctrl[KEY_INPUT_SPACE] & ~(ctrlOld[KEY_INPUT_SPACE]))
	{
		// ëÊÇPà¯êîóvèCê≥
		lpCourceCtrl.SetCourceData(VECTOR2(pos.x, pos.y), id);
	}

	_RPTN(_CRT_WARN, "ID:%d\n", static_cast<int>(id));
}

void DesignCursor::Draw(void)
{
	lpImageMng.GetActID("image/player.act", "Wait");
}

bool DesignCursor::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_CURSOR);
}

bool DesignCursor::CheckAngleType(ANGLE_TYPE type)
{
	return (type == ANGLE_TYPE::STRAIGHT);
}
