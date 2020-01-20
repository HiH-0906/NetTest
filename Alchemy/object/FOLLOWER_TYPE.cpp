#include <type_traits>
#include "FOLLOWER_TYPE.h"

FOLLOWER_TYPE begin(FOLLOWER_TYPE)
{
	return FOLLOWER_TYPE::OCTOPUS;
};

FOLLOWER_TYPE end(FOLLOWER_TYPE)
{
	return FOLLOWER_TYPE::MAX;
};

FOLLOWER_TYPE operator++(FOLLOWER_TYPE type)
{
	if (type != FOLLOWER_TYPE::MAX)
	{
		type = static_cast<FOLLOWER_TYPE>(std::underlying_type<FOLLOWER_TYPE>::type(type) + 1);
	}
	return type;
}

FOLLOWER_TYPE operator*(FOLLOWER_TYPE type)
{
	return type;
}
