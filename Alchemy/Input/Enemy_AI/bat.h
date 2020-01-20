#pragma once
#include "../InputState.h"
#include "../AI_Ctl.h"

class Bat :
	public InputState
{
public:
	Bat(Obj& obj);
	~Bat();
	void Update(std::vector<sharedObj>& objList) override;			// ˆ—

private:
	Obj & _masterObj;
	AI_Ctl _aiCtl{ _masterObj, *this };
};

