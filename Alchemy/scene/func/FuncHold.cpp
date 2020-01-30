#include "FuncHold.h"
#include <object/Player.h>
#include <_DebugConOut.h>

bool FuncHold::operator()(ActQueT & actQue, std::vector<sharedObj>& objList)
{
	if (actQue.second.tageObj().expired())
	{
		return false;
	}

	for (auto obj : objList)
	{
		if ((*obj).unitID() == UNIT_ID::PLAYER)
		{
			if (((Player&)(*obj))._plNum == ((Player&)actQue.second)._plNum)
			{
				//壺投げﾌﾗｸﾞをリセットするか
				//((Player&)actQue.second)._throwPot = true;
				((Player&)actQue.second)._holdList.emplace_back(((Player&)actQue.second)._tageObj.lock());

				auto holdenObj = ((Player&)actQue.second)._holdList.back(); // 持つオブジェ

				(*holdenObj)._holdPlayer = obj;
				(*holdenObj)._zOrder = INT_MAX;
				(*holdenObj)._height = 40.0 * ((Player&)actQue.second)._holdList.size();
				(*holdenObj).state(STATE::HOLDEN);
				(*holdenObj)._tageObj.reset();
				actQue.second.state(STATE::HOLD);

				return true;
			}
		}
	}
	return false;
}
