#pragma once
#include <vector>
#include <array>
#include "OBJ_ID.h"
#include "classObj.h"
#include "VECTOR2.h"

#define lpCourceCtrl CourceCtrl::GetInstance()

class CourceCtrl
{
public:
	static CourceCtrl & GetInstance(void)
	{
		static CourceCtrl s_instance;
		return s_instance;
	}

	// 取得した情報(mapData)をもとに描画 modeFlag:true→EditMode false→GameMode
	void Draw(bool modeFlag);

	// ｺｰｽの全長を準備する:ｽﾀｰﾄ地点と最低限(画面3個分くらい)のﾌﾞﾗﾝｸ部分
	bool SetUp(VECTOR2 mapSize, VECTOR2 blockSize, VECTOR2 drawOffset);

	// GameModeのみ、ﾌﾟﾚｲﾔｰをｲﾝｽﾀﾝｽする関数 1体ｲﾝｽﾀﾝｽしたら2体目以降はｲﾝｽﾀﾝｽされない
	// modeFlag:true→EditMode false→GameMode
	bool SetUpGameObj(sharedListObj objList, bool modeFlag);

	bool SetCourceData(VECTOR2 pos, OBJ_ID id);

	void SetScroll(int distance);

private:
	CourceCtrl();
	~CourceCtrl();

	std::vector<OBJ_ID> courceData;

	std::array<std::string, static_cast<int>(OBJ_ID::MAX)> actNameTbl;

	VECTOR2 mapSize;		// ｺｰｽ内の設置ﾌﾞﾛｯｸ数
	VECTOR2 blockSize;
	VECTOR2 drawOffset;
	int scrollOffsetX;
};

