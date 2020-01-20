#pragma once
#include <vector>
#include "../Obj.h"

struct PlayerThrow
{
	void operator()(Obj&, std::vector<sharedObj>& objList);
};
