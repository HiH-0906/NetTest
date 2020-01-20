#pragma once
#include "../InputState.h"
#include "../AI_Ctl.h"

class FollowDemon :
	public InputState
{
public:
	FollowDemon(Obj& obj);
	~FollowDemon();
	void Update(std::vector<sharedObj>& objList) override;

private:
	Obj & _masterObj;
	AI_Ctl _aiCtl{ _masterObj, *this };
	
};

