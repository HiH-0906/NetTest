#include <type_traits>
#include "ENEMY_TYPE.h"


ENEMY_TYPE begin(ENEMY_TYPE)
{
	return ENEMY_TYPE::SLIME;
};

ENEMY_TYPE end(ENEMY_TYPE)
{
	return ENEMY_TYPE::MAX;
};

ENEMY_TYPE operator++(ENEMY_TYPE type)
{
	if (type != ENEMY_TYPE::MAX)
	{
		type = static_cast<ENEMY_TYPE>(std::underlying_type<ENEMY_TYPE>::type(type) + 1);
	}
	return type;
}

ENEMY_TYPE operator*(ENEMY_TYPE type)
{
	return type;
}
