#pragma once
#include <vector>
#include <object\Obj.h>

struct BossAttack
{
	void operator ()(Obj& obj, std::vector<sharedObj>& objList);
};


