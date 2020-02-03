#pragma once
#include "Input/InputState.h"
#include "../AI_Ctl.h"
class Boss_AI :
	public InputState
{
public:
	Boss_AI(Obj& obj);
	~Boss_AI();
	void Update(std::vector<sharedObj>& objList) override;

private:
	Obj & _masterObj;
	AI_Ctl _aiCtl{ _masterObj, *this };
};

