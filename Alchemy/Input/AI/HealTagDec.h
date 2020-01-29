#pragma once
#include <Input/InputState.h>
#include <object/Obj.h>
struct HealTagDec
{
	bool operator()(Obj& master, std::vector<sharedObj>& objList, InputState& input);
};

