#include <type_traits>
#include "UNIT_ID.h"

UNIT_ID bigin(UNIT_ID())
{
	return UNIT_ID::NON;
}

UNIT_ID end(UNIT_ID())
{
	return UNIT_ID::FOLLOWER;
}

UNIT_ID operator*(UNIT_ID key)
{
	return key;
}

UNIT_ID operator++(UNIT_ID & key)
{
	return key = static_cast<UNIT_ID>(std::underlying_type<UNIT_ID>::type(key) + 1);
}
