#include <algorithm>
#include "TargetDec.h"
#include <DIR.h>

bool TargetDec::operator()(Obj & master, std::vector<sharedObj>& objList, InputState & input)
{
	TEAM_TAG tageTeam = (master.teamTag() == TEAM_TAG::ENEMY_TEAM ? TEAM_TAG::ALLY_TEAM : TEAM_TAG::ENEMY_TEAM);
	if (master.tageObj().expired())
	{
		// ©•ª‚©‚ç‚Ì‹——£‚ª‹ß‚¢‡‚ÉobjList‚ğƒ\[ƒg
		std::sort(objList.begin(), objList.end(),
			[&](sharedObj objA, sharedObj objB) {
			return LengthSquare((*objA).pos(), master.pos()) < LengthSquare((*objB).pos(), master.pos());
		});

		for (auto obj : objList)
		{
			if ((master.searchRange() * master.searchRange()) > LengthSquare(master.pos(), (*obj).pos()))
			{
				if (tageTeam == (*obj).teamTag())
				{
					if ((*obj).state() <= STATE::ATTACK)
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
			else
			{
				return false;
			}
		}
	}

	return false;
}
