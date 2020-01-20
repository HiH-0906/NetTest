#pragma once
#include <vector>
#include "../Obj.h"

struct PlayerHold
{
	void operator()(Obj&, std::vector<sharedObj>& objList);
};
