#pragma once
#pragma once
#include <vector>
#include <object\Obj.h>

struct OctpusAttack
{
	void operator ()(Obj& obj, std::vector<sharedObj>& objList);
	
private:
	double _effectRad;		// ´Ìª¸Ä—p‚ÌŠp“x
};


