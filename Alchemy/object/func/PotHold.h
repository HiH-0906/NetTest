#pragma once
#include <vector>
#include "../Obj.h"

struct PotHold
{
	void operator()(Obj&, std::vector<sharedObj>& objList);
};

