#pragma once
#include "../InputState.h"
#include "../AI_Ctl.h"

class FollowGhost :
	public InputState
{
public:
	FollowGhost(Obj& obj);
	~FollowGhost();
	void Update(std::vector<sharedObj>& objList) override;

private:
	Obj & _masterObj;
	AI_Ctl _aiCtl{ _masterObj, *this };
};

