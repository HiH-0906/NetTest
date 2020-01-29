#pragma once
#include <vector>
#include "../Obj.h"

struct PlayerDeath
{
	void operator()(Obj&, std::vector<sharedObj>& objList);
};