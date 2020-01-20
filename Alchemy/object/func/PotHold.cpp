#include <_DebugConOut.h>
#include "PotHold.h"
#include "../Pot.h"
#include "../FOLLOWER_TYPE.h"

void PotHold::operator()(Obj& pot, std::vector<sharedObj>& objList)
{
	if (((Pot&)pot)._mixList.empty())
	{
		AST();
		pot.state(STATE::NORMAL);
		return;
	}

	if (--((Pot&)pot)._comboCnt <= 0)
	{
		for (auto mixData : ((Pot&)pot)._mixList)
		{
			UNIT_ID checkID;
			int type;
			std::tie(checkID, type) = mixData;
			if (checkID != UNIT_ID::PLAYER)
			{
				((Pot&)pot)._throwList.emplace_back(lpSceneMng.serialNumCnt());
				lpSceneMng.AddInstanceQue({ UNIT_ID::FOLLOWER, static_cast<int>(FOLLOWER_TYPE::OCTOPUS),pot._pos,0 });
			}
		}
		lpSceneMng.AddActQue({ ACT_QUE::THOROW , pot });
		((Pot&)pot)._mixList.clear();
	}
}

