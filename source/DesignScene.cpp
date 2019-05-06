#include "DesignScene.h"
#include "SceneMng.h"
#include "DesignCursor.h"
#include "CourceCtrl.h"
#include "GameCtrl.h"
#include "classObj.h"


DesignScene::DesignScene()
{
	Init();
}


DesignScene::~DesignScene()
{
}

unique_Base DesignScene::UpDate(unique_Base own, const GameCtrl & controller)
{
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);

	for (auto itr = objList->begin(); itr != objList->end(); ++itr)
	{
		(*itr)->UpDate(controller);
//		data->GetScroll();
	}

	DesignDraw();

	return move(own);
}

int DesignScene::Init()
{
	if (!objList)
	{
		objList = std::make_shared<uniqueObjList>();
	}
	objList->clear();
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpCourceCtrl.SetUp(VECTOR2(GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y), VECTOR2(BLOCK_SIZE_X, BLOCK_SIZE_Y), lpSceneMng.GetDrawOffset());
	AddObjList()(objList, std::make_unique<DesignCursor>(lpSceneMng.GetDrawOffset()));
	
	return 0;
}

void DesignScene::SelectDraw(void)
{

}

void DesignScene::DesignDraw(void)
{
	ClsDrawScreen();

	DrawString(0, 100, "GameArea", 0x00ffffff);
	DrawString(0, 600, "GameArea", 0x00ffffff);

	// ¶Ò×”ÍˆÍ‚©‚çŠ®‘S‚Éo‚½•”•ª‚Í•`‰æ‚µ‚È‚¢

	lpCourceCtrl.Draw(true);

	for (auto itr = objList->begin(); itr != objList->end(); ++itr)
	{
		(*itr)->Draw();
	}

	ScreenFlip();
}
