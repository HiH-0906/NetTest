#include "TestEnemyUpdate.h"
#include <Input/InputState.h>

void TestEnemyUpdate::operator()(Obj& obj, std::vector<sharedObj>& objList)
{
	/*for (auto id : INPUT_ID())
	{
		if ((*obj._input).btnState(id).first && !(*obj._input).btnState(id).second)
		{
			TRACE("%dÇÃÉLÅ[Ç™âüÇ≥ÇÍÇ‹ÇµÇΩ\n", static_cast<int>(id));
		}
	}*/

	if ((*obj._input).LStickState().first.isInput)
	{
		obj._rad = RAD(static_cast<double>((*obj._input).LStickState().first.angle));
		obj._pos += {2.0 * cos(obj._rad), 2.0 * sin(obj._rad)};

		obj.dir((*obj._input).LStickState().first.dir);
	}
}
