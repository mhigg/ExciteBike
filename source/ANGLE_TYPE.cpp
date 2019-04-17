#include <type_traits>
#include "ANGLE_TYPE.h"



ANGLE_TYPE operator+(ANGLE_TYPE & angle, int num)
{
	return static_cast<ANGLE_TYPE>(static_cast<int>(angle) + num);
}

ANGLE_TYPE operator+(ANGLE_TYPE & a, ANGLE_TYPE & b)
{
	return static_cast<ANGLE_TYPE>(static_cast<int>(a) + static_cast<int>(b));
}

ANGLE_TYPE operator++(ANGLE_TYPE & angle)
{
	angle = angle + 1;
	return angle;
}

ANGLE_TYPE operator++(ANGLE_TYPE& angle, int)
{
	ANGLE_TYPE tmpAngle = angle;
	++angle;
	return tmpAngle;
}

ANGLE_TYPE operator-(ANGLE_TYPE & angle, int num)
{
	return static_cast<ANGLE_TYPE>(static_cast<int>(angle) - num);
}

ANGLE_TYPE operator-(ANGLE_TYPE & a, ANGLE_TYPE & b)
{
	return static_cast<ANGLE_TYPE>(static_cast<int>(a) - static_cast<int>(b));
}

ANGLE_TYPE operator--(ANGLE_TYPE & angle)
{
	angle = angle - 1;
	return angle;
}

ANGLE_TYPE operator--(ANGLE_TYPE & angle, int)
{
	ANGLE_TYPE tmpAngle = angle;
	--angle;
	return tmpAngle;
}
