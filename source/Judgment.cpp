#include "Judgment.h"
#include "Player.h"
//#include "Obstacle.h"
#include "Slope.h"
#include "Rectangle.h"
#include "Composite.h"


bool Judgment::CheckSpin(void)
{
	return false;
}

bool Judgment::CheckObstacle(void)
{
	// ��ڲ԰�̑O�ւƵ�޼ު�Ă�����������true

	// SLOPE�Ȃ����̊J�n�_�ƒ��_�A�����̊J�n�_�ƏI���_


	// RECTANGLE�Ȃ獶��ƉE��

	// COMPOSITE�̍��SLOPE�A��̓��͐ڒn����A���̂ʂ���݂͋�`�Q��


	return false;
}

bool Judgment::CheckIsGround(void)
{

	return false;
}

Judgment::Judgment()
{
}


Judgment::~Judgment()
{
}
