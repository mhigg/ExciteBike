#pragma once
enum class ANGLE_TYPE
{
	STRAIGHT,		// 傾いていない状態
	FINE,			// 15度くらい:ｳｨﾘｰ1段階目
	LOOSE,			// 緩い斜面(30度くらい):ｳｨﾘｰ2段階目
	NORMAL,			// 普通の斜面(45度くらい):ｳｨﾘｰ3段階目
	MEDIUM,			// 55度くらい:ｳｨﾘｰ4段階目
	STEEP,			// 急な斜面(60度くらい):ｳｨﾘｰ5段階目
	UPRIGHT,		// 90度:ｳｨﾘｰ6段階目
	LOOSE_DOWN,
	MAX
};

// FIRE_DIRの先頭を返す
ANGLE_TYPE begin(ANGLE_TYPE);

// FIRE_DIRの最後尾を返す
ANGLE_TYPE end(ANGLE_TYPE);

// ｲﾝｸﾘﾒﾝﾄ
ANGLE_TYPE operator++(ANGLE_TYPE& dir);

// 参照のｱﾄﾞﾚｽをそのまま返す	
ANGLE_TYPE operator*(ANGLE_TYPE& dir);