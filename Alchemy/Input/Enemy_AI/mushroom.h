#pragma once
#include "../InputState.h"
#include "../AI_Ctl.h"

class Mushroom :
	public InputState
{
public:
	Mushroom(Obj& obj);
	~Mushroom();
	void Update(std::vector<sharedObj>& objList) override;			// ˆ—

private:
	Obj & _masterObj;
	AI_Ctl _aiCtl{ _masterObj, *this };
};

