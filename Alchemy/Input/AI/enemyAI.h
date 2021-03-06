#pragma once
#include "../InputState.h"
#include "../AI_Ctl.h"

class enemyAI :
	public InputState
{
public:
	enemyAI(Obj& obj);
	~enemyAI();
	void Update(std::vector<sharedObj>& objList) override;			// 処理

private:
	Obj& _masterObj;						// 呼ばれた元
	AI_Ctl _aiCtl{_masterObj,*this};
};

