#pragma once
#include <DxLib.h>
#include "InputState.h"

class PadState :
	public InputState
{
public:
	PadState();
	PadState(int pudNum);
	~PadState();
	void Update(std::vector<sharedObj>& objList) override;
private:
	int _pudNum;
};

