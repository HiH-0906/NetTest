#include <type_traits>
#include "DIR.h"

DIR begin(DIR)
{
	return DIR::LEFT;
}

DIR end(DIR)
{
	return DIR::MAX;
}

DIR operator++(DIR& id)
{
	if (id != DIR::MAX)
	{
		id = static_cast<DIR>(std::underlying_type<DIR>::type(id) + 1);
	}
	return id;
}

DIR operator*(DIR id)
{
	return id;
}

DIR convToDir(double rad)
{
	return static_cast<DIR>(((static_cast<int>(DEG(rad)) + 180 + 45) / 90) % static_cast<int>(end(DIR())));
}

DIR convToDir(int angle)
{
	return static_cast<DIR>(((angle + 180 + 45) / 90) % static_cast<int>(end(DIR())));
}

double convToRad(DIR dir)
{
	
	return RAD(static_cast<int>(dir) * 90 - 180);
}

int convToAngle(DIR dir)
{
	return (static_cast<int>(dir) * 90 - 180);
}
