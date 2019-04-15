#pragma once
#include <memory>

constexpr int GAME_SCREEN_X = 0;			// �`��I�t�Z�b�g
constexpr int GAME_SCREEN_Y = 100;

constexpr int GAME_SCREEN_SIZE_X = 1200;	// �Q�[���G���A�̃T�C�Y
constexpr int GAME_SCREEN_SIZE_Y = 500;

constexpr int LANE_WIDTH = 50;				// ڰ�1�̕�(��ڲ԰�̕��̔���)

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