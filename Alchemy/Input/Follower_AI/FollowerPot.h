#pragma once
#include <Input/InputState.h>
#include "../AI_Ctl.h"

class FollowerPot :
	public InputState
{
public:
	FollowerPot(Obj& obj);
	~FollowerPot();
	void Update(std::vector<sharedObj>& objList) override;

private:
	Obj & _masterObj;
	AI_Ctl _aiCtl{_masterObj, *this};
};

