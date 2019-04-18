#include <DxLib.h>
#include "SceneMng.h"
#include "BaseScene.h"
#include "GameScene.h"
#include "VECTOR2.h"

constexpr int SCREEN_SIZE_X = 1200;
constexpr int SCREEN_SIZE_Y = 800;

//#define SCREEN_SIZE_X 1200			//âÊñ âëúìx
//#define SCREEN_SIZE_Y 800


SceneMng::SceneMng()
{
	Init();
}

void SceneMng::Run(void)
{
	activeScene = std::make_unique<GameScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		gameCtrl->UpDate();
		activeScene = activeScene->UpDate(std::move(activeScene), (*gameCtrl));
		framCnt++;
	}
}

VECTOR2 SceneMng::GetScreenSize(void)
{
	return VECTOR2(SCREEN_SIZE_X, SCREEN_SIZE_Y);
}

VECTOR2 SceneMng::GetGameScreenSize(void)
{
	return VECTOR2(GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y);
}

VECTOR2 SceneMng::GetDrawOffset(void)
{
	return drawOffset;
}

void SceneMng::SetDrawOffset(VECTOR2 drawOffset)
{
	this->drawOffset = drawOffset;
}

int SceneMng::GetFram(bool timeFlag)
{
	if (timeFlag)
	{
		return (framCnt / 60);
	}
	return framCnt;
}

int SceneMng::Init(void)
{
	SetWindowText("ExciteBike_ãvï€éRèÆãP");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	framCnt = 0;

	gameCtrl = std::make_unique<GameCtrl>();

	return 0;
}