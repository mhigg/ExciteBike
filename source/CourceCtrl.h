#pragma once
#include "classObj.h"
#include "VECTOR2.h"

#define lpCourceCtrl = CourceCtrl::GetInstance()

class CourceCtrl
{
public:
	static CourceCtrl & GetInstance(void)
	{
		static CourceCtrl s_instance;
		return s_instance;
	}

	// æ“¾‚µ‚½î•ñ(mapData)‚ğ‚à‚Æ‚É•`‰æ modeFlag:true¨EditMode false¨GameMode
	void Draw(bool modeFlag);

	// GameMode‚Ì‚İAÌßÚ²Ô°‚ğ²İ½Àİ½‚·‚éŠÖ” 1‘Ì²İ½Àİ½‚µ‚½‚ç2‘Ì–ÚˆÈ~‚Í²İ½Àİ½‚³‚ê‚È‚¢
	// modeFlag:true¨EditMode false¨GameMode
	bool SetUpGameObj(sharedListObj objList, bool modeFlag);

private:
	CourceCtrl();
	~CourceCtrl();

	VECTOR2 drawOffset;
};

