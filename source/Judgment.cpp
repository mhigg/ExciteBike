#include "Judgment.h"
#include "Player.h"
//#include "Obstacle.h"
#include "Slope.h"
#include "Rectangle.h"
#include "Composite.h"


bool Judgment::CheckSpin(void)
{
	return false;
}

bool Judgment::CheckObstacle(void)
{
	// ﾌﾟﾚｲﾔｰの前輪とｵﾌﾞｼﾞｪｸﾄが当たったらtrue

	// SLOPEなら上り坂の開始点と頂点、下り坂の開始点と終了点


	// RECTANGLEなら左上と右下

	// COMPOSITEの坂はSLOPE、上の道は接地判定、下のぬかるみは矩形２回


	return false;
}

bool Judgment::CheckIsGround(void)
{

	return false;
}

Judgment::Judgment()
{
}


Judgment::~Judgment()
{
}
