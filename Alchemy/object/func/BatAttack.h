#pragma once
#include <vector>
#include <object\Obj.h>

struct BatAttack
{
	void operator ()(Obj& obj, std::vector<sharedObj>& objList);
};
