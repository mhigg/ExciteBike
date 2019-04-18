#pragma once
enum class OBJ_ID
{
	START,			// ｽﾀｰﾄ地点(Designﾓｰﾄﾞでは選択不可)
	BLANK,			// 障害物なし(Designﾓｰﾄﾞでは選択不可)
	SMALL,			// 小山 45度
	MEDIUM,			// 中山	45度
	LARGE,			// 大山 45度
	LOOSE,			// 小山 30度
	STEEP,			// 大山 60度
	L_TO_S,			// 緩から急
	S_TO_L,			// 急から緩
	JUMPER,			// ｼﾞｬﾝﾌﾟ台
	STEP_BACK,		// 段差 上
	STEP_NEAR,		// 段差 下
	MUDDY_BACK,		// ぬかるみ 上
	MUDDY_NEAR,		// ぬかるみ 下
	COOL_BACK,		// ｸｰﾙｿﾞｰﾝ 上
	COOL_NEAR,		// ｸｰﾙｿﾞｰﾝ 下
	TRACK_BACK,		// 芝ありﾄﾗｯｸ 上
	TRACK_NEAR,		// 芝ありﾄﾗｯｸ 下
	TRACK_NONE,		// 芝のみ
	MOUNTAIN,		// 二段山
	COMPOSITE,		// 複合地帯
	END,			// ﾗｯﾌﾟ・ｺﾞｰﾙ地点
	MAX
};

constexpr OBJ_ID PARTS_START = OBJ_ID::SMALL;

constexpr OBJ_ID PARTS_MAX = OBJ_ID::COMPOSITE;

OBJ_ID operator+(OBJ_ID id, OBJ_ID id2);

OBJ_ID operator-(OBJ_ID id, OBJ_ID id2);

OBJ_ID operator++(OBJ_ID id, int);

OBJ_ID operator--(OBJ_ID id, int);
