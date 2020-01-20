#include <type_traits>
#include "STATE.h"

STATE begin(STATE)
{
	return STATE::NORMAL;
};

STATE end(STATE)
{
	return STATE::MAX;
};

STATE operator++(STATE type)
{
	if (type != STATE::MAX)
	{
		type = static_cast<STATE>(std::underlying_type<STATE>::type(type) + 1);
	}
	return type;
}

STATE operator*(STATE type)
{
	return type;
}
