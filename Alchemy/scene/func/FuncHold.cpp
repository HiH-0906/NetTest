#include "FuncHold.h"
#include <object/Player.h>
#include <_DebugConOut.h>

bool FuncHold::operator()(ActQueT & actQue, std::vector<sharedObj>& objList)
{
	for (auto obj : objList)
	{
		if ((*obj).unitID() == UNIT_ID::PLAYER)
		{
			if (((Player&)(*obj))._plNum == ((Player&)actQue.second)._plNum)
			{
				((Player&)actQue.second)._holdList.emplace_back(((Player&)actQue.second)._tageObj);

				auto holdenObj = ((Player&)actQue.second)._holdList.back(); // 持つオブジェ

				(*holdenObj)._holdPlayer = obj;
				(*holdenObj)._height = 30.0;
				(*holdenObj).state(STATE::HOLDEN);
				(*holdenObj)._tageObj.reset();
				actQue.second.state(STATE::HOLD);

				return true;
			}
		}
	}
	return false;
}
