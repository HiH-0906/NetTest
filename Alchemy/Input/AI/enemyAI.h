#pragma once
#include "../InputState.h"
#include "../AI_Ctl.h"

class enemyAI :
	public InputState
{
public:
	enemyAI(Obj& obj);
	~enemyAI();
	void Update(std::vector<sharedObj>& objList) override;			// ˆ—

private:
	Obj& _masterObj;						// ŒÄ‚Î‚ê‚½Œ³
	AI_Ctl _aiCtl{_masterObj,*this};
};

