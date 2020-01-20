#pragma once
#include <input/InputState.h>
#include <object/Obj.h>

struct HeadPot
{
	bool operator()(Obj& master, std::vector<sharedObj>& objList, InputState& input);
};

