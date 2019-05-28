#include <DxLib.h>
#include <memory>
#include "GameScene.h"
#include "DesignScene.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "Obj.h"
#include "Player.h"
#include "GameCtrl.h"
#include "CourceCtrl.h"
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
		objList = std::make_shared<uniqueObjList>();
	}
	objList->clear();
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpCourceCtrl.SetUp(VECTOR2(GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y), VECTOR2(BLOCK_SIZE_X, BLOCK_SIZE_Y), lpSceneMng.GetDrawOffset());
	lpCourceCtrl.SetUpGameObj(objList, false);

	return 0;
}

void GameScene::Draw()
{
	ClsDrawScreen();

	DrawString(0, 100, "GameArea", 0x00ffffff);
	DrawString(0, 600, "GameArea", 0x00ffffff);

	// ｶﾒﾗ範囲から完全に出た部分は描画しない

	lpCourceCtrl.Draw(false);

	for (auto itr = objList->begin(); itr != objList->end(); ++itr)
	{
		(*itr)->Draw();
	}

	DrawGraph(0, 480 - 117, lpImageMng.GetID("image/info.png")[0], true);

	ScreenFlip();
}

unique_Base GameScene::UpDate(unique_Base own, const GameCtrl & controller)
{
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);

	// プレイヤーの動作処理
	for (auto itr = objList->begin(); itr != objList->end(); ++itr)
	{
		(*itr)->UpDate(controller);
	}

	if (ctrl[KEY_INPUT_SPACE] & ~ctrlOld[KEY_INPUT_SPACE])
	{
		return std::make_unique<DesignScene>();
	}

	Draw();

	return move(own);
}
