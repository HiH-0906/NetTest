#pragma once
#include <functional>
#include <vector>
#include "InputState.h"
#include <object\Obj.h>

using funcAI = std::function<bool(Obj&, std::vector<sharedObj>&,InputState&)>;

class AI_Ctl
{
public:
	AI_Ctl(Obj& obj,InputState& state);
	~AI_Ctl();
	void Update(std::vector<sharedObj>& objList);

	void AIList(funcAI);
private:
	std::vector<funcAI> _AIList;	// 
	Obj& _masterObj;				// 呼ばれた元のオブジェクト
	InputState& _masterInput;		// 呼ばれた元の入力管理
};

