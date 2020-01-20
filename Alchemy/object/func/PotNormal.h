#pragma once
#include <vector>
#include "../Obj.h"

struct PotNormal
{
	void operator()(Obj&, std::vector<sharedObj>& objList);
};

