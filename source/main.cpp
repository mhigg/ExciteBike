#include <DxLib.h>
#include <Windows.h>
#include "SceneMng.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SceneMng::GetInstance().Run();

	DxLib_End();	// DXײ���؂̏I������
	return 0;
}