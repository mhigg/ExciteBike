#pragma once
#include "BaseScene.h"
#include "classObj.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base UpDate(unique_Base own, const GameCtrl & controller);		// ƒQ[ƒ€’†‚Ì“®ìˆ—

private:
	int Init();		// ƒQ[ƒ€‚ÉŠÖ‚·‚é‰Šú‰»

	void Draw();	// ƒQ[ƒ€’†‚Ì•`‰æ

	sharedListObj objList;	//obj—p@Ø½Ä
};