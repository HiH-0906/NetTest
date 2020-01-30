#include "FuncPut.h"
#include <object/Player.h>
#include <_DebugConOut.h>

bool FuncPut::operator()(ActQueT& actQue, std::vector<sharedObj>& objList)
{
	if (actQue.second.unitID() == UNIT_ID::PLAYER)
	{
		Player& player = ((Player&)actQue.second);
		auto thrownObj = player._holdList.front();

		(*thrownObj)._height = 0;
		(*thrownObj)._zOrder = 0;
		(*thrownObj).state(STATE::NORMAL);

		player.state(STATE::THROW);
		player._holdList.erase(player._holdList.begin());

		for (int i = 0; i < player._holdList.size(); i++)
		{
			(*player._holdList[i])._height = 40.0 * (i + 1);
		}
	}
	else
	{
		AST();
	}

	return true;
}
