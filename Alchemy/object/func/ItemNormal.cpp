#include "ItemNormal.h"
#include "../Item.h"
#include <cmath>

void ItemNormal::operator()(Obj & obj, std::vector<sharedObj>& objList)
{
	auto tmpheight = std::abs(((Item&)obj).floatCnt() % 40 - 20) - 10;
	obj._height = static_cast<double>(tmpheight);

	
}
