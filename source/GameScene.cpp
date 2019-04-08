#include <DxLib.h>
#include "GameScene.h"
#include "SceneMng.h"
#include "Obj.h"
#include "GameCtrl.h"
#include "classObj.h"


GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
}

int GameScene::Init()
{
	if (!objList)
	{
		objList = std::make_shared<sharedObjList>();
	}
	objList->clear();
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));

	return 0;
}

void GameScene::Draw()
{
	ClsDrawScreen();

	DrawString(200, 200, "Hello World!", 0x00ffffff);

	ScreenFlip();
}

unique_Base GameScene::UpDate(unique_Base own, const GameCtrl & controller)
{
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);

	// ƒvƒŒƒCƒ„[‚Ì“®ìˆ—
	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpDate(controller, objList);
	}

	Draw();

	return move(own);
}
