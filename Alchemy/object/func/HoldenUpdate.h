#pragma once
#include <vector>
#include "../Obj.h"

// Obj‚ÌSTATE‚ªHOLDEN(‚½‚ê‚Ä‚¢‚é)ó‘Ô‚Ì‚ÌUpdateŠÖ”
struct HoldenUpdate
{
	void operator()(Obj&, std::vector<sharedObj>& objList);
};

