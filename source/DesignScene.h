#pragma once
#include "BaseScene.h"
class DesignScene :
	public BaseScene
{
public:
	DesignScene();
	~DesignScene();

	unique_Base UpDate(unique_Base own, const GameCtrl &controller);

private:
	int Init();

};

