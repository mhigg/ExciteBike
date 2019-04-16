#include <type_traits>
#include "ANGLE_TYPE.h"


ANGLE_TYPE begin(ANGLE_TYPE)
{
	return ANGLE_TYPE(0);
}

ANGLE_TYPE end(ANGLE_TYPE)
{
	return ANGLE_TYPE::MAX;
}

ANGLE_TYPE operator++(ANGLE_TYPE& angle)
{
	return angle = ANGLE_TYPE(std::underlying_type<ANGLE_TYPE>::type(angle) + 1);
}

ANGLE_TYPE operator*(ANGLE_TYPE& angle)
{
	return angle;
}
