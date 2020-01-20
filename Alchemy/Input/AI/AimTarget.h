#pragma once
#include <object/Obj.h>
#include <Input/InputState.h>

struct AimTarget
{
	bool operator()(Obj& master, std::vector<sharedObj>& objList, InputState& input);
};

