#include <DxLib.h>
#include "TitleScene.h"
#include "GameScene.h"
#include "DesignScene.h"
#include "GameCtrl.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::UpDate(unique_Base own, const GameCtrl & controller)
{
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);

	if (ctrl[KEY_INPUT_SPACE] & ~ctrlOld[KEY_INPUT_SPACE])
	{
		return std::make_unique<DesignScene>();
	}

	return move(own);
}

int TitleScene::Init(void)
{
	mode = MODE_SINGLE;
	return 0;
}
