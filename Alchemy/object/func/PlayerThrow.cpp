#include "PlayerThrow.h"

void PlayerThrow::operator()(Obj& player, std::vector<sharedObj>& objList)
{
	player.state(STATE::NORMAL);
}

