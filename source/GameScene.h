#pragma once
#include "BaseScene.h"
#include "classObj.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base UpDate(unique_Base own, const GameCtrl & controller);		// �Q�[�����̓��쏈��

private:
	int Init();		// �Q�[���Ɋւ��鏉����

	void Draw();	// �Q�[�����̕`��

	sharedListObj objList;	//obj�p�@ؽ�
};