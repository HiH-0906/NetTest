#include <_DebugConOut.h>
#include "FuncIntoPot.h"
#include <object/Pot.h>

bool FuncIntoPot::operator()(ActQueT& actQue, std::vector<sharedObj>& objList)
{
	auto pot = actQue.second._tageObj.lock();

	if ((*pot)._unitID != UNIT_ID::POT)
	{
		AST();
		return false;
	}

	MixData data = { actQue.second._unitID,actQue.second.getType() };

	((Pot&)(*pot)).AddMixList(data);
	(*pot).state(STATE::HOLD);
	actQue.second.state(STATE::NORMAL);
	actQue.second._tageObj.reset();
	actQue.second._dead = true;

	return true;
}