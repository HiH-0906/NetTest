#pragma once
#include <vector>
#include "../Obj.h"

struct PotThrow
{
	void operator()(Obj&, std::vector<sharedObj>& objList);
};

