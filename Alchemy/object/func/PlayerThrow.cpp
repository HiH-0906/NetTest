#include "PlayerThrow.h"
#include "../Player.h"
void PlayerThrow::operator()(Obj& player, std::vector<sharedObj>& objList)
{
	if (((Player&)player).GetHoldListSize())
	{
		player.state(STATE::HOLD);
	}
	else
	{
		player.state(STATE::NORMAL);

	}
}

