#include <DxLib.h>
#include <Windows.h>
#include "SceneMng.h"
#include "ImageMng.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	lpSceneMng.Run();

	DxLib_End();	// DXײ���؂̏I������
	return 0;
}