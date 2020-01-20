#pragma once
#include <vector>
#include "../Obj.h"

// Obj‚ÌSTATE‚ªTHROWN(“Š‚°‚ç‚ê‚Ä‚¢‚é)ó‘Ô‚Ì‚ÌUpdateŠÖ”
struct ThrownUpdate
{
	void operator()(Obj&, std::vector<sharedObj>& objList);
};

