#pragma once
#include <vector>
#include "InputState.h"
#include "../object/PlNum.h"
#include "../NetWork/NetWork.h"
class NetState :
	public InputState
{
public:
	NetState(PlNum plNum);
	~NetState();
	void Update(std::vector<sharedObj>& objList)override;
private:
	unsigned char _num;
	PlNum _plNum;
	std::vector<MES> tmp;
};

