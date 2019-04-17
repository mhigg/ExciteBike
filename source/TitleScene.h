#pragma once
#include "BaseScene.h"

enum MODE {
	MODE_SINGLE,
	MODE_MATCH,
	MODE_DESIGN,
	MODE_MAX
};

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	unique_Base UpDate(unique_Base own, const GameCtrl &controller);

private:
	int Init(void);
	MODE mode;
};

