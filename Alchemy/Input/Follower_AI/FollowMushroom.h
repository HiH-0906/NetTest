#pragma once
#include "../InputState.h"
#include "../AI_Ctl.h"

class FollowMushroom :
	public InputState
{
public:
	FollowMushroom(Obj& obj);
	~FollowMushroom();
	void Update(std::vector<sharedObj>& objList) override;

private:
	Obj & _masterObj;
	AI_Ctl _aiCtl{ _masterObj, *this };
};

