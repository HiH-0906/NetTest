#pragma once
#include <vector>
#include <object\Obj.h>


struct Slime_Attack
{
	void operator ()(Obj& obj, std::vector<sharedObj>& objList);
};

