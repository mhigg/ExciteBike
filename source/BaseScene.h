#pragma once
#include <memory>

#define GAME_SCREEN_X 0				// 描画オフセット
#define GAME_SCREEN_Y 100

#define GAME_SCREEN_SIZE_X 1200		// ゲームエリアのサイズ
#define GAME_SCREEN_SIZE_Y 500

#define LANE_WIDTH 50				// ﾚｰﾝ1つの幅(ﾌﾟﾚｲﾔｰの幅の半分)

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