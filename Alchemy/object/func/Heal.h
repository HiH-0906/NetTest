#pragma once
#include <vector>
#include <object\Obj.h>

struct Heal
{
	void operator ()(Obj& obj, std::vector<sharedObj>& objList);
};

