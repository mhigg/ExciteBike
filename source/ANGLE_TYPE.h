#pragma once

enum class ANGLE_TYPE
{
	STEEP_FOW,		// 急な斜面(-60度くらい)
	MEDIUM_FOW,		// -50度くらい
	NORMAL_FOW,		// 普通の斜面(-45度くらい)
	LOOSE_FOW,		// 緩い斜面(-30度くらい)
	STRAIGHT,		// 傾いていない状態
	FINE,			// 15度くらい:ｳｨﾘｰ1段階目
	LOOSE,			// 緩い斜面(30度くらい):ｳｨﾘｰ2段階目
	NORMAL,			// 普通の斜面(45度くらい):ｳｨﾘｰ3段階目
	MEDIUM,			// 55度くらい:ｳｨﾘｰ4段階目
	STEEP,			// 急な斜面(60度くらい):ｳｨﾘｰ5段階目
	UPRIGHT,		// 90度:ｳｨﾘｰ6段階目
	MAX
};

// ANGLE_TYPEとint型の加算
ANGLE_TYPE operator+(ANGLE_TYPE& angle, int num);

// ANGLE_TYPE同士の加算
ANGLE_TYPE operator+(ANGLE_TYPE& a, ANGLE_TYPE& b);

// 前置型ｲﾝｸﾘﾒﾝﾄ
ANGLE_TYPE operator++(ANGLE_TYPE& angle);

// 後置型ｲﾝｸﾘﾒﾝﾄ
ANGLE_TYPE operator++(ANGLE_TYPE& angle, int);

// ANGLE_TYPEとint型の減算
ANGLE_TYPE operator-(ANGLE_TYPE& angle, int num);

// ANGLE_TYPE同士の減算
ANGLE_TYPE operator-(ANGLE_TYPE& a, ANGLE_TYPE& b);

// 前置型ﾃﾞｸﾘﾒﾝﾄ
ANGLE_TYPE operator--(ANGLE_TYPE& angle);

// 後置型ﾃﾞｸﾘﾒﾝﾄ
ANGLE_TYPE operator--(ANGLE_TYPE& angle, int);
