#pragma once
#include <memory>

#define GAME_SCREEN_X 0				// �`��I�t�Z�b�g
#define GAME_SCREEN_Y 0

#define GAME_SCREEN_SIZE_X 600		// �Q�[���G���A�̃T�C�Y
#define GAME_SCREEN_SIZE_Y 600

#define CHIP_SIZE 50				//1Ͻ�̻���(�c�����p)

class BaseScene;
class GameCtrl;

using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	virtual ~BaseScene();
	virtual unique_Base UpDate(unique_Base own, const GameCtrl &controller) = 0;

private:
	virtual int Init() = 0;

};