#pragma once
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

	bool SetUp();

	// GameModeのみ、ﾌﾟﾚｲﾔｰをｲﾝｽﾀﾝｽする関数 1体ｲﾝｽﾀﾝｽしたら2体目以降はｲﾝｽﾀﾝｽされない
	// modeFlag:true→EditMode false→GameMode
	bool SetUpGameObj(sharedListObj objList, bool modeFlag);

//	bool SetCourceData(VECTOR2 pos, )

private:
	CourceCtrl();
	~CourceCtrl();

	VECTOR2 drawOffset;
};

