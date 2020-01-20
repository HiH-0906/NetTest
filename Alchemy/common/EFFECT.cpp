#include <type_traits>
#include "EFFECT.h"


EFFECT begin(EFFECT)
{
	return EFFECT::DASH;
}

EFFECT end(EFFECT)
{
	return EFFECT::MAX;
}

EFFECT operator++(EFFECT & effect)
{
	if (effect != EFFECT::MAX)
	{
		effect = static_cast<EFFECT>(std::underlying_type<EFFECT>::type(effect) + 1);
	}
	return effect;
}

EFFECT operator*(EFFECT effect)
{
	return effect;
}
