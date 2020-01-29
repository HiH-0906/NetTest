#include "HealTagDec.h"

bool HealTagDec::operator()(Obj & master, std::vector<sharedObj>& objList, InputState & input)
{
	TEAM_TAG tageTeam = (master.teamTag() == TEAM_TAG::ENEMY_TEAM ? TEAM_TAG::ENEMY_TEAM : TEAM_TAG::ALLY_TEAM);
	for (auto obj : objList)
	{
		if (master.getType() != (*obj).getType())
		{
			if (tageTeam == (*obj).teamTag())
			{
				if ((master.searchRange() * master.searchRange()) > LengthSquare(master.pos(), (*obj).pos()))
				{
					if ((*obj)._hp >= (*obj)._hpMax)
					{
						if ((*obj).state() == STATE::NORMAL || (*obj).state() == STATE::ATTACK || (*obj).state() == STATE::HOLD)
						{
							if (master.tageObj().expired())
							{
								StickState state;
								state.isInput = true;
								state.angle = static_cast<short>DEG(atan2((*obj).pos().y - master.pos().y, (*obj).pos().x - master.pos().x));
								state.dir = convToDir(state.angle);
								input.LStickState(state);
								master.SetTageObj(obj);
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}
