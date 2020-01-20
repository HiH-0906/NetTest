#pragma once
#include <vector>
#include "../Obj.h"

struct TestEnemyUpdate
{
	void operator()(Obj&, std::vector<sharedObj>& objList);
};

