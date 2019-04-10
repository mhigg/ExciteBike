#pragma once
#include <list>
#include "BaseScene.h"
#include "GameCtrl.h"
#include "VECTOR2.h"

#define lpSceneMng SceneMng::GetInstance()

class Obj;

using ListObj_itr = std::list<Obj>::iterator;

class SceneMng
{
public:
	static SceneMng& GetInstance(void)
	{
		static SceneMng s_instance;
		return s_instance;
	}

	void Run(void);							// ゲームループ
	VECTOR2 GetScreenSize(void);			// 画面のサイズを取得
	VECTOR2 GetGameScreenSize(void);		// ゲームエリアのサイズを取得
	void SetDrawOffset(VECTOR2 drawOffset);

private:
	SceneMng();
	int Init(void);		// ゲーム全体的な初期化

	VECTOR2 drawOffset;	// 描画オフセット
	int framCnt;		// 経過フレーム数

	unique_Base activeScene;
	std::unique_ptr<GameCtrl> gameCtrl;
};

