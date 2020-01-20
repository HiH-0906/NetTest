#pragma once
#include <vector>
#include "../Obj.h"

struct PlayerNormal
{
	void operator()(Obj&, std::vector<sharedObj>& objList);
};

