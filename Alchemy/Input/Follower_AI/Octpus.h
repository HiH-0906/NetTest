#pragma once
#include "../InputState.h"
#include "../AI_Ctl.h"

class Octpus :
	public InputState
{
public:
	Octpus(Obj& obj);
	~Octpus();

	void Update(std::vector<sharedObj>& objList) override;			// ˆ—
private:
	Obj& _masterObj;
	AI_Ctl _aiCtl{ _masterObj, *this };
};

