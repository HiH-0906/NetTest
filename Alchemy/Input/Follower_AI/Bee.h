#pragma once
#include "../InputState.h"
#include "../AI_Ctl.h"

class Bee :
	public InputState
{
public:
	Bee(Obj& obj);
	~Bee();
	void Update(std::vector<sharedObj>& objList) override;

private:
	Obj & _masterObj;
	AI_Ctl _aiCtl{ _masterObj, *this };
};

