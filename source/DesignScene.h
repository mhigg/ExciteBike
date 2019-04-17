#pragma once
#include "BaseScene.h"
#include "classObj.h"

class DesignScene :
	public BaseScene
{
public:
	DesignScene();
	~DesignScene();

	unique_Base UpDate(unique_Base own, const GameCtrl &controller);

private:
	int Init();

	void SelectDraw(void);
	void DesignDraw(void);

	sharedListObj objList;
};

