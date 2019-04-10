#include <memory>
#include <DxLib.h>
#include "CourceCtrl.h"
#include "SceneMng.h"
#include "Player.h"
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
}

bool CourceCtrl::SetUpGameObj(sharedListObj objList, bool modeFlag)
{
	if (modeFlag)
	{

	}
	else
	{
//		sharedObj objPtr = std::make_unique<Player>(drawOffset);
	}
	return false;
}
