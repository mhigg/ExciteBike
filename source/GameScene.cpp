#include <DxLib.h>
#include "GameScene.h"
#include "SceneMng.h"
#include "Obj.h"
#include "Player.h"
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
//	AddObjList()(objList, std::make_unique<Player>((0.0f, 0.0f, 0.0f), 500));
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));

	return 0;
}

void GameScene::Draw()
{
	ClsDrawScreen();

	DrawString(0, 100, "GameArea", 0x00ffffff);
	DrawString(0, 600, "GameArea", 0x00ffffff);

	ScreenFlip();
}

unique_Base GameScene::UpDate(unique_Base own, const GameCtrl & controller)
{
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);

	// �v���C���[�̓��쏈��
	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpDate(controller, objList);
	}

	Draw();

	return move(own);
}
