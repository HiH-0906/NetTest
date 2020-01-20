#include <type_traits>
#include "PlNum.h"

PlNum begin(PlNum)
{
	return PlNum::PL_01;
}

PlNum end(PlNum)
{
	return PlNum::PL_MAX;
}

PlNum operator*(PlNum num)
{
	return num;
}

PlNum operator++(PlNum & num)
{
	return num = static_cast<PlNum>(std::underlying_type<PlNum>::type(num) + 1);
}
