#pragma once
#include "../InputState.h"
#include "object/Obj.h"

struct TargetDec
{
	bool operator()(Obj& master, std::vector<sharedObj>& objList, InputState& input);
};

