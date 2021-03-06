#pragma once
#include "BaseScene.h"
#include "classObj.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base UpDate(unique_Base own, const GameCtrl & controller);		// ゲーム中の動作処理

private:
	int Init();		// ゲームに関する初期化

	void Draw();	// ゲーム中の描画

	sharedListObj objList;	//obj用　ﾘｽﾄ
};