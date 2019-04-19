#pragma once
#include <memory>
#include "VECTOR2.h"

constexpr int GAME_SCREEN_X = 50;			// �`��I�t�Z�b�g
constexpr int GAME_SCREEN_Y = 265;

constexpr int GAME_SCREEN_SIZE_X = 16000;	// �Q�[���G���A�̃T�C�Y(1��ۯ�16�~100��ۯ���)
constexpr int GAME_SCREEN_SIZE_Y = 300;

constexpr int LANE_WIDTH = 50;				// ڰ�1�̕�(��ڲ԰�̕��̔���)

constexpr int BLOCK_SIZE_X = 16;
constexpr int BLOCK_SIZE_Y = 112;


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