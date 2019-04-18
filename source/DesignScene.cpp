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

	for (auto &data : (*objList))
	{
		data->UpDate(controller);
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
	AddObjList()(objList, std::make_unique<DesignCursor>(lpSceneMng.GetDrawOffset()));
	
	return 0;
}

void DesignScene::SelectDraw(void)
{

}

void DesignScene::DesignDraw(void)
{
	for (auto &itr : (*objList))
	{
		itr->Draw();
	}
}
