#include "AI_Ctl.h"

AI_Ctl::AI_Ctl(Obj & obj,InputState& input):_masterObj(obj),_masterInput(input)
{
}

AI_Ctl::~AI_Ctl()
{
}

void AI_Ctl::Update(std::vector<sharedObj>& objList)
{
	for (auto ai : _AIList)
	{
		if (ai(_masterObj, objList,_masterInput))
		{
			break;
		}
	}
}

void AI_Ctl::AIList(funcAI ai)
{
	_AIList.emplace_back(ai);
}
