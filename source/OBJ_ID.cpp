#include "OBJ_ID.h"



OBJ_ID operator+(OBJ_ID id, OBJ_ID id2)
{
	return static_cast<OBJ_ID>(static_cast<int>(id) + static_cast<int>(id2));
}

OBJ_ID operator-(OBJ_ID id, OBJ_ID id2)
{
	return static_cast<OBJ_ID>(static_cast<int>(id) - static_cast<int>(id2));
}

OBJ_ID operator++(OBJ_ID id, int)
{
	return static_cast<OBJ_ID>(static_cast<int>(id) + 1);
}

OBJ_ID operator--(OBJ_ID id, int)
{
	return static_cast<OBJ_ID>(static_cast<int>(id) - 1);
}
