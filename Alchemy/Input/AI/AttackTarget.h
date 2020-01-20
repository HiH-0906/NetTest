#pragma once
#include <object/Obj.h>
#include <Input/InputState.h>

struct AttackTarget
{
	bool operator()(Obj& master, std::vector<sharedObj>& objList, InputState& input);
};

